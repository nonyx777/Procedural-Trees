#pragma once

#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "../Util/Gizmo.hpp"
#include "../Util/Grid.hpp"
#include "../Globals.hpp"
#include "../Util/Collision.hpp"
#include <random>

class Scene : public GameObject
{
private:
    static Scene *instance;
    Collision collision;
    std::vector<std::vector<Box>> grid;
    std::vector<Line> branches;
    std::vector<Circle> leafs;
    sf::Vector2f root_base = sf::Vector2f(GLOBAL::window_width / 2.f, GLOBAL::window_height);

    //wind related
    Box windBox = Box(sf::Vector2f(250.f, 150.f), sf::Vector2f(GLOBAL::window_width/2.f, GLOBAL::window_height / 1.5f));
    sf::Vector2f wind_mov; //area which the wind covers(position)
    float wind_count = 0.f; //angle 0 -> 360
    float amplitude = 100.f;
    float frequency = 5.f;

    //branch spring related
    float stiffness = 1.f;

private:
    Scene();
    ~Scene();

public:
    // Delete copy constructor and assignment operator to prevent cloning
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    static Scene *getInstance();

    // tree
    void branch(sf::Vector2f base, float length, float angle, float parent_angle, int parent_index);
    int randomAngle();
    int randomNumberBranch();
    void stickBranchToParent();
    void stickLeafToBranch();

    //branch spring
    void solve(Line &branch);

    void update(float dt) override;
    void update(sf::Vector2f &vec, float dt);
    void render(sf::RenderTarget *target) override;
};