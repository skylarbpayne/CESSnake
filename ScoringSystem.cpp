/**
    * The ScoringSystem is responsible for keeping track of the score and game time (both can be used as a 'score')
    *
    * Author: Skylar Payne
    * Date: 8/30/2013
    * File: ScoringSystem.cpp
**/

#include "ScoringSystem.h"
#include "Entity.h"
#include "GameScenes.h"
#include <string>

/**
 * @brief ScoringSystem::Update displays the game time and score
 * @param dt the time splice since last frame
 */
void ScoringSystem::Update(unsigned int dt)
{
    sf::Text txt;
    txt.setCharacterSize(36);
    txt.setColor(sf::Color::White);
    txt.setFont(*this->GetFont("resources/Corki-Regular.otf"));

    txt.setString(std::to_string(_Score));
    txt.setPosition(this->GetWindow()->getSize().x / 3, 0);
    this->GetWindow()->draw(txt);

    txt.setString(std::to_string((unsigned int)_GameTime.getElapsedTime().asSeconds()));
    txt.setPosition(this->GetWindow()->getSize().x * 2 / 3, 0);
    this->GetWindow()->draw(txt);
}

/**
 * @brief ScoringSystem::ValidateEntity No entities are validated for this system
 * @param ID the entity to validate
 * @return false always
 */
bool ScoringSystem::ValidateEntity(unsigned int ID)
{
    return false;
}

/**
 * @brief ScoringSystem::OnMessage Checks to see if the head hit a coin, or if the body hit a coin. Updates the score and ends the game.
 * @param msg
 */
void ScoringSystem::OnMessage(CollisionMessage &msg)
{
    Entity* e1 = this->GetEntity(msg.ID1);
    Entity* e2 = this->GetEntity(msg.ID2);

    if(strcmp(e1->GetTag(), "Head") == 0)
    {
        if(strcmp(e2->GetTag(), "Coin") == 0)
        {
            _Score++;
        }

        else if(strcmp(e2->GetTag(), "Body") == 0)
        {
            ChangeSceneMessage sceneMsg;
            sceneMsg.NextScene = new EndScene(_Score, _GameTime.getElapsedTime());
            Emit<ChangeSceneMessage>(sceneMsg);
        }
    }
}
