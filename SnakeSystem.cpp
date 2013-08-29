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
#include "IListener.h"
#include <cstring>

#include "Logger.h"

/**
 * @brief SnakeSystem::SnakeSystem Sets default values for the system
 */
SnakeSystem::SnakeSystem() : ISystem("Snake"), _Accumulator(0)
{
    _HeadDirection.x = 1;
    _HeadDirection.y = 0;
    _SnakeBody.clear();
}

/**
 * @brief SnakeSystem::Update updates the direction of the snake and also moves it
 * @param dt the amount of time since last frame
 */
void SnakeSystem::Update(unsigned int dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && _HeadDirection.y != 1)
    {
        _HeadDirection.y = -1;
        _HeadDirection.x = 0;

    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && _HeadDirection.y != -1)
    {
        _HeadDirection.y = 1;
        _HeadDirection.x = 0;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _HeadDirection.x != 1)
    {
        _HeadDirection.x = -1;
        _HeadDirection.y = 0;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _HeadDirection.x != -1)
    {
        _HeadDirection.x = 1;
        _HeadDirection.y = 0;
    }

    _Accumulator += dt;
    if(_Accumulator < sf::milliseconds(333).asMicroseconds())
    {
        return;
    }
    _Accumulator -= sf::milliseconds(333).asMicroseconds();

    MoveEntityMessage msg;
    msg.ID = _Head;

    Entity* head = this->GetEntity(_Head);

    msg.newPosition = head->GetComponent<PositionComponent>("Position")->GetPosition();
    msg.newPosition.x += _HeadDirection.x * 20.f;
    msg.newPosition.y += _HeadDirection.y * 20.f;

    Emit<MoveEntityMessage>(msg);

    if(!_SnakeBody.empty())
    {

        msg.ID = _SnakeBody.front();
        msg.newPosition.x -= _HeadDirection.x * 20.f;
        msg.newPosition.y -= _HeadDirection.y * 20.f;
        Emit<MoveEntityMessage>(msg);

        _SnakeBody.pop_front();
        _SnakeBody.push_back(msg.ID);
    }
}

bool SnakeSystem::ValidateEntity(unsigned int ID)
{
    Entity* e = this->GetEntity(ID);

    if(strcmp(e->GetTag(), "Body") == 0)
    {
        Entity* head = this->GetEntity(_Head);
        sf::Vector2f pos = head->GetComponent<PositionComponent>("Position")->GetPosition();

        if(_HeadDirection.x < 0)
        {
            pos.x += 20;
        }

        else if(_HeadDirection.x > 0)
        {
            pos.x -= 20;
        }

        else if(_HeadDirection.y < 0)
        {
            pos.y += 20;
        }

        else if(_HeadDirection.y > 0)
        {
            pos.y -= 20;
        }

        _SnakeBody.push_front(ID);
        MoveEntityMessage msg;
        msg.ID = ID;
        msg.newPosition = pos;
        Emit<MoveEntityMessage>(msg);
    }

    if(strcmp(e->GetTag(), "Head") == 0)
    {
        _Head = ID;
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
