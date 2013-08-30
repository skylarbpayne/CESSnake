/**
    * Contains declarations of all GameScenes
    *
    * Author: Skylar Payne
    * Date: 8/28/2013
    * File: GameScenes.cpp
**/

#include "GameScenes.h"

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "BehaviorSystem.h"

#include "SnakeSystem.h"
#include "CoinSystem.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "ColliderComponent.h"
#include "CircleComponent.h"
#include "RectangleComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

bool PlayScene::Load()
{
    sf::Clock clock;
    ISystem* s = nullptr;

    s = new MovementSystem();
    sm.Add(s);

    s = new CollisionSystem();
    sm.Add(s);

    s = new RenderSystem();
    sm.Add(s);

    s = new BehaviorSystem();
    sm.Add(s);

    s = new SnakeSystem();
    sm.Add(s);

    s = new CoinSystem();
    sm.Add(s);

    s = nullptr;

    ef.Register("Position", []() { return new PositionComponent(); });
    ef.Register("Movement", []() { return new MovementComponent(); });
    ef.Register("Collider", []() { return new ColliderComponent(); });
    ef.Register("Circle", []() { return new CircleComponent(); });
    ef.Register("Rectangle", []() { return new RectangleComponent(); });
    ef.Register("Text", []() { return new TextComponent(); });
    ef.Register("Sprite", []() { return new SpriteComponent(); });

    ef.Create("scripts/snake head.lua", 100, 100);

    srand(clock.getElapsedTime().asMicroseconds());
    ef.Create("scripts/coin.lua", rand() % this->GetWindow()->getSize().x, rand() % this->GetWindow()->getSize().y);

    return true;
}

void PlayScene::Update()
{
    sf::Event event;
    while(this->GetWindow()->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            ExitMessage msg;
            msg.ExitStatus = 0;
            Emit<ExitMessage>(msg);
        }
    }

    this->GetWindow()->clear();

    em.Update();
    sm.Update();

    this->GetWindow()->display();
}

void PlayScene::Unload()
{
    rm.Unload();
}
