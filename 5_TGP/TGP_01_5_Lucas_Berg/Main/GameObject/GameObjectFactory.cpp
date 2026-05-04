#include "GameObjectFactory.h"
#include "Model/PrimitiveMeshes.h"
#include "../Shader/ShaderFactory.h"
#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define NOMINMAX 

#include "tiny_obj_loader.h"

GameObjectFactory* GameObjectFactory::myInstance = nullptr;

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}

bool GameObjectFactory::Init(ID3D11Device* aDevice)
{
	auto& shaders = ShaderFactory::GetInstance();

	myMeshes["Cube"].Init(aDevice,
		Primitives::UVCubeVertices, 24,
		Primitives::UVCubeIndices, 36);

	myMeshes["Pyramid"].Init(aDevice,
		Primitives::PyramidVertices, 16,
		Primitives::PyramidIndices, 18);

	return true;
}

GameObject GameObjectFactory::CreateGameObject(const std::string& aMeshName)
{
	GameObject obj;
	auto it = myMeshes.find(aMeshName);
	if (it != myMeshes.end())
		obj.SetMesh(&it->second);
	return obj;
}

bool GameObjectFactory::LoadObj(ID3D11Device* aDevice, const std::string& aMeshName, const std::string& aFilePath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, aFilePath.c_str());
	if (!ok) return false;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (auto& shape : shapes)
	{
		for (auto& index : shape.mesh.indices)
		{
			Vertex v = {};
			v.x = attrib.vertices[3 * index.vertex_index + 0];
			v.y = attrib.vertices[3 * index.vertex_index + 1];
			v.z = attrib.vertices[3 * index.vertex_index + 2];
			v.w = 1.0f;
			v.r = v.g = v.b = v.a = 1.0f;

			if (index.texcoord_index >= 0)
			{
				v.u = attrib.texcoords[2 * index.texcoord_index + 0];
				v.v = 1.0f - attrib.texcoords[2 * index.texcoord_index + 1];
			}

			if (index.normal_index >= 0)
			{
				v.nx = attrib.normals[3 * index.normal_index + 0];
				v.ny = attrib.normals[3 * index.normal_index + 1];
				v.nz = attrib.normals[3 * index.normal_index + 2];
			}

			indices.push_back((unsigned int)vertices.size());
			vertices.push_back(v);
		}
	}

	myMeshes[aMeshName].Init(aDevice, vertices.data(), (unsigned int)vertices.size(),
		indices.data(), (unsigned int)indices.size());
	return true;
}