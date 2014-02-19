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

    float x;    // x coordinates
    float y;    // y coordinates
};
// Component to store a 2d speed
struct Speed : public ecs::Component {
    static const ecs::ComponentType _mType;

    float vx;   // speed along x coordinates
    float vy;   // speed along y coordinates
};
// Component to store physical attributes
struct Physic : public ecs::Component {
    static const ecs::ComponentType _mType;

    float weight;   // weight
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

    ecs::Entity ball = manager.createEntity();
// TODO manager.addComponent(ball, Position());

    return (bRet?0:1);
}