// Config.cpp
#include "Config.h"

Config::Config()
{
	static bool loaded = false; // init guard

	if (!loaded)
	{
		std::ifstream file("config.json");
		if (file)
		{
			file >> j;
		}
		loaded = true;
		file.close();
	}
}

const json& Config::Get()
{
	return Instance()->j;
}

Config* Config::Instance()
{
	static Config instance;
	return &instance;
}


// Anywhere
//auto& cfg = GetConfig();
//float g = cfg.heli.gravity;
