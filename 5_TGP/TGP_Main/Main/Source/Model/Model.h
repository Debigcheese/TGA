#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Model/Mesh.h"

class Texture;

namespace TextureSlot
{
	enum : int
	{
		Albedo = 0,
		Normal,
		Material,
		Count
	};

	inline constexpr unsigned int Registers[Count] = {10, 12, 13};
}

class Model
{
public:
	struct SubMesh
	{
		Mesh mesh;
		std::string materialName;
		Texture* defaultTextures[TextureSlot::Count] = {};
	};

	SubMesh& AddSubMesh() { return mySubMeshes.emplace_back(); }

	int GetSubMeshCount() const { return static_cast<int>(mySubMeshes.size()); }
	SubMesh& GetSubMesh(int anIndex) { return mySubMeshes[anIndex]; }
	const SubMesh& GetSubMesh(int anIndex) const { return mySubMeshes[anIndex]; }

	float GetRadius() const { return myRadius; }
	void GrowRadius(float aRadius) { myRadius = std::max(myRadius, aRadius); }
private:
	std::vector<SubMesh> mySubMeshes;
	float myRadius = 0.0f;
};
