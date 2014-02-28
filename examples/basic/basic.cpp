/**
 * @file    basic.cpp
 * @ingroup ecs_basic_example
 * @brief   Basic example of the Entity-Component-System manager.
 *
 * Basic example moving balls with simple collision detection.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/Component.h>
#include <ecs/ComponentStore.h>
#include <ecs/Manager.h>

#include <iostream>

#include <cstdlib> // srand, rand

// Component to store a 2d position
struct Position : public ecs::Component {
    static const ecs::ComponentType _mType;

    float x;    // x coordinates in meters
    float y;    // y coordinates in meters

    // Initialize coordinates
    Position(float aX, float aY) : x(aX), y(aY) {
    }
};

// Component to store a 2d speed
struct Speed : public ecs::Component {
    static const ecs::ComponentType _mType;

    float vx;   // speed along x coordinates in m/s
    float vy;   // speed along y coordinates in m/s

    // Initialize speed coordinates
    Speed(float aX, float aY) : vx(aX), vy(aY) {
    }
};

// Component to detect collisions
struct Collidable : public ecs::Component {
    static const ecs::ComponentType _mType;

    float radius;

    // Initialize radius
    Collidable(float aRadius) : radius(aRadius) {
    }
};

// Component to detect restrict the play area
struct Area : public ecs::Component {
    static const ecs::ComponentType _mType;

    float left;
    float right;
    float top;
    float bottom;

    // Initialize area
    Area(float aLeft, float aRight, float aTop, float aDown) :
        left(aLeft), right(aRight), top(aTop), bottom(aDown) {
    }
};

const ecs::ComponentType Position::_mType   = 1;
const ecs::ComponentType Speed::_mType      = 2;
const ecs::ComponentType Collidable::_mType = 3;
const ecs::ComponentType Area::_mType       = 4;


// A System to update Position with Speed data
class SystemMove : public ecs::System {
public:
    SystemMove(ecs::Manager& aManager) :
        ecs::System(aManager) {
        ecs::ComponentTypeSet requiredComponents;
        requiredComponents.insert(Position::_mType);
        requiredComponents.insert(Speed::_mType);
        setRequiredComponents(std::move(requiredComponents));
    }

    // Update Position with Speed data and elapsed time
    virtual void updateEntity(float aElapsedTime, ecs::Entity aEntity) {
        const Speed& speed = mManager.getComponentStore<Speed>().get(aEntity);
        Position& position = mManager.getComponentStore<Position>().get(aEntity);

        position.x += (speed.vx) * aElapsedTime;
        position.y += (speed.vy) * aElapsedTime;
    }
};

// A System to update Speed and Position with collision detection
class SystemCollide : public ecs::System {
public:
    SystemCollide(ecs::Manager& aManager) :
        ecs::System(aManager) {
        ecs::ComponentTypeSet requiredComponents;
        requiredComponents.insert(Position::_mType);
        requiredComponents.insert(Speed::_mType);
        requiredComponents.insert(Collidable::_mType);
        setRequiredComponents(std::move(requiredComponents));
    }

    // Update Speed with collision detection
    virtual void updateEntity(float aElapsedTime, ecs::Entity aEntity) {
        Speed& speed = mManager.getComponentStore<Speed>().get(aEntity);
        Position& position = mManager.getComponentStore<Position>().get(aEntity);
        const Collidable& collidable = mManager.getComponentStore<Collidable>().get(aEntity);

        // Detect collisions with limits of the Area
        const Area& area = mManager.getComponentStore<Area>().getComponents().begin()->second;
        if (position.x >= area.right) {
            position.x -= (position.x - area.right);
            speed.vx = -speed.vx;
            std::cout << "Entity #" << aEntity << " Collision(right): (" << position.x << ", " << position.y << ")\n";
        } else if (position.x <= area.left) {
            position.x += (area.left - position.x);
            speed.vx = -speed.vx;
            std::cout << "Entity #" << aEntity << " Collision(left): (" << position.x << ", " << position.y << ")\n";
        }
        if (position.y >= area.top) {
            position.y -= (position.y - area.top);
            speed.vy = -speed.vy;
            std::cout << "Entity #" << aEntity << " Collision(top): (" << position.x << ", " << position.y << ")\n";
        } else if (position.y <= area.bottom) {
            position.y += (area.bottom - position.y);
            speed.vy = -speed.vy;
            std::cout << "Entity #" << aEntity << " Collision(bottom): (" << position.x << ", " << position.y << ")\n";
        }

        // TODO Detect collision with other entities
    }
};

// A System to "draw" (print) the Entity
class SystemDraw : public ecs::System {
public:
    SystemDraw(ecs::Manager& aManager) :
        ecs::System(aManager) {
        ecs::ComponentTypeSet requiredComponents;
        requiredComponents.insert(Position::_mType);
        setRequiredComponents(std::move(requiredComponents));
    }

    // "Draw" (print) the Entity
    virtual void updateEntity(float aElapsedTime, ecs::Entity aEntity) {
        const Position& position = mManager.getComponentStore<Position>().get(aEntity);
        std::cout << "Entity #" << aEntity << " (" << position.x << ", " << position.y << ")\n";
    }
};


/**
 * Basic example moving balls with simple collision detection.
 */
int main() {
    bool bRet = true;
    ecs::Manager manager;

    // NOTE : for testing purpose only:
    std::cout << "sizeof(manager)=" << sizeof(manager) << std::endl;
    std::cout << "sizeof(Position)=" << sizeof(Position) << std::endl;
    std::cout << "sizeof(Speed)=" << sizeof(Speed) << std::endl;
    std::cout << "sizeof(Collidable)=" << sizeof(Collidable) << std::endl;
    std::cout << "sizeof(Area)=" << sizeof(Area) << std::endl;

    // Create all ComponentStore
    bRet &= manager.createComponentStore<Position>();
    bRet &= manager.createComponentStore<Speed>();
    bRet &= manager.createComponentStore<Collidable>();
    bRet &= manager.createComponentStore<Area>();

    std::cout << "sizeof(storePosition)=" << sizeof(manager.getComponentStore<Position>()) << std::endl;
    std::cout << "sizeof(storeSpeed)=" << sizeof(manager.getComponentStore<Speed>()) << std::endl;
    std::cout << "sizeof(storeCollidable)=" << sizeof(manager.getComponentStore<Collidable>()) << std::endl;
    std::cout << "sizeof(storeArea)=" << sizeof(manager.getComponentStore<Area>()) << std::endl;

    // Create the Systems
    manager.addSystem(ecs::System::Ptr(new SystemMove(manager)));
    manager.addSystem(ecs::System::Ptr(new SystemCollide(manager)));
    manager.addSystem(ecs::System::Ptr(new SystemDraw(manager)));

    // Create an Area Entity
    ecs::Entity area = manager.createEntity();
    bRet &= manager.addComponent(area, Area(-1.0f, 1.0f, 1.0f, -1.0f));
    manager.registerEntity(area);

    // Create a few Entities
    size_t nbRegistered = 0;
    for (size_t i = 0; i < 2; ++i) {
        // Create an Entity, with its Components, and register it to appropriate Systems
        ecs::Entity ball = manager.createEntity();
        bRet &= manager.addComponent(ball, Position(0.0f, 0.0f));   // spawn at origin
        bRet &= manager.addComponent(ball, Speed(10.0f*(rand()-RAND_MAX/2)/RAND_MAX,
                                                 10.0f*(rand()-RAND_MAX/2)/RAND_MAX));
        bRet &= manager.addComponent(ball, Collidable(0.05f));      // 10cm wide ball
        nbRegistered += manager.registerEntity(ball);
    }
    std::cout << "Created " << nbRegistered << " Entities\n";

    // Update them a few time, emulating a 30fps update
    size_t nbUpdated = 0;
    for (size_t i = 0; i < 20; ++i) {
        nbUpdated += manager.updateEntities(0.032f); // 32ms (30fps)
    }
    std::cout << "Updated them " << nbUpdated << " time\n";

    std::cout << "Done (ret=" << bRet << ")\n";
    return (bRet?0:1);
}
