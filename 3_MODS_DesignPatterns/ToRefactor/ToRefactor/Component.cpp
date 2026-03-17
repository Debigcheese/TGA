#include "Component.h"

#include "Actor.h"
#include "DamagePacket.h"
#include "Game.h"
#include "GameState.h"
#include "StatsComponent.h"

void SpellbookComponent::AddSpell(Spell* spell)
{
	mySpells.push_back(spell);
	if (!myCurrentSpell) myCurrentSpell = spell;
}


bool PlayerInputComponent::HandleInput(Game* game, char input)
{
	m_tempMoveX = myOwner->myX;
	m_tempMoveY = myOwner->myY;

	game->m_lastPlayerInput = input;

	bool takeTurn = false;

	if (input == 'w')
	{
		m_tempMoveY--;
		takeTurn = true;
	}
	else if (input == 's')
	{
		m_tempMoveY++;
		takeTurn = true;
	}
	else if (input == 'a')
	{
		m_tempMoveX--;
		takeTurn = true;
	}
	else if (input == 'd')
	{
		m_tempMoveX++;
		takeTurn = true;
	}
	else if (input == 'q')
	{
		game->ChangeGameState(NULL);
		return false;
	}
	else if (input == 'h')
	{
		std::string helpMsg =
			"w/a/s/d: Move or Melee Attack\n"
			"p: Drink Potion (Heal 50 HP)\n"
			"c: Cast Current Spell (Enter Targeting Mode)\n"
			"z/x: Change Current Spell\n"
			"h: Show Help (This screen)\n"
			"q: Quit Game\n\n"
			"Targeting Mode:\n"
			"w/a/s/d: Move Target Cursor\n"
			"f: Fire Spell\n"
			"q: Cancel Targeting";
		game->ChangeGameState(new HelpState(game->myCurrentState, helpMsg));
		return false;
	}
	else if (input == 'p')
	{
		InventoryComponent* inv = myOwner->GetComponent<InventoryComponent>();
		if (inv && inv->potions > 0)
		{
			inv->potions--;
			StatsComponent* stats = myOwner->GetComponent<StatsComponent>();
			stats->setHp(stats->getHp() + 50);
			if (stats->getHp() > stats->getMaxHp()) stats->setHp(stats->getMaxHp());
			game->updateLog("You drink a potion.");
			takeTurn = true;
		}
		else
		{
			game->updateLog("You have no potions!");
		}
	}
	else if (input == 'c')
	{
		game->ChangeGameState(new TargetState(game, game->myCurrentState));
		return false;
	}
	else if (input == 'z' || input == 'x')
	{
		PlayerActor* player = static_cast<PlayerActor*>(myOwner);
		if (player && !player->mySpells.empty())
		{
			auto it = std::find(player->mySpells.begin(), player->mySpells.end(), player->myCurrentSpell);
			int index = static_cast<int>(it - player->mySpells.begin());

			if (input == 'x') index++;
			else index--;

			if (index < 0) index = static_cast<int>(player->mySpells.size()) - 1;
			if (index >= static_cast<int>(player->mySpells.size())) index = 0;

			player->myCurrentSpell = player->mySpells[index];
			game->updateLog("Spell: " + player->myCurrentSpell->myName);
		}
		return false;
	}
	else if (input == 'u') // undo key
	{
		if (!myMoveCommands.empty())
		{
			myMoveCommands.back()->Undo();
			myMoveCommands.pop_back();
		}
		return false;
	}
	else
	{
		return false;
	}

	if (!takeTurn) return false;

	Tile* targetTile = game->myMap[m_tempMoveY][m_tempMoveX];
	if (!targetTile->IsWalkable(myOwner))
	{
		game->updateLog("You bump into a wall. Last input was: " + std::string(1, game->m_lastPlayerInput));
		return false;
	}

	{
		auto moveCommand = new MoveCommand(myOwner, m_tempMoveX, m_tempMoveY, game);
		myMoveCommands.push_back(moveCommand);
	}

	Actor* target = game->GetActorAt(m_tempMoveX, m_tempMoveY);
	if (target && target != myOwner)
	{
		StatsComponent* myStats = myOwner->GetComponent<StatsComponent>();
		StatsComponent* targetStats = target->GetComponent<StatsComponent>();
		if (myStats && targetStats)
		{
			DamagePacket dmg;
			dmg.amount = myStats->getAttack();
			dmg.myType = game->m_physicalType;
			dmg.mySource = myOwner;
			targetStats->HandleDamage(dmg);
		}
	}
	else
	{
		myOwner->myX = m_tempMoveX;
		myOwner->myY = m_tempMoveY;
		targetTile->OnStep(game, myOwner);
	}

	return true;
}

void MonsterAIComponent::Update(Game* game)
{
	if (!myOwner || !myOwner->myIsActive) return;

	Actor* player = game->myPlayer;
	int dx = player->myX - myOwner->myX;
	int dy = player->myY - myOwner->myY;

	MonsterActor* monster = static_cast<MonsterActor*>(myOwner);

	bool isAgressive = monster->isAggressive;

	if (!isAgressive)
	{
		// only agressive enemies persue if far away.
		if (abs(dx) > 3 || abs(dy) > 3)
			return;
	}

	if (abs(dx) <= 1 && abs(dy) <= 1)
	{
		StatsComponent* myStats = myOwner->GetComponent<StatsComponent>();
		StatsComponent* targetStats = player->GetComponent<StatsComponent>();
		if (myStats && targetStats)
		{
			DamagePacket dmg;
			dmg.amount = myStats->getAttack();
			dmg.myType = game->m_physicalType;
			dmg.mySource = myOwner;
			targetStats->HandleDamage(dmg);
		}
	}
	else
	{
		int move_x = 0;
		int move_y = 0;
		if (dx > 0) move_x = 1;
		else if (dx < 0) move_x = -1;
		if (dy > 0) move_y = 1;
		else if (dy < 0) move_y = -1;

		int new_x = myOwner->myX + move_x;
		int new_y = myOwner->myY + move_y;

		if (game->myMap[new_y][new_x]->IsWalkable(myOwner) && !game->GetActorAt(new_x, new_y))
		{
			myOwner->myX = new_x;
			myOwner->myY = new_y;
		}
	}
}
