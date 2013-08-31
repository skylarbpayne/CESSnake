/**
    * Contains declarations of all GameScenes
    *
    * Author: Skylar Payne
    * Date: 8/28/2013
    * File: GameScenes.h
**/

#pragma once

#include "IScene.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "ResourceManager.h"
#include "SystemManager.h"
#include "WindowAccessor.h"
#include "IListener.h"

class SplashScene : public IScene, public ResourceAccessor, public WindowAccessor
{
private:
    sf::Clock _Clock;
    sf::Sprite _Splash;
    ResourceManager rm;
public:
    bool Load() override;
    void Update() override;
    void Unload() override;
};

class MainMenuScene : public IScene, public WindowAccessor, public ResourceAccessor
{
private:
    sf::Text _Title;
    sf::Text _Buttons[2];
    sf::RectangleShape _ButtonContainers[2];
    ResourceManager rm;
public:
    bool Load() override;
    void Update() override;
    void Unload() override;
};

class ControlsScene : public IScene, public WindowAccessor, public ResourceAccessor
{
private:
    sf::Sprite _Controls;
    ResourceManager rm;
public:
    bool Load() override;
    void Update() override;
    void Unload() override;
};

class PlayScene : public IScene, public WindowAccessor
{
private:
    EntityManager em;
    EntityFactory ef;
    SystemManager sm;
    ResourceManager rm;
public:
    bool Load() override;
    void Update() override;
    void Unload() override;
};

class EndScene : public IScene, public WindowAccessor, public ResourceAccessor
{
private:
    unsigned int _Score;
    sf::Time _EndTime;
    sf::Text _EndText;
    ResourceManager rm;
public:
    EndScene(unsigned int score, sf::Time time) : _Score(score), _EndTime(time) { }

    bool Load() override;
    void Update() override;
    void Unload() override;
};
