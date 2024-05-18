#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"
#include "Entity.hpp"
#include "../Util/Math.hpp"

class Line : public GameObject, public Rigidbody, public Entity
{
public:
    sf::Vector2f base;
    sf::Vector2f direction;
    float rest_length;
    sf::Vector2f rest_position;
    int parent_index;

    Line();
    Line(sf::Vector2f base, sf::Vector2f direction);
    Line(sf::Vector2f base, sf::Vector2f direction, float rest_length, sf::Vector2f rest_position, int parent_index);

    void calcMomentOfInertia() override;
    void update(float dt) override;
    void render(sf::RenderTarget *target) override;
};