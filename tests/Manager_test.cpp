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

// Test Components
class ComponentTest1 : public ecs::Component {
public:
    static const ecs::ComponentType _mType = 1;
};
class ComponentTest1b : public ecs::Component {
public:
    static const ecs::ComponentType _mType = 1;
};
class ComponentTest2 : public ecs::Component {
public:
    static const ecs::ComponentType _mType = 2;
};

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
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest1>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest1b>());
    EXPECT_TRUE(manager.createComponentStore<ComponentTest2>());
    EXPECT_FALSE(manager.createComponentStore<ComponentTest2>());
}