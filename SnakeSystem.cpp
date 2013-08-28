/**
    * The SnakeSystem controls the movement of and addition of parts to the snake
    *
    * Author: Skylar Payne
    * Date: 8/28/2013
    * File: SnakeSystem.cpp
**/

#include "SnakeSystem.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "IListener.h"
#include <cstring>

void SnakeSystem::Update(unsigned int dt)
{
    std::list<unsigned int>::iterator it = _Snake.begin();
    Entity* e1 = this->GetEntity(*it);
    Entity* e2 = nullptr;
    PushEntityMessage msg;

    for(++it; it != _Snake.end(); it++)
    {
        e2 = this->GetEntity(*it);
        msg.ID = *it;
        sf::Vector2f pos1 = e1->GetComponent<PositionComponent>("Position")->GetPosition();
        sf::Vector2f pos2 = e2->GetComponent<PositionComponent>("Position")->GetPosition();
        msg.newVelocity = pos1 - pos2;

        if(fabs(msg.newVelocity.x) > fabs(msg.newVelocity.y))
        {
            msg.newVelocity.y = 0;
            msg.newVelocity.x /= abs(msg.newVelocity.x);
            msg.newVelocity.x *= 5;
        }

        else
        {
            msg.newVelocity.x = 0;
            msg.newVelocity.y /= abs(msg.newVelocity.y);
            msg.newVelocity.y *= 5;
        }

        Emit<PushEntityMessage>(msg);
    }
}

bool SnakeSystem::ValidateEntity(unsigned int ID)
{
    Entity* e = this->GetEntity(ID);
    if(strcmp(e->GetTag(), "Body") == 0 || strcmp(e->GetTag(), "Head") == 0)
    {
        if(_Snake.empty())
        {
            _Snake.push_back(ID);
            return false;
        }

        Entity* tail = this->GetEntity(_Snake.back());
        sf::Vector2f pos = tail->GetComponent<PositionComponent>("Position")->GetPosition();
        sf::Vector2f const& vel = tail->GetComponent<MovementComponent>("Movement")->GetVelocity();

        if(vel.x < 0)
        {
            pos.x += 20;
        }

        else if(vel.x > 0)
        {
            pos.x -= 20;
        }

        else if(vel.y < 0)
        {
            pos.y += 20;
        }

        else if(vel.y > 0)
        {
            pos.y -= 20;
        }

        _Snake.push_back(ID);
        MoveEntityMessage msg;
        msg.ID = ID;
        msg.newPosition = pos;
        Emit<MoveEntityMessage>(msg);
    }

    return false;
}

void SnakeSystem::OnMessage(CollisionMessage &msg)
{
    Entity* c = this->GetEntity(msg.ID2);
    if(strcmp(c->GetTag(), "Coin") == 0)
    {
        CreateEntityMessage cmsg;
        cmsg.script = "scripts/snake body.lua";
        Emit<CreateEntityMessage>(cmsg);

        DestroyEntityMessage dmsg;
        dmsg.ID = msg.ID2;
        Emit<DestroyEntityMessage>(dmsg);
    }
}
