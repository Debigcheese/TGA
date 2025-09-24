#pragma once

namespace GameConstants
{
	//Diablo.cpp
	const int PLAYER_NAME_ARRAY_SIZE = 18;
	const int PLAYER_NAME_MIN_LENGTH = 2;
	const int PLAYER_NAME_MAX_LENGTH = 16;
	const int CIN_IGNORE = 10000;

	const int DOOR_COUNT_MAXIMUM = 4;

	//Attributes
	const float HEALTH_ZERO = 0.0f;
	const float DAMAGE_ZERO = 0.0f;

	const float STRENGTH_BASE = 10.0f; //styrka (10-99)
	const float AGILITY_BASE = 20.0f; // smidighet (10-99)
	const float ENDURANCE_BASE = 40.0f; // fysik (10-99)

	//Navigation
	const int NAV_DIRECTION_CHOICE_OFFSET = 1;

	//Player
	const int PLAYER_ATTACK_INDEX_ZERO = 0;
	const int PLAYER_ATTACK_INDEX_INVALID = -1;
	const int PLAYER_TARGET_ENEMY_MIN = 1;
	const int PLAYER_TARGET_INDEX_OFFSET = 1;
	const int PLAYER_ATTACK_INDEX_OFFSET = 1;

	const float HEAVY_MULTI_MIN = 0.8f;
	const float HEAVY_MULTI_MAX = 1.2f;

	const float ATTRI_GET_HEALTH_ENDURANCE_MULTI = 4.0f;
	const float ATTRI_GET_HEALTH_STRENGTH_MULTI = 6.0f;
	const float ATTRI_GET_HEALTH_AGILITY_MULTI = 3.0f;
	const float ATTRI_GET_CARRY_AGILITY_DIV = 3.0f;

	const float DEFENSE_BASE_MULTI = 1.0f;
	const float DEFENSE_SCALING_FACTOR = 150.0f;

	//Cheats
	const int CHEATS_ONESHOT_MULTI = 1000;

	//array indexes
	const int ARRAY_INDEX_OFFSET = 1;
	const int ARRAY_COUNT_ZERO = 0;

	//worldmap
	const int ENEMY_ID_FIRST = 0;

	const int ROOM_0_ID = 0;
	const int ROOM_1_ID = 1;
	const int ROOM_2_ID = 2;
	const int ROOM_3_ID = 3;
	const int ROOM_4_ID = 4;
	const int ROOM_WIN_ID = 5;

	const int LOCK_1_AGILITY_REQ_DECLARE = 50;
	const int LOCK_1_STRENGTH_REQ_DECLARE = 10;

	const int LOCK_1_AGILITY_REQ = 50;
	const int LOCK_1_STRENGTH_REQ = 10;
}
