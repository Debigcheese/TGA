#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Config
{
public:
	Config();
	static const json& Get();

private:
	static Config* Instance();
	json j;
};
