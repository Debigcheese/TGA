#include "Game.h"

#include "Actor.h"
#include "IMapPass.h"
#include "IMessageListener.h"
#include "GameState.h"
#include "MapConfigSingleton.h"
#include <random>

class DrunkenWalkPass : public IMapPass
{
public:
	void Execute(Game* game) override
	{
		// Fetch configuration from the global singleton
		int steps = MapConfigSingleton::GetInstance()->PathStepsPerCarve;
		int area = MapConfigSingleton::GetInstance()->InitialAreaSize;

		// Hardcoded starting points
		game->CarveRandomPath({3, 3}, steps, area);
		game->CarveRandomPath({game->myMapWidth / 2, game->myMapHeight / 2}, steps, area);
		game->CarveRandomPath({game->myMapWidth - 4, 4}, steps, area);
		game->CarveRandomPath({4, game->myMapHeight - 4}, steps, area);
		game->CarveRandomPath({game->myMapWidth - 4, game->myMapHeight - 4}, steps, area);
	}
};

class RoomStampingPass : public IMapPass
{
public:
	int RoomMinSize = 5;
	int RoomMaxSize = 10;
	int NumRooms = 3;

	void Execute(Game* game) override
	{
		for (int i = 0; i < NumRooms; ++i)
		{
			// Find a random starting point
			Coordinate center = game->FindRandomOpenTile();
			int size = RoomMinSize + rand() % (RoomMaxSize - RoomMinSize + 1);

			int startX = center.x - size / 2;
			int startY = center.y - size / 2;
			int endX = startX + size;
			int endY = startY + size;

			// Clamp bounds
			if (startX < 1) startX = 1;
			if (startY < 1) startY = 1;
			if (endX > game->myMapWidth - 2) endX = game->myMapWidth - 2;
			if (endY > game->myMapHeight - 2) endY = game->myMapHeight - 2;

			// Carve the room, potentially overwriting existing tunnels (DrunkenWalkPass output)
			for (int y = startY; y < endY; y++)
			{
				for (int x = startX; x < endX; x++)
				{
					if (game->myMap[y][x])
					{
						delete game->myMap[y][x];
					}
					game->myMap[y][x] = new FloorTile();
				}
			}
		}
	}
};

class PipelineStrategy : public IMapGenerationStrategy
{
private:
	std::vector<IMapPass*> myPasses;

public:
	PipelineStrategy()
	{
		myPasses.push_back(new DrunkenWalkPass()); // 1. Tunnels
		myPasses.push_back(new RoomStampingPass()); // 2. Rooms (overwrites tunnels)
	}

	~PipelineStrategy()
	{
		for (IMapPass* pass : myPasses)
			delete pass;
	}

	void Generate(Game* game) override
	{
		game->InitializeMap();

		for (IMapPass* pass : myPasses)
		{
			pass->Execute(game);
		}
	}
};


// ----------------------------------------------------
// GAME IMPLEMENTATION BLOCK 1: MAP GENERATION HELPERS
// ----------------------------------------------------

void Game::InitializeMap()
{
	if (myMap.empty())
	{
		myMap.resize(myMapHeight);
		for (int y = 0; y < myMapHeight; y++)
		{
			myMap[y].resize(myMapWidth);
		}
	}

	for (int y = 0; y < myMapHeight; y++)
	{
		for (int x = 0; x < myMapWidth; x++)
		{
			if (y == 0 || y == myMapHeight - 1 || x == 0 || x == myMapWidth - 1)
			{
				myMap[y][x] = new WallTile();
			}
			else
			{
				myMap[y][x] = new WallTile();
			}
		}
	}
}

void Game::CarveRandomPath(Coordinate current, int steps, int areaSize)
{
	int x = current.x;
	int y = current.y;

	// Carve out a starting area (room-like element)
	for (int i = -areaSize / 2; i <= areaSize / 2; i++)
	{
		for (int j = -areaSize / 2; j <= areaSize / 2; j++)
		{
			int cx = x + i;
			int cy = y + j;
			if (cx > 0 && cx < myMapWidth - 1 && cy > 0 && cy < myMapHeight - 1)
			{
				delete myMap[cy][cx];
				myMap[cy][cx] = new FloorTile();
			}
		}
	}

	// Start the random walk
	for (int i = 0; i < steps; i++)
	{
		int dx = 0, dy = 0;

		if (rand() % 10 == 0)
		{
			dx = (rand() % 10) - 5;
			dy = (rand() % 10) - 5;
		}
		else
		{
			int direction = rand() % 4;
			if (direction == 0) dy = -1;
			else if (direction == 1) dy = 1;
			else if (direction == 2) dx = -1;
			else if (direction == 3) dx = 1;
		}

		x += dx;
		y += dy;

		if (x <= 0) x = 1;
		if (x >= myMapWidth - 1) x = myMapWidth - 2;
		if (y <= 0) y = 1;
		if (y >= myMapHeight - 1) y = myMapHeight - 2;

		// ANTIPATTERN: More memory leak by replacing pointer without checking type
		delete myMap[y][x];
		myMap[y][x] = new FloorTile();
	}
}

void Game::EnsureExitReachable()
{
	int requiredRightSteps = myMapWidth - 3;
	int requiredDownSteps = myMapHeight - 3;

	if (requiredRightSteps <= 0 || requiredDownSteps <= 0) return;

	std::vector<int> pathSteps;
	for (int i = 0; i < requiredRightSteps; ++i) { pathSteps.push_back(1); } // 1 = Right
	for (int i = 0; i < requiredDownSteps; ++i) { pathSteps.push_back(-1); } // -1 = Down

	std::random_shuffle(pathSteps.begin(), pathSteps.end());

	int currentX = 1;
	int currentY = 1;

	for (int move : pathSteps)
	{
		int newX = currentX;
		int newY = currentY;

		if (move == 1) newX++;
		else if (move == -1) newY++;

		if (newX > 0 && newX < myMapWidth - 1 && newY > 0 && newY < myMapHeight - 1)
		{
			if (dynamic_cast<WallTile*>(myMap[newY][newX]))
			{
				delete myMap[newY][newX];
				myMap[newY][newX] = new FloorTile();
			}
			currentX = newX;
			currentY = newY;
		}
	}
}

Game::Game()
{
	myMapWidth = 80;
	myMapHeight = 22;
	myPlayer = nullptr;
	myCurrentState = nullptr;
	m_lastPlayerInput = 0;
	srand((unsigned int)time(nullptr));

	m_physicalType = new PhysicalDamage();
	m_fireType = new FireDamage();
	m_iceType = new IceDamage();

	myMapGenStrategy = new PipelineStrategy();
}

Game::~Game()
{
}


// ----------------------------------------------------
// GAME IMPLEMENTATION BLOCK 3: UTILITY METHODS
// ----------------------------------------------------

void Game::updateLog(std::string message)
{
	LogEntry.push_back(message);
	if (LogEntry.size() > 5)
	{
		LogEntry.pop_back();
	}
}

Actor* Game::GetActorAt(int x, int y)
{
	for (Actor* actor : m_actorList)
	{
		if (actor->myIsActive && actor->myX == x && actor->myY == y && actor->IsTargetable())
		{
			return actor;
		}
	}
	return NULL;
}

Coordinate Game::FindRandomOpenTile()
{
	int x, y;
	int attempts = 0;
	while (attempts < myMapWidth * myMapHeight)
	{
		x = 1 + rand() % (myMapWidth - 2);
		y = 1 + rand() % (myMapHeight - 2);

		if (myMap[y][x]->IsWalkable(nullptr) && dynamic_cast<FloorTile*>(myMap[y][x]) && !GetActorAt(x, y))
		{
			return {x, y};
		}
		attempts++;
	}
	return {1, 1};
}

void Game::CheckPlayerVisibility(int maxDist)
{
	for (int y = 0; y < myMapHeight; y++)
	{
		for (int x = 0; x < myMapWidth; x++)
		{
			int dist = (int)sqrt(pow(myPlayer->myX - x, 2) + pow(myPlayer->myY - y, 2));
			if (dist <= maxDist)
			{
				// Use the safe setter instead of touching internals
				myMap[y][x]->SetDiscovered(true);
			}
		}
	}
}

void Game::ChangeGameState(GameState* newState)
{
	if (myCurrentState)
	{
		delete myCurrentState;
	}
	myCurrentState = newState;
}

// ----------------------------------------------------
// GAME IMPLEMENTATION BLOCK 4: THE CORE RUN LOOP
// ----------------------------------------------------

void Game::Run()
{
	// --- Initialize Procedural Map via Pipeline Strategy ---
	myMapGenStrategy->Generate(this);


	// --- Hardcoded Feature Placement ---
	delete myMap[myMapHeight - 2][myMapWidth - 2];
	myMap[myMapHeight - 2][myMapWidth - 2] = new ExitTile();

	// Guaranteed connectivity check and fix
	EnsureExitReachable();

	// --- Create Player Actor ---
	myPlayer = new PlayerActor(1, 1);
	m_actorList.push_back(myPlayer);

	for (int i = 0; i < 4; i++)
	{
		Coordinate pos = FindRandomOpenTile();
		m_actorList.push_back(new GoblinActor(pos.x, pos.y));
	}

	for (int i = 0; i < 4; i++)
	{
		Coordinate pos = FindRandomOpenTile();
		m_actorList.push_back(new FireImpActor(pos.x, pos.y));
	}

	for (int i = 0; i < 10; i++)
	{
		Coordinate pos = FindRandomOpenTile();

		TrapActor* trapEntity = new TrapActor(pos.x, pos.y);
		m_actorList.push_back(trapEntity);

		delete myMap[pos.y][pos.x];
		myMap[pos.y][pos.x] = new TrapTile(trapEntity);
	}

	// --- Setup Log Listener ---
	class GameLogger : public IMessageListener
	{
	public:
		Game* myGame;

		void HandleMessage(Message* msg)
		{
			Log_Message* log = dynamic_cast<Log_Message*>(msg);
			if (log)
			{
				myGame->updateLog(log->text);
			}
		}
	};
	GameLogger* logger = new GameLogger();
	logger->myGame = this;
	MessageBus::GetInstance()->Subscribe(logger);

	// --- Start Game ---
	updateLog("Welcome to the Tangled Tomb! Press 'h' for help.");
	CheckPlayerVisibility(8);
	ChangeGameState(new PlayState(this));

	myCurrentState->Draw(this);

	// --- Main Loop ---
	while (myCurrentState != NULL)
	{
		LogEntry.clear();
		myCurrentState->Update(this);
		if (myCurrentState)
		{
			myCurrentState->Draw(this);
		}
	}
}
