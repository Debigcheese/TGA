#pragma once
#include "Shader.h"
#include <unordered_map>
#include <memory>
#include <string>

class ShaderFactory
{
public:
	static ShaderFactory& GetInstance();

	bool Init(ID3D11Device* aDevice);
	Shader* GetShader(const std::string& aName);

private:
	ShaderFactory() = default;
	ID3D11Device* myDevice = nullptr;
	std::unordered_map<std::string, std::shared_ptr<Shader>> myShaders;
};