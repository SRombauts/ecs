/**
 * @file    basic.cpp
 * @ingroup ecs_basic_example
 * @brief   Basic example of the Entity-Component-System manager.
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

// Component to store physical attributes
struct Physic : public ecs::Component {
    static const ecs::ComponentType _mType;

    float mass;   // mass in kilograms

    // Initialize mass
    Physic(float aMass) : mass(aMass) {
    }
};

const ecs::ComponentType Position::_mType   = 1;
const ecs::ComponentType Speed::_mType      = 2;
const ecs::ComponentType Physic::_mType     = 3;


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


int main() {
    bool bRet = true;
    ecs::Manager manager;

    // NOTE : for testing purpose only:
    std::cout << "sizeof(manager)=" << sizeof(manager) << std::endl;
    std::cout << "sizeof(Position)=" << sizeof(Position) << std::endl;
    std::cout << "sizeof(Speed)=" << sizeof(Speed) << std::endl;
    std::cout << "sizeof(Physic)=" << sizeof(Physic) << std::endl;

    // Create all ComponentStore
    bRet &= manager.createComponentStore<Position>();
    bRet &= manager.createComponentStore<Speed>();
    bRet &= manager.createComponentStore<Physic>();

    std::cout << "sizeof(storePosition)=" << sizeof(manager.getComponentStore<Position>()) << std::endl;
    std::cout << "sizeof(storeSpeed)=" << sizeof(manager.getComponentStore<Speed>()) << std::endl;
    std::cout << "sizeof(storePhysic)=" << sizeof(manager.getComponentStore<Physic>()) << std::endl;

    // Create the System
    manager.addSystem(ecs::System::Ptr(new SystemMove(manager)));

    // Create a thousand Entities
    size_t nbRegistered = 0;
    for (size_t i = 0; i < 1000; ++i) {
        // Create an Entity, with its Components, and register it to appropriate Systems
        ecs::Entity ball = manager.createEntity();
        bRet &= manager.addComponent(ball, Position(123.0f, 456.0f));
        bRet &= manager.addComponent(ball, Speed(1.0f, 0.0f));
        bRet &= manager.addComponent(ball, Physic(5.0f));
        nbRegistered += manager.registerEntity(ball);
    }
    std::cout << "Created " << nbRegistered << " Entities\n";

    // Update them a thousand time, emulating a 60fps update
    size_t nbUpdated = 0;
    for (size_t i = 0; i < 1000; ++i) {
        nbUpdated += manager.updateEntities(0.016667f); // 16.667ms
    }
    std::cout << "Updated them " << nbUpdated << " time\n";

    std::cout << "Done (ret=" << bRet << ")\n";
    return (bRet?0:1);
}
