#include "../../include/Game/Scene.hpp"

Scene *Scene::instance = nullptr;

Scene::Scene()
{
    branch(root_base, 100.f, 30.f, -120.f, -1);
}

Scene::~Scene()
{
    delete instance;
}

Scene *Scene::getInstance()
{
    if (!instance)
        instance = new Scene();

    return instance;
}

void Scene::update(float dt)
{
    for (int i = 1; i < branches.size() - 1; i++)
    {
        branches[i].base = branches[branches[i].parent_index].direction;
    }
}

void Scene::render(sf::RenderTarget *target)
{
    for (Line &b : branches)
        b.render(target);
    for (Circle &l : leafs)
        l.render(target);
}

void Scene::branch(sf::Vector2f base, float length, float angle, float parent_angle, int parent_index)
{
    sf::Vector2f direction = sf::Vector2f(Math::_cos(parent_angle + angle), Math::_sin(parent_angle + angle)) * length;
    direction = base + direction;
    Line root = Line(base, direction, direction, parent_index);
    branches.push_back(root);
    int parent_index_ = branches.size() - 1;

    length *= 0.75f;
    angle = randomAngle();

    if (length > 2.f)
    {
        parent_angle = Math::_atan2(root.direction.y - root.base.y, root.direction.x - root.base.x);
        // right branch
        branch(root.direction, length, angle, parent_angle, parent_index_);
        // left branch
        branch(root.direction, length, -angle, parent_angle, parent_index_);
    }

    Circle leaf = Circle(1.f, root.direction);
    leaf.property.setFillColor(sf::Color::Green);
    leafs.push_back(leaf);
}

int Scene::randomAngle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 45);
    return dis(gen);
}

int Scene::randomNumberBranch()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    return dis(gen);
}