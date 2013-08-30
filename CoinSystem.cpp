/**
    * The CoinSystem handles the destruction and respawn of coins
    *
    * Author: Skylar Payne
    * Date: 8/29/2013
    * File: CoinSystem.h
**/

#include "CoinSystem.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include <cstring>

void CoinSystem::Update(unsigned int dt)
{
}

bool CoinSystem::ValidateEntity(unsigned int ID)
{
    return false;
}

void CoinSystem::OnMessage(CollisionMessage& msg)
{
    Entity* e1 = this->GetEntity(msg.ID1);
    Entity* e2 = this->GetEntity(msg.ID2);

    if(strcmp(e1->GetTag(), "Coin") == 0)
    {
        sf::Vector2f size = e2->GetComponent<ColliderComponent>("Collider")->GetDimensions();
        MoveEntityMessage mmsg;
        mmsg.ID = msg.ID1;
        mmsg.newPosition.x = rand() % (unsigned int)(this->GetWindow()->getSize().x - size.x);
        mmsg.newPosition.y = rand() % (unsigned int)(this->GetWindow()->getSize().y - size.y);
        Emit<MoveEntityMessage>(mmsg);
    }

    else if(strcmp(e2->GetTag(), "Coin") == 0)
    {
        sf::Vector2f size = e2->GetComponent<ColliderComponent>("Collider")->GetDimensions();
        MoveEntityMessage mmsg;
        mmsg.ID = msg.ID2;
        mmsg.newPosition.x = rand() % (unsigned int)(this->GetWindow()->getSize().x - size.x);
        mmsg.newPosition.y = rand() % (unsigned int)(this->GetWindow()->getSize().y - size.y);
        Emit<MoveEntityMessage>(mmsg);
    }
}
