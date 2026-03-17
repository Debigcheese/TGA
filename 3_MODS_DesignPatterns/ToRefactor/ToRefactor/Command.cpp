#include "Command.h"
#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include "StatsComponent.h"

MoveCommand::MoveCommand(Actor* aActor, int aNewX, int aNewY, Game* aGame) : myActor(aActor),
                                                                             myNewX(aNewX), myNewY(aNewY),
                                                                             myPrevX(0), myPrevY(0), myPrevHp(0)
{
	myPrevX = aActor->myX;
	myPrevY = aActor->myY;
	myPrevHp = myActor->GetComponent<StatsComponent>()->getHp();

	// snapshot all monster positions too
	for (Actor* a : aGame->m_actorList)
	{
		myMonsterSnapshot.push_back({a, a->myX, a->myY});
	}
}

void MoveCommand::Execute()
{
	myActor->myX = myNewX;
	myActor->myY = myNewY;
}

void MoveCommand::Undo()
{
	myActor->myX = myPrevX;
	myActor->myY = myPrevY;
	myActor->GetComponent<StatsComponent>()->setHp(myPrevHp);

	for (auto& snap : myMonsterSnapshot)
	{
		snap.actor->myX = snap.x;
		snap.actor->myY = snap.y;
	}
}
