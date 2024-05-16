#include "../../include/Entities/Line.hpp"

Line::Line()
{
    //...
}

Line::Line(sf::Vector2f base, sf::Vector2f direction)
{
    this->base = base;
    this->direction = direction;
}
Line::Line(sf::Vector2f base, sf::Vector2f direction, sf::Vector2f rest_position, int parent_index)
{
    this->base = base;
    this->direction = direction;
    this->rest_position = rest_position;
    this->parent_index = parent_index;
}

void Line::calcMomentOfInertia()
{
    // 1/12mL^2
    float length = Math::_length(this->direction - this->base);
    this->momentOfInertia = (this->mass * (length * length)) / 12.f;
}

void Line::update(float dt)
{
    //...
}

void Line::render(sf::RenderTarget *target)
{
    sf::Vertex line[] = {
        this->base,
        this->direction};
    target->draw(line, 2, sf::Lines);
}