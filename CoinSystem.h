/**
    * The CoinSystem handles the destruction and respawn of coins
    *
    * Author: Skylar Payne
    * Date: 8/29/2013
    * File: CoinSystem.h
**/

#pragma once

#include "ISystem.h"
#include "WindowAccessor.h"

class CoinSystem : public ISystem, public WindowAccessor, public IListener<CollisionMessage>
{
public:
    CoinSystem() : ISystem("Coin") { }

    void Update(unsigned int dt) override;
    bool ValidateEntity(unsigned int ID) override;

    void OnMessage(CollisionMessage& msg) override;
};
