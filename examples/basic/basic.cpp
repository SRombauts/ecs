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

    float weight;   // weight in kgs

    // Initialize weight
    Physic(float aWeight) : weight(aWeight) {
    }
};

const ecs::ComponentType Position::_mType   = 1;
const ecs::ComponentType Speed::_mType      = 2;
const ecs::ComponentType Physic::_mType     = 3;


int main() {
    bool bRet = true;
    ecs::Manager manager;

    std::cout << "sizeof(manager)=" << sizeof(manager) << std::endl;
    std::cout << "sizeof(Position)=" << sizeof(Position) << std::endl;
    std::cout << "sizeof(Speed)=" << sizeof(Speed) << std::endl;
    std::cout << "sizeof(Physic)=" << sizeof(Physic) << std::endl;
    // TODO for testing purpose only:
    ecs::ComponentStore<Position> storePosition;
    ecs::ComponentStore<Speed> storeSpeed;
    ecs::ComponentStore<Physic> storePhysic;
    std::cout << "sizeof(storePosition)=" << sizeof(storePosition) << std::endl;
    std::cout << "sizeof(storeSpeed)=" << sizeof(storeSpeed) << std::endl;
    std::cout << "sizeof(storePhysic)=" << sizeof(storePhysic) << std::endl;

    bRet &= manager.createComponentStore<Position>();
    bRet &= manager.createComponentStore<Speed>();
    bRet &= manager.createComponentStore<Physic>();

    ecs::Entity ball1 = manager.createEntity();
    bRet &= manager.addComponent(ball1, Position(123.0f, 456.0f));
    bRet &= manager.addComponent(ball1, Speed(1.0f, 0.0f));
    bRet &= manager.addComponent(ball1, Physic(5.0f));
    // TODO tell the manager that the entity is complete/can be registered to appropriate Systems

    return (bRet?0:1);
}