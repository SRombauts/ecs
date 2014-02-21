/**
 * @file    Manager_test.cpp
 * @ingroup ecs_test
 * @brief   Test of the Entity-Component-System manager.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/Manager.h>

#include <gtest/gtest.h>

// A Test Component
struct ComponentTest1a : public ecs::Component {
    static const ecs::ComponentType _mType;
};
const ecs::ComponentType ComponentTest1a::_mType = 1;
// Erroneous component (same type as Test1a)
struct ComponentTest1b : public ecs::Component {
    static const ecs::ComponentType _mType;
};
const ecs::ComponentType ComponentTest1b::_mType = 1; // this is an error
// A second Component
struct ComponentTest2 : public ecs::Component {
    static const ecs::ComponentType _mType;
};
const ecs::ComponentType ComponentTest2::_mType = 2;

// Creating entities
TEST(Manager, createEntity) {
    ecs::Manager manager;
    EXPECT_EQ((ecs::Entity)1, manager.createEntity());
    EXPECT_EQ((ecs::Entity)2, manager.createEntity());
    EXPECT_EQ((ecs::Entity)3, manager.createEntity());
}

// Creating Component stores
TEST(Manager, createComponentStore) {
    ecs::Manager manager;
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest1b>());
    EXPECT_TRUE(manager.createComponentStore<ComponentTest2>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest2>());
}

// Finding Component stores
TEST(Manager, getComponentStore) {
    ecs::Manager manager;
    EXPECT_THROW(manager.getComponentStore<ComponentTest1a>(), std::runtime_error);
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_NO_THROW(manager.getComponentStore<ComponentTest1a>());
    EXPECT_THROW(manager.getComponentStore<ComponentTest2>(), std::runtime_error);
    EXPECT_TRUE(manager.createComponentStore<ComponentTest2>());
    EXPECT_NO_THROW(manager.getComponentStore<ComponentTest2>());
}

// Adding Component to stores
TEST(Manager, addComponent) {
    ecs::Manager manager;
    ecs::Entity entity1 = 1;
    EXPECT_THROW(manager.addComponent<ComponentTest1a>(entity1, ComponentTest1a()), std::runtime_error);
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_TRUE(manager.addComponent<ComponentTest1a>(entity1, ComponentTest1a()));
}
