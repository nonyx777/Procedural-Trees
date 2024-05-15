#pragma once

#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "../Util/Gizmo.hpp"
#include "../Util/Grid.hpp"
#include "../Globals.hpp"
#include "../Util/Collision.hpp"

class Scene : public GameObject
{
private:
    static Scene *instance;
    std::vector<std::vector<Box>> grid;
    std::vector<Line> branches;
    float angle = 45.f;

private:
    Scene();
    ~Scene();

public:
    // Delete copy constructor and assignment operator to prevent cloning
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    static Scene *getInstance();

    //tree
    void branch(sf::Vector2f base, float length, float angle, float parent_angle);

    void update(float dt) override;
    void update(sf::Vector2f &vec, float dt);
    void render(sf::RenderTarget *target) override;
};