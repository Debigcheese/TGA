#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class JsonService
{
public:
	JsonService();
	static const json& Get();

private:
	static JsonService* Instance();
	json j;
};
