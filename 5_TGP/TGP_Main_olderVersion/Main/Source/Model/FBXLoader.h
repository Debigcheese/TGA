#pragma once
#include <vector>
#include <d3d11.h>
#include "Model/Mesh.h"

bool LoadFBXModel(ID3D11Device* aDevice, const char* aPath, std::vector<Mesh>& outMeshes);
