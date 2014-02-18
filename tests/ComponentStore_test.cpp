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
    static const ecs::ComponentType _mType;
};
const ecs::ComponentType ComponentTest1::_mType = 1;

// Adding/removing/testing for presence
TEST(ComponentStore, hasHadRemove) {
    ecs::ComponentStore<ComponentTest1> store;
    ecs::Entity entity1 = 1;
    ecs::Entity entity2 = 2;
    EXPECT_FALSE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
    EXPECT_TRUE(store.add(entity1, ComponentTest1()));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
    EXPECT_TRUE(store.add(entity2, ComponentTest1()));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_FALSE(store.add(entity2, ComponentTest1()));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_TRUE(store.remove(entity1));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_FALSE(store.remove(entity1));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_TRUE(store.remove(entity2));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
}
