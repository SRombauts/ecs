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
struct ComponentTest1 : public ecs::Component {
    static const ecs::ComponentType _mType;

    // A simple test constructor, init the test value
    ComponentTest1(int a) : m(a) {
    }

    int m; // A simple test value
};
const ecs::ComponentType ComponentTest1::_mType = 1;

// Adding/removing/testing for presence
TEST(ComponentStore, hasHadRemove) {
    ecs::ComponentStore<ComponentTest1> store;
    ecs::Entity entity1 = 1;
    ecs::Entity entity2 = 2;
    // Before any insertion
    EXPECT_FALSE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
    EXPECT_THROW(store.get(entity1), std::out_of_range);
    EXPECT_THROW(store.get(entity2), std::out_of_range);
    EXPECT_FALSE(store.remove(entity1));
    EXPECT_FALSE(store.remove(entity2));
    // Add a component to the first Entity (using a temporary rvalue)
    EXPECT_TRUE(store.add(entity1, ComponentTest1(123)));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
    EXPECT_NO_THROW(store.get(entity1));
    EXPECT_EQ(123, store.get(entity1).m);
    EXPECT_THROW(store.get(entity2), std::out_of_range);
    // Error: A component can be inserted only once for a given Entity
    EXPECT_FALSE(store.add(entity1, ComponentTest1(666)));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
    // Add a component to the second Entity (using std::move to get the requierd rvalue)
    ComponentTest1 component2(456);
    EXPECT_TRUE(store.add(entity2, std::move(component2)));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_NO_THROW(store.get(entity1));
    EXPECT_EQ(123, store.get(entity1).m);
    EXPECT_NO_THROW(store.get(entity2));
    EXPECT_EQ(456, store.get(entity2).m);
    // Error: A component can be inserted only once for a given Entity
    EXPECT_FALSE(store.add(entity2, ComponentTest1(666)));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    // Remove the component of the first Entity
    EXPECT_TRUE(store.remove(entity1));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    // A component can be removed only once for a given Entity
    EXPECT_FALSE(store.remove(entity1));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    // Insert a new component to the second Entity
    EXPECT_TRUE(store.add(entity1, ComponentTest1(789)));
    EXPECT_TRUE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    EXPECT_NO_THROW(store.get(entity1));
    EXPECT_EQ(789, store.get(entity1).m);
    EXPECT_NO_THROW(store.get(entity2));
    EXPECT_EQ(456, store.get(entity2).m);
    // Extract the component of the first Entity
    ComponentTest1 component3 = store.extract(entity1);
    EXPECT_EQ(789, component3.m);
    EXPECT_FALSE(store.has(entity1));
    EXPECT_TRUE(store.has(entity2));
    // Remove the component of the second Entity
    EXPECT_TRUE(store.remove(entity2));
    EXPECT_FALSE(store.has(entity1));
    EXPECT_FALSE(store.has(entity2));
}
