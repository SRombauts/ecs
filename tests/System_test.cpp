/**
 * @file    System_test.cpp
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
#include <ecs/Manager.h>

#include "../src/Utils.h" // defines the "override" identifier if needed (gcc < 4.7)

#include <gtest/gtest.h>


// A test System
class SystemTest1 : public ecs::System {
public:
    explicit SystemTest1(ecs::Manager& aManager) :
        ecs::System(aManager) {
    }

    // Update function - for a given matching Entity - specialized.
    virtual void updateEntity(float, ecs::Entity) override {
    }
};

// Adding/removing/testing for presence
TEST(System, hasHadRemove) {
    ecs::Manager manager;
    SystemTest1 system(manager);
    ecs::Entity entity1 = 1;
    ecs::Entity entity2 = 2;
    // Before any insertion
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
    EXPECT_EQ(0U, system.unregisterEntity(entity1));
    EXPECT_EQ(0U, system.unregisterEntity(entity2));
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
    EXPECT_EQ(1U, system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // An Entity can be removed only once for a given Entity
    EXPECT_EQ(0U, system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Insert again the second Entity
    EXPECT_TRUE(system.registerEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Remove the the first Entity
    EXPECT_EQ(1U, system.unregisterEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_TRUE(system.hasEntity(entity2));
    // Remove the the second Entity
    EXPECT_EQ(1U, system.unregisterEntity(entity2));
    EXPECT_FALSE(system.hasEntity(entity1));
    EXPECT_FALSE(system.hasEntity(entity2));
}
