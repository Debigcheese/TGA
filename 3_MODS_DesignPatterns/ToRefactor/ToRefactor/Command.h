#pragma once
#include <vector>

class Actor;
class Game;


class Command
{
public:
	Command()
	{
	};

	virtual ~Command()
	{
	}

	virtual void Execute() = 0;
	virtual void Undo() = 0;

private:
};

class MoveCommand : public Command
{
public:
	MoveCommand(Actor* aActor, int aNewX, int aNewY, Game* aGame);

	void Execute() override;
	void Undo() override;

private:
	struct ActorSnapshot
	{
		Actor* actor;
		int x, y;
	};

	Actor* myActor;
	int myPrevX, myPrevY, myPrevHp;
	int myNewX, myNewY;
	std::vector<ActorSnapshot> myMonsterSnapshot;
};

//class PotionCommand : public Command
//{
//public:
//	PotionCommand(int aHp, int aPotions)
//	{
//	}
//
//	void Execute() override;
//	void Undo() override;
//
//private:
//	int myHp, myPotions;
//};

//class SpellCommand : public Command
//{
//public:
//	SpellCommand();
//
//	void Execute() override;
//	void Undo() override;
//
//private:
//	int myHp;
//	int myPotions;
//};
