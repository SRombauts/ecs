/**
 * @file    ComponentStore_test.cpp
 * @ingroup ecs_test
 * @brief   Test of a ComponentStore.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/Component.h>
#include <ecs/ComponentStore.h>
#include <ecs/Entity.h>

#include <gtest/gtest.h>

// A test Component
class ComponentTest1 : public ecs::Component {
public:
    static const ecs::ComponentType _mType = 1;
};


// Test ComponentStore::().
TEST(ComponentStore, createEntity) {
    ecs::ComponentStore<ComponentTest1> store;
    ecs::Entity entity1 = 1;
    EXPECT_EQ(false, store.has(entity1));
    EXPECT_EQ(true, store.add(entity1, ComponentTest1()));
    EXPECT_EQ(true, store.has(entity1));
}
