#include "GameState.h"

#include <conio.h>
#include <sstream>
#include <iostream>

#include "Actor.h"
#include "ActorDiedMessage.h"
#include "Component.h"
#include "StatsComponent.h"
#include "Game.h"



void GameOverState::Update(Game* game)
{
    if (_getch()) game->ChangeGameState(NULL);
}
void GameOverState::Draw(Game* game)
{
    system("cls");
    printf("GAME OVER\n\n");
    printf("%s\n\n", game->LogEntry[0].c_str());
    printf("Press any key to exit.\n");
}

PlayState::PlayState(Game* game)
{
    this->myGame = game;
    MessageBus::GetInstance()->Subscribe(this);
}

void PlayState::HandleMessage(Message* msg)
{
    ActorDiedMessage* death = dynamic_cast<ActorDiedMessage*>(msg);
    if (death && death->myVictim == myGame->myPlayer)
    {
        myGame->updateLog("You have been slain!");
        myGame->ChangeGameState(new GameOverState());
    }
}

void PlayState::Update(Game* game)
{
    char input = _getch();
    PlayerInputComponent* inputComp = game->myPlayer->GetComponent<PlayerInputComponent>();
    bool playerTookTurn = inputComp->HandleInput(game, input);

    if (playerTookTurn)
    {
        for (Actor* actor : game->m_actorList)
            if (actor != game->myPlayer && actor->myIsActive)
                actor->Update(game);

        game->CheckPlayerVisibility(8);
    }
}

void PlayState::Draw(Game* game)
{
    system("cls");
    std::stringstream ss;
    for (int y = 0; y < game->myMapHeight; y++)
    {
        for (int x = 0; x < game->myMapWidth; x++)
        {
            Tile* tile = game->myMap[y][x];
            if (!tile->WasDiscovered())
            {
                ss << " ";
                continue;
            }

            Actor* actor = game->GetActorAt(x, y);
            if (actor && actor->myIsActive)
            {
                ss << actor->GetComponent<RenderComponent>()->m_symbol;
            }
            else
            {
                ss << tile->GetTileSymbol();
            }
        }
        ss << "\n";
    }

    StatsComponent* pStats = game->myPlayer->GetComponent<StatsComponent>();
    InventoryComponent* pInv = game->myPlayer->GetComponent<InventoryComponent>();
    PlayerActor* pPlayer = static_cast<PlayerActor*>(game->myPlayer);

    ss << "--------------------------------------------------\n";
    ss << "HP: " << pStats->getHp() << "/" << pStats->getMaxHp()
        << " | MP: " << pStats->getMana() << "/" << pStats->getMaxMana()
        << " | ATK: " << pStats->getAttack()
        << " | DEF: " << pStats->getDefense()
        << " | Lvl: " << pStats->myLevel << "\n";

    ss << "Potions: " << pInv->potions
        << " | Spell: " << (pPlayer->myCurrentSpell ? pPlayer->myCurrentSpell->myName : "None")
        << " | Cost: " << (pPlayer->myCurrentSpell ? pPlayer->myCurrentSpell->cost : 0) << " MP)\n";

    ss << "--------------------------------------------------\n";
    ss << "Actions: [w/a/s/d] Move/Attack | [p] Potion | [c] Cast | [h] Help | [q] Quit\n";

    for (const std::string& log : game->LogEntry)
    {
        ss << log << "\n";
    }

    std::cout << ss.str();
}

TargetState::TargetState(Game* game, GameState* prev)
    : myPreviousState(prev), myTargetX(game->myPlayer->myX),
    myTargetY(game->myPlayer->myY)
{
    myCaster = game->myPlayer;
    PlayerActor* player = static_cast<PlayerActor*>(game->myPlayer);
    mySpell = player->myCurrentSpell;
}

void TargetState::Update(Game* game)
{
    if (!mySpell)
    {
        MessageBus::GetInstance()->Publish(new Log_Message("No spell selected!"));
        game->ChangeGameState(myPreviousState);
        return;
    }

    StatsComponent* stats = myCaster->GetComponent<StatsComponent>();
    if (stats->getMana() < mySpell->cost)
    {
        MessageBus::GetInstance()->Publish(new Log_Message("Not enough mana!"));
        game->ChangeGameState(myPreviousState);
        return;
    }

    char input = _getch();
    game->m_lastPlayerInput = input; // Update anti-pattern member

    if (input == 'w') myTargetY--;
    else if (input == 's') myTargetY++;
    else if (input == 'a') myTargetX--;
    else if (input == 'd') myTargetX++;
    else if (input == 'q')
    {
        MessageBus::GetInstance()->Publish(new Log_Message("Spell cancelled."));
        game->ChangeGameState(myPreviousState);
    }
    else if (input == 'f')
    {
        ITargetable* target = game->GetActorAt(myTargetX, myTargetY);
        if (target && !target->IsTargetable())
        {
            MessageBus::GetInstance()->Publish(new Log_Message("Cannot target that location!"));
            game->ChangeGameState(myPreviousState);
            return;
        }

        if (mySpell->Cast(game, myCaster, myTargetX, myTargetY))
        {
            stats->setMana(stats->getMana() - mySpell->cost);

            // Manually trigger the AI turn
            for (Actor* actor : game->m_actorList)
            {
                if (actor != game->myPlayer && actor->myIsActive)
                {
                    actor->Update(game);
                }
            }
            game->CheckPlayerVisibility(8);
        }
        game->ChangeGameState(myPreviousState);
    }
}

void TargetState::Draw(Game* game)
{
    myPreviousState->Draw(game);
    printf("\x1B[%d;%dH", myTargetY + 1, myTargetX + 1);
    printf("X");
    printf("\x1B[30;0H");
    printf("Targeting at (%d, %d) with %s. (f to cast, q to cancel)\n",
        myTargetX, myTargetY, mySpell ? mySpell->myName.c_str() : "None");
}

MessageState::MessageState(GameState* prev, std::string msg)
    : myPreviousState(prev), myMessage(msg) {
}

void MessageState::Update(Game* game)
{
    if (_getch()) game->ChangeGameState(myPreviousState);
}

void MessageState::Draw(Game* game)
{
    myPreviousState->Draw(game);
    printf("\n--- %s ---\n(Press any key)\n", myMessage.c_str());
}

void HelpState::Draw(Game* game)
{
    system("cls");
    printf("--- GAME CONTROLS ---\n\n");
    printf("%s\n", myMessage.c_str());
    printf("---------------------\n");
    printf("(Press any key to return)\n");
}
