/**
    * The ScoringSystem is responsible for keeping track of the score and game time (both can be used as a 'score')
    *
    * Author: Skylar Payne
    * Date: 8/30/2013
    * File: ScoringSystem.h
**/

#pragma once

#include "ISystem.h"
#include "WindowAccessor.h"
#include "ResourceAccessor.h"

class ScoringSystem : public ISystem, public IListener<CollisionMessage>, public WindowAccessor, public ResourceAccessor
{
private:
    unsigned int _Score;
    sf::Clock _GameTime;
public:
    ScoringSystem() : ISystem("Scoring"), _Score(0) { }

    void Update(unsigned int dt) override;
    bool ValidateEntity(unsigned int ID) override;

    void OnMessage(CollisionMessage& msg) override;
};
