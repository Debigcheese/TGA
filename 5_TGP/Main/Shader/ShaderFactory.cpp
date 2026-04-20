#include "ShaderFactory.h"

ShaderFactory& ShaderFactory::GetInstance()
{
	static ShaderFactory instance;
	return instance;
}

bool ShaderFactory::Init(ID3D11Device* aDevice)
{
	myDevice = aDevice;

	auto colored = std::make_shared<Shader>();
	if (!colored->Init(aDevice, "colored_mesh_VS.cso", "colored_mesh_PS.cso"))
		return false;
	myShaders["colored"] = colored;

	auto animated = std::make_shared<Shader>();
	if (!animated->Init(aDevice, "colored_mesh_VS.cso", "animated_mesh_PS.cso"))
		return false;
	myShaders["animated"] = animated;

	return true;
}

Shader* ShaderFactory::GetShader(const std::string& aName)
{
	auto it = myShaders.find(aName);
	if (it != myShaders.end())
		return it->second.get();
	return nullptr;
}