#include "ShaderFactory.h"

ShaderFactory& ShaderFactory::GetInstance()
{
	static ShaderFactory instance;
	return instance;
}

bool ShaderFactory::Init(ID3D11Device* aDevice)
{
	myDevice = aDevice;

	auto addShader = [&](const std::string& name, const std::string& vs, const std::string& ps) -> bool
		{
			auto shader = std::make_shared<Shader>();
			if (!shader->Init(aDevice, vs, ps)) return false;
			myShaders[name] = shader;
			return true;
		};

	if (!addShader("default", "default_VS.cso", "default_PS.cso")) return false;
	if (!addShader("colored", "default_VS.cso", "colored_mesh_PS.cso"))  return false;
	if (!addShader("textured", "default_VS.cso", "textured_mesh_PS.cso")) return false;
	if (!addShader("camera", "default_VS.cso", "camera_pos_PS.cso")) return false;
	if (!addShader("lit", "model_lit_VS.cso", "model_lit_PS.cso"))      return false;
	if (!addShader("animated", "model_animated_VS.cso", "model_animated_PS.cso")) return false;
	return true;
}

Shader* ShaderFactory::GetShader(const std::string& aName)
{
	auto it = myShaders.find(aName);
	if (it != myShaders.end())
		return it->second.get();
	return nullptr;
}