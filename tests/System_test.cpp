/**
 * @file    SystemStore_test.cpp
 * @ingroup ecs_test
 * @brief   Test of a System.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/System.h>
#include <ecs/Entity.h>

#include <gtest/gtest.h>


// A test System
class SystemTest1 : public ecs::System {
public:
    SystemTest1() :
        ecs::System(ecs::ComponentTypeSet()) {
    }

    // Update function - for a given matching Entity - specialized.
    virtual void updateEntity(float, ecs::Entity) {
    }
};

// Adding/removing/testing for presence
TEST(System, hasHadRemove) {
    SystemTest1 system;
    ecs::Entity entity1 = 1;
    ecs::Entity entity2 = 2;
    // Before any insertion
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
    EXPECT_FALSE(system.unregisterEntity(entity1));
    EXPECT_FALSE(system.unregisterEntity(entity2));
    // Add an Entity
    EXPECT_TRUE(system.registerEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
    // Error: An Entity can be inserted only once for a given Entity
    EXPECT_FALSE(system.registerEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
    // Add the second Entity
    EXPECT_TRUE(system.registerEntity(entity2));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Error: An Entity can be inserted only once for a given Entity
    EXPECT_FALSE(system.registerEntity(entity2));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Remove the first Entity
    EXPECT_TRUE(system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // An Entity can be removed only once for a given Entity
    EXPECT_FALSE(system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Insert again the second Entity
    EXPECT_TRUE(system.registerEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Remove the the first Entity
    EXPECT_TRUE(system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Remove the the second Entity
    EXPECT_TRUE(system.unregisterEntity(entity2));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
}
