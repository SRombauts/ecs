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

// Test Manager::createEntity().
TEST(Manager, createEntity) {
    ecs::Manager manager;
    EXPECT_EQ(1, manager.createEntity());
    EXPECT_EQ(2, manager.createEntity());
    EXPECT_EQ(3, manager.createEntity());
}
