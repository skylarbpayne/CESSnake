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
