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
#include "ScoringSystem.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "ColliderComponent.h"
#include "CircleComponent.h"
#include "RectangleComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

#include "IListener.h"

/**
 * @brief SplashScene::Load loads the splash scene texture
 * @return true if everything loaded properly
 */
bool SplashScene::Load()
{
    rm.AddTexture("resources/splash.png");
    _Splash.setTexture(*this->GetTexture("resources/splash.png"));
    return true;
}

/**
 * @brief SplashScene::Update slowly fades the splash scene out
 */
void SplashScene::Update()
{
    sf::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;

    color.a = 255 - _Clock.getElapsedTime().asSeconds() * (255 / 3);

    _Splash.setColor(color);

    this->GetWindow()->clear();
    this->GetWindow()->draw(_Splash);
    this->GetWindow()->display();

    if(color.a == 0)
    {
        ChangeSceneMessage msg;
        msg.NextScene = new MainMenuScene();
        Emit<ChangeSceneMessage>(msg);
    }
}

/**
 * @brief SplashScene::Unload unloads all allocated resources
 */
void SplashScene::Unload()
{
    rm.Unload();
}

/**
 * @brief MainMenuScene::Load Loads all of the buttons
 * @return true if everything loaded properly
 */
bool MainMenuScene::Load()
{
    rm.AddFont("resources/Corki-Regular.otf");

    _Title.setString("Snake");
    _Title.setFont(*this->GetFont("resources/Corki-Regular.otf"));
    _Title.setCharacterSize(36);
    _Title.setColor(sf::Color::White);
    _Title.setPosition((this->GetWindow()->getSize().x - _Title.getGlobalBounds().width) / 2, 60);

    _Buttons[0].setString("Play (1-P)");
    _Buttons[1].setString("Controls");

    for(unsigned int i = 0; i < 2; i++)
    {
        _Buttons[i].setFont(*this->GetFont("resources/Corki-Regular.otf"));
        _Buttons[i].setCharacterSize(24);
        _Buttons[i].setColor(sf::Color::White);
        _Buttons[i].setPosition((this->GetWindow()->getSize().x - _Buttons[i].getGlobalBounds().width) / 2, 175 * i + 250);

        _ButtonContainers[i].setFillColor(sf::Color::Blue);
        _ButtonContainers[i].setPosition(_Buttons[i].getPosition().x - 10, _Buttons[i].getPosition().y - 10);
        sf::Vector2f size;
        size.x = _Buttons[i].getGlobalBounds().width + 20;
        size.y = _Buttons[i].getGlobalBounds().height + 20;
        _ButtonContainers[i].setSize(size);
    }



    return true;
}

/**
 * @brief MainMenuScene::Update checks for any button presses and renders the buttons
 */
void MainMenuScene::Update()
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

        else if(event.type == sf::Event::MouseMoved)
        {
            for(unsigned int i = 0; i < 2; i++)
            {
                if(_ButtonContainers[i].getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                {
                    _ButtonContainers[i].setFillColor(sf::Color::Red);
                }

                else
                {
                    _ButtonContainers[i].setFillColor(sf::Color::Blue);
                }
            }
        }

        else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            for(unsigned int i = 0; i < 2; i++)
            {
                if(_ButtonContainers[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    ChangeSceneMessage msg;

                    switch(i)
                    {
                    case 0:
                        msg.NextScene = new PlayScene();
                        break;
                    case 1:
                        msg.NextScene = new ControlsScene();
                        break;
                    }

                    Emit<ChangeSceneMessage>(msg);
                }
            }
        }
    }

    this->GetWindow()->clear();

    this->GetWindow()->draw(_Title);
    for(unsigned int i = 0; i < 2; i++)
    {
        this->GetWindow()->draw(_ButtonContainers[i]);
        this->GetWindow()->draw(_Buttons[i]);
    }

    this->GetWindow()->display();
}


/**
 * @brief MainMenuScene::Unload unloads all allocated resources
 */
void MainMenuScene::Unload()
{
    rm.Unload();
}


/**
 * @brief ControlsScene::Load loads the controls texture
 * @return true if everything loaded correctly, false otherwise
 */
bool ControlsScene::Load()
{
    rm.AddTexture("resources/controls.png");
    _Controls.setTexture(*this->GetTexture("resources/controls.png"));
    return true;
}

/**
 * @brief ControlsScene::Update checks to see if escape was pressed
 */
void ControlsScene::Update()
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

        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                ChangeSceneMessage msg;
                msg.NextScene = new MainMenuScene();
                Emit<ChangeSceneMessage>(msg);
            }
        }
    }

    this->GetWindow()->clear();
    this->GetWindow()->draw(_Controls);
    this->GetWindow()->display();
}

/**
 * @brief ControlsScene::Unload unloads all allocated resources
 */
void ControlsScene::Unload()
{
    rm.Unload();
}


/**
 * @brief PlayScene::Load loads all game systems, entities, and resources
 * @return true if everything loaded properly, false otherwise
 */
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

    s = new ScoringSystem();
    sm.Add(s);

    s = nullptr;

    rm.AddFont("resources/Corki-Regular.otf");

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

/**
 * @brief PlayScene::Update updates all game systems
 */
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

        else if(event.key.code == sf::Keyboard::Escape)
        {
            ChangeSceneMessage msg;
            msg.NextScene = new MainMenuScene();
            Emit<ChangeSceneMessage>(msg);
        }
    }

    this->GetWindow()->clear();

    em.Update();
    sm.Update();

    this->GetWindow()->display();
}

/**
 * @brief PlayScene::Unload unloads all game resources
 */
void PlayScene::Unload()
{
    rm.Unload();
}

/**
 * @brief EndScene::Load sets up the ending message
 * @return true if loaded properly, false otherwise
 */
bool EndScene::Load()
{
    rm.AddFont("resources/Corki-Regular.otf");

    _EndText.setFont(*this->GetFont("resources/Corki-Regular.otf"));
    _EndText.setCharacterSize(32);
    _EndText.setColor(sf::Color::White);
    _EndText.setString("Your snake was " + std::to_string(_Score) + " pieces long and stayed alive for "
                       + std::to_string((unsigned int)_EndTime.asSeconds()) + " seconds.");
    _EndText.setPosition((this->GetWindow()->getSize().x - _EndText.getGlobalBounds().width) / 2,
                         (this->GetWindow()->getSize().y - _EndText.getGlobalBounds().height) / 2);
    return true;
}

void EndScene::Update()
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

            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    ChangeSceneMessage msg;
                    msg.NextScene = new MainMenuScene();
                    Emit<ChangeSceneMessage>(msg);
                }
            }
        }

        this->GetWindow()->clear();
        this->GetWindow()->draw(_EndText);
        this->GetWindow()->display();
}

/**
 * @brief EndScene::Unload unloads all loaded assets
 */
void EndScene::Unload()
{
    rm.Unload();
}
