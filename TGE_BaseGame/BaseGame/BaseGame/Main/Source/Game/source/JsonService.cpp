#include "JsonService.h"

#include <iostream>

JsonService::JsonService()
{
	static bool loaded = false;

	if (!loaded)
	{
		std::ifstream file("../Source/Game/source/JsonConfig.json");
		if (file)
		{
			file >> j;
		}

		loaded = true;
		file.close();
	}
}

const json& JsonService::Get()
{
	return Instance()->j;
}

JsonService* JsonService::Instance()
{
	static JsonService instance;
	return &instance;
}

// Anywhere
//auto& cfg = JsonService::Get();
//auto& sprites = cfg["Sprites"];

//std::ifstream file("JsonConfig.json");
//Must be in working directory (usually in .exe)
//else search for path:
//std::ifstream file("../Source/Game/source/JsonConfig.json");

//debug tip: std::cout << std::filesystem::current_path();
