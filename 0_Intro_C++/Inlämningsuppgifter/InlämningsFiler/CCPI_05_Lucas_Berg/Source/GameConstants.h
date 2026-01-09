#pragma once

namespace GameConstants
{
	//Diablo.cpp
	constexpr int PLAYER_NAME_ARRAY_SIZE = 18;
	constexpr int PLAYER_NAME_MIN_LENGTH = 2;
	constexpr int PLAYER_NAME_MAX_LENGTH = 16;
	constexpr int CIN_IGNORE = 10000;

	constexpr int DOOR_COUNT_MAXIMUM = 4;

	//Attributes
	constexpr float HEALTH_ZERO = 0.0f;
	constexpr float DAMAGE_ZERO = 0.0f;

	constexpr float STRENGTH_BASE = 10.0f; //styrka (10-99)
	constexpr float AGILITY_BASE = 10.0f; // smidighet (10-99)
	constexpr float ENDURANCE_BASE = 10.0f; // fysik (10-99)

	//PlayerController
	constexpr int NAV_DIRECTION_CHOICE_OFFSET = 1;

	//Player
	constexpr int PLAYER_ATTACK_INDEX_ZERO = 0;
	constexpr int PLAYER_ATTACK_INDEX_INVALID = -1;
	constexpr int PLAYER_TARGET_ENEMY_MIN = 1;
	constexpr int PLAYER_TARGET_INDEX_OFFSET = 1;
	constexpr int PLAYER_ATTACK_INDEX_OFFSET = 1;

	constexpr float HEAVY_MULTI_MIN = 0.8f;
	constexpr float HEAVY_MULTI_MAX = 1.2f;

	constexpr float ATTRI_GET_HEALTH_ENDURANCE_MULTI = 4.0f;
	constexpr float ATTRI_GET_HEALTH_STRENGTH_MULTI = 6.0f;
	constexpr float ATTRI_GET_HEALTH_AGILITY_MULTI = 3.0f;
	constexpr float ATTRI_GET_CARRY_AGILITY_DIV = 3.0f;

	constexpr float DEFENSE_BASE_MULTI = 1.0f;
	constexpr float DEFENSE_SCALING_FACTOR = 150.0f;

	//Cheats
	constexpr int CHEATS_ONESHOT_MULTI = 1000;

	//array indexes
	constexpr int ARRAY_INDEX_OFFSET = 1;
	constexpr int ARRAY_COUNT_ZERO = 0;

	//worldmap
	constexpr int ENEMY_ID_FIRST = 0;


	constexpr int LOCK_1_AGILITY_REQ_DECLARE = 50;
	constexpr int LOCK_1_STRENGTH_REQ_DECLARE = 10;

	constexpr int LOCK_1_AGILITY_REQ = 50;
	constexpr int LOCK_1_STRENGTH_REQ = 10;
}
