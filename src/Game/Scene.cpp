#include "../../include/Game/Scene.hpp"

Scene *Scene::instance = nullptr;

Scene::Scene()
{
    branch(root_base, 80.f, 30.f, -120.f, -1);

    windBox.property.setFillColor(sf::Color::Transparent);
    windBox.property.setOutlineThickness(1.f);
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
    wind_mov = sf::Vector2f(amplitude * Math::_cos(wind_count * frequency), amplitude * Math::_sin(wind_count * frequency)) + sf::Vector2f(GLOBAL::window_width / 2.f, GLOBAL::window_height / 1.5f);
    windBox.property.setPosition(wind_mov);

    stickBranchToParent();
    stickLeafToBranch();

    for(Line &b : branches)
        solve(b);

    if (wind_count < 360.f)
        wind_count++;
    else
        wind_count = 0.f;
}

void Scene::render(sf::RenderTarget *target)
{
    for (Line &b : branches)
        b.render(target);
    for (Circle &l : leafs)
        l.render(target);

    // windBox.render(target);
}

void Scene::branch(sf::Vector2f base, float length, float angle, float parent_angle, int parent_index)
{
    sf::Vector2f direction = sf::Vector2f(Math::_cos(parent_angle + angle), Math::_sin(parent_angle + angle)) * length;
    direction = base + direction;
    float rest_length_tempo = Math::_length(direction - base);
    Line root = Line(base, direction, rest_length_tempo, direction, parent_index);
    root.mass = length;

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

    else
    {
        Circle leaf = Circle(1.f, root.direction);
        leaf.property.setFillColor(sf::Color::Green);
        leaf.branch_index = parent_index_;
        leafs.push_back(leaf);
    }
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

void Scene::stickBranchToParent()
{
    for (int i = 1; i < branches.size() - 1; i++)
    {
        if (collision._boxPointCollide(windBox, branches[i].base))
            branches[i].direction += sf::Vector2f(2.f, 0.1f) / branches[i].mass;
        branches[i].base = branches[branches[i].parent_index].direction;
    }
}

void Scene::stickLeafToBranch()
{
    for (Circle &l : this->leafs)
    {
        l.property.setPosition(branches[l.branch_index].direction);
    }
}

void Scene::solve(Line &branch)
{
    sf::Vector2f displace = branch.direction - branch.base;
    float distance = Math::_length(displace);

    sf::Vector2f unit = Math::_normalize(displace);

    sf::Vector2f force = (stiffness * (distance - branch.rest_length)) * unit;

    branch.direction += -force;
    sf::Vector2f vel = branch.rest_position - branch.direction;
    branch.direction += vel * 0.05f;
}