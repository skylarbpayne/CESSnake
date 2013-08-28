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
#include "ISystem.h"

class SnakeSystem : public ISystem, public IListener<CollisionMessage>
{
private:
    std::list<unsigned int> _Snake;
public:
    SnakeSystem() : ISystem("Snake") { }

    void Update(unsigned int dt) override;
    bool ValidateEntity(unsigned int ID) override;

    void OnMessage(CollisionMessage& msg) override;
};
