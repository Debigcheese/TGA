#include "GameObjectFactory.h"
#include "Model/PrimitiveMeshes.h"
#include <TGAFBXImporter/source/Importer.h>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <iterator>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#include "tiny_obj_loader.h"

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}

bool GameObjectFactory::Init(ID3D11Device* aDevice, ID3D11DeviceContext* aContext)
{
	myDevice = aDevice;
	myContext = aContext;

	const unsigned char white[] = {255, 255, 255, 255};
	const unsigned char flatNormal[] = {128, 128, 255, 255};
	if (!myFallbackTextures[TextureSlot::Albedo].Initialize(aDevice, aContext, white, 1, 1, true)) return false;
	if (!myFallbackTextures[TextureSlot::Normal].Initialize(aDevice, aContext, flatNormal, 1, 1, false)) return false;
	if (!myFallbackTextures[TextureSlot::Material].Initialize(aDevice, aContext, white, 1, 1, false)) return false;

	using namespace Primitives;
	if (!AddSubMesh(CreateModel("Cube"), UVCubeVertices, (unsigned int)std::size(UVCubeVertices),
	                UVCubeIndices, (unsigned int)std::size(UVCubeIndices)))
		return false;

	if (!AddSubMesh(CreateModel("Pyramid"), PyramidVertices, (unsigned int)std::size(PyramidVertices),
	                PyramidIndices, (unsigned int)std::size(PyramidIndices)))
		return false;

	if (!AddSubMesh(CreateModel("Plane"), PlaneVertices, (unsigned int)std::size(PlaneVertices),
	                PlaneIndices, (unsigned int)std::size(PlaneIndices)))
		return false;

	return true;
}

GameObject GameObjectFactory::CreateGameObject(const std::string& aModelName)
{
	GameObject obj;
	obj.SetModel(GetModel(aModelName));
	return obj;
}

Model* GameObjectFactory::GetModel(const std::string& aModelName)
{
	auto it = myModels.find(aModelName);
	if (it == myModels.end())
	{
		assert(false && "GameObjectFactory: no model with that name, did you forget LoadFbx/LoadObj?");
		return nullptr;
	}
	return &it->second;
}

Texture* GameObjectFactory::GetTexture(const std::string& aFilePath, bool anSRGB)
{
	auto it = myTextures.find(aFilePath);
	if (it != myTextures.end())
		return &it->second;

	int width, height, channels;
	unsigned char* pixels = stbi_load(aFilePath.c_str(), &width, &height, &channels, 4);
	if (!pixels)
		return nullptr;

	Texture& texture = myTextures[aFilePath];
	const bool ok = texture.Initialize(myDevice, myContext, pixels, width, height, anSRGB);
	stbi_image_free(pixels);

	if (!ok)
	{
		myTextures.erase(aFilePath);
		return nullptr;
	}
	return &texture;
}

Model& GameObjectFactory::CreateModel(const std::string& aModelName)
{
	Model& model = myModels[aModelName];
	model = Model{};
	return model;
}

Model::SubMesh* GameObjectFactory::AddSubMesh(Model& aModel,
                                              const Vertex* aVertices, unsigned int aVertexCount,
                                              const unsigned int* aIndices, unsigned int aIndexCount,
                                              const std::string& aMaterialName)
{
	Model::SubMesh& subMesh = aModel.AddSubMesh();
	subMesh.materialName = aMaterialName;

	for (int slot = 0; slot < TextureSlot::Count; ++slot)
	{
		subMesh.defaultTextures[slot] = &myFallbackTextures[slot];
	}
	for (unsigned int i = 0; i < aVertexCount; ++i)
	{
		const Vertex& v = aVertices[i];
		aModel.GrowRadius(std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	}

	if (!subMesh.mesh.Init(myDevice, aVertices, aVertexCount, aIndices, aIndexCount))
		return nullptr;

	return &subMesh;
}

Texture* GameObjectFactory::FindTexture(const std::string& aFolder, const std::vector<std::string>& someBaseNames,
                                        int aSlot)
{
	static const std::vector<std::string> suffixes[TextureSlot::Count] = {
		{"_C", "_Diffuse", "_Albedo", "_BaseColor", "_Color"},
		{"_N", "_Normal"},
		{"_M", "_Specular", "_Material"},
	};
	static const char* folders[] = {"", "textures/", "../textures/"};
	static const char* extensions[] = {".png", ".jpg", ".jpeg", ".tga", ".tga.png"};

	for (const std::string& baseName : someBaseNames)
	{
		for (const char* folder : folders)
		{
			for (const std::string& suffix : suffixes[aSlot])
			{
				for (const char* extension : extensions)
				{
					const std::string path = aFolder + folder + baseName + suffix + extension;
					if (std::filesystem::exists(path))
						return GetTexture(path, aSlot == TextureSlot::Albedo);
				}
			}
		}
	}
	return nullptr;
}

bool GameObjectFactory::LoadFbx(const std::string& aModelName, const std::string& aFilePath)
{
	TGA::FBX::Mesh fbxMesh;
	if (!TGA::FBX::Importer::LoadMeshA(aFilePath, fbxMesh))
		return false;

	struct Part
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};
	std::map<unsigned int, Part> parts;

	for (const TGA::FBX::Mesh::Element& element : fbxMesh.Elements)
	{
		Part& part = parts[element.MaterialIndex];
		const unsigned int baseVertex = static_cast<unsigned int>(part.vertices.size());

		for (const auto& src : element.Vertices)
		{
			Vertex v = {};
			v.x = src.Position[0];
			v.y = src.Position[1];
			v.z = src.Position[2];
			v.w = src.Position[3];

			v.r = v.g = v.b = v.a = 1.0f;

			v.u = src.UVs[0][0];
			v.v = src.UVs[0][1];

			v.nx = src.Normal[0];
			v.ny = src.Normal[1];
			v.nz = src.Normal[2];

			v.tx = src.Tangent[0];
			v.ty = src.Tangent[1];
			v.tz = src.Tangent[2];

			v.bx = src.BiNormal[0];
			v.by = src.BiNormal[1];
			v.bz = src.BiNormal[2];

			part.vertices.push_back(v);
		}

		for (unsigned int index : element.Indices)
			part.indices.push_back(baseVertex + index);
	}

	const std::string folder = aFilePath.substr(0, aFilePath.find_last_of("/\\") + 1);
	const std::string fileName = std::filesystem::path(aFilePath).stem().string();
	Model& model = CreateModel(aModelName);

	for (auto& [materialIndex, part] : parts)
	{
		if (part.vertices.empty() || part.indices.empty())
			continue;

		std::string materialName;
		if (materialIndex < fbxMesh.Materials.size())
			materialName = fbxMesh.Materials[materialIndex].MaterialName;

		Model::SubMesh* subMesh = AddSubMesh(model,
		                                     part.vertices.data(), static_cast<unsigned int>(part.vertices.size()),
		                                     part.indices.data(), static_cast<unsigned int>(part.indices.size()),
		                                     materialName);
		if (!subMesh)
			return false;

		std::vector<std::string> baseNames;
		if (!materialName.empty())
		{
			baseNames.push_back(materialName);
			baseNames.push_back(fileName + "_" + materialName);
		}
		baseNames.push_back(fileName + "_DefaultMaterial");
		baseNames.push_back(fileName);

		for (int slot = 0; slot < TextureSlot::Count; ++slot)
		{
			if (Texture* texture = FindTexture(folder, baseNames, slot))
				subMesh->defaultTextures[slot] = texture;
		}

		if (subMesh->defaultTextures[TextureSlot::Albedo] == &myFallbackTextures[TextureSlot::Albedo])
		{
			const std::string message = "LoadFbx: no albedo texture found for material '" + materialName +
				"' (file '" + fileName + "') in " + aFilePath + "\n";
			OutputDebugStringA(message.c_str());
		}
	}

	return model.GetSubMeshCount() > 0;
}

bool GameObjectFactory::LoadObj(const std::string& aModelName, const std::string& aFilePath)
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

	if (vertices.empty() || indices.empty())
		return false;

	return AddSubMesh(CreateModel(aModelName), vertices.data(), (unsigned int)vertices.size(),
	                  indices.data(), (unsigned int)indices.size()) != nullptr;
}
