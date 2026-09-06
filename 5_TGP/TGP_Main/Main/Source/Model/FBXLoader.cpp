#include "FBXLoader.h"

#include <TGAFBXImporter/source/Importer.h>
#include "Model/Vertex.h"

bool LoadFBXModel(ID3D11Device* aDevice, const char* aPath, std::vector<Mesh>& outMeshes)
{
	TGA::FBX::Mesh fbxMesh;
	if (!TGA::FBX::Importer::LoadMeshA(aPath, fbxMesh))
		return false;

	outMeshes.reserve(outMeshes.size() + fbxMesh.Elements.size());

	for (const TGA::FBX::Mesh::Element& element : fbxMesh.Elements)
	{
		std::vector<Vertex> vertices;
		vertices.resize(element.Vertices.size());

		for (size_t i = 0; i < element.Vertices.size(); i++)
		{
			const auto& src = element.Vertices[i];
			Vertex& dst = vertices[i];

			dst.x = src.Position[0];
			dst.y = src.Position[1];
			dst.z = src.Position[2];
			dst.w = src.Position[3];

			dst.r = 1.f; /* src.VertexColors[0][0];*/
			dst.g = 1.f; //src.VertexColors[0][1];
			dst.b = 1.f; //src.VertexColors[0][2];
			dst.a = 1.f; //src.VertexColors[0][3];

			dst.u = src.UVs[0][0];
			dst.v = src.UVs[0][1];

			dst.nx = src.Normal[0];
			dst.ny = src.Normal[1];
			dst.nz = src.Normal[2];

			dst.tx = src.Tangent[0];
			dst.ty = src.Tangent[1];
			dst.tz = src.Tangent[2];

			dst.bx = src.BiNormal[0];
			dst.by = src.BiNormal[1];
			dst.bz = src.BiNormal[2];
		}

		if (vertices.empty() || element.Indices.empty())
			continue;

		Mesh& mesh = outMeshes.emplace_back();
		if (!mesh.Init(aDevice,
			vertices.data(), static_cast<unsigned int>(vertices.size()),
			element.Indices.data(), static_cast<unsigned int>(element.Indices.size())))
		{
			outMeshes.pop_back();
			return false;
		}
	}

	return !outMeshes.empty();
}
