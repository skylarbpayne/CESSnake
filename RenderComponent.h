/** Render Component Header
 *
 * @author      Caleb Geiger
 * Created:     8-2-2013
 * Source File:  RenderComponent.h
 */

#pragma once

#include "IComponent.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class RenderComponent : public IComponent
{
friend class RenderSystem;
private:
    CircleShape _Circle;
public:
    RenderComponent() : IComponent("Render") { _Circle.setRadius(40); _Circle.setFillColor(sf::Color::Red); }
    CircleShape const& GetShape()
    {
        return _Circle;
    }
    void setRadius(float radius){
        _Circle.setRadius(radius);
    }
    void setColor(Color c){
        _Circle.setFillColor(c);
    }
    float getRadius(){
        return _Circle.getRadius();
    }
    Color getColor(){
        return _Circle.getFillColor();
    }

};
