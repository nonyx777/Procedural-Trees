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
    std::vector<std::vector<Box>> grid;
    std::vector<Line> branches;
    std::vector<Circle> leafs;
    sf::Vector2f root_base = sf::Vector2f(GLOBAL::window_width / 2.f, GLOBAL::window_height);

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

    void update(float dt) override;
    void update(sf::Vector2f &vec, float dt);
    void render(sf::RenderTarget *target) override;
};