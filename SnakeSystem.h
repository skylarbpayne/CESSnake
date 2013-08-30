/**
    * The SnakeSystem controls the movement of and addition of parts to the snake
    *
    * Author: Skylar Payne
    * Date: 8/28/2013
    * File: SnakeSystem.h
**/

#pragma once

#include <list>
#include "ISystem.h"

class SnakeSystem : public ISystem, public IListener<CollisionMessage>
{
private:
    unsigned int _Accumulator;
    bool _NewPart;
    unsigned int _Head;
    sf::Vector2i _HeadDirection;
    std::list<unsigned int> _SnakeBody;
public:
    SnakeSystem();

    void Update(unsigned int dt) override;
    bool ValidateEntity(unsigned int ID) override;

    void OnMessage(CollisionMessage& msg) override;
};
