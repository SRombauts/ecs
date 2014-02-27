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

    ComponentTest1a(float aInitValue = 0.0f) : mValue(aInitValue) {
    }

    float mValue;
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

    ComponentTest2(float aInitValue1 = 0.0f, float aInitValue2 = 0.0f) : mValue1(aInitValue1), mValue2(aInitValue2) {
    }

    float mValue1;
    float mValue2;
};
const ecs::ComponentType ComponentTest2::_mType = 2;
// A third Component
struct ComponentTest3 : public ecs::Component {
    static const ecs::ComponentType _mType;
};
const ecs::ComponentType ComponentTest3::_mType = 3;


// A test System, requiring ComponentTest1a
class SystemTest1 : public ecs::System {
public:
    SystemTest1(ecs::Manager& aManager) :
        ecs::System(aManager) {
        ecs::ComponentTypeSet requiredComponents;
        requiredComponents.insert(ComponentTest1a::_mType);
        setRequiredComponents(std::move(requiredComponents));
    }

    // Update function - for a given matching Entity - specialized.
    virtual void updateEntity(float aElapsedTime, ecs::Entity aEntity) {
        mManager.getComponentStore<ComponentTest1a>().get(aEntity).mValue += aElapsedTime;
    }
};


// A test System, requiring ComponentTest1a and ComponentTest2
class SystemTest2 : public ecs::System {
public:
   SystemTest2(ecs::Manager& aManager) :
        ecs::System(aManager) {
        ecs::ComponentTypeSet requiredComponents;
        requiredComponents.insert(ComponentTest1a::_mType);
        requiredComponents.insert(ComponentTest2::_mType);
        setRequiredComponents(std::move(requiredComponents));
    }

    // Update function - for a given matching Entity - specialized.
    virtual void updateEntity(float, ecs::Entity aEntity) {
        float value = mManager.getComponentStore<ComponentTest1a>().get(aEntity).mValue;
        mManager.getComponentStore<ComponentTest2>().get(aEntity).mValue1 += value;
        mManager.getComponentStore<ComponentTest2>().get(aEntity).mValue2 += value;
    }
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
    ecs::Entity entity1 = manager.createEntity();
    EXPECT_THROW(manager.addComponent(entity1, ComponentTest1a()), std::runtime_error);
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_TRUE(manager.addComponent(entity1, ComponentTest1a()));
    ecs::Entity entityUnknown = 666;
    EXPECT_THROW(manager.addComponent(entityUnknown, ComponentTest1a()), std::runtime_error);
}

// Registering Entity with Systems
TEST(Manager, registerEntityToSystems) {
    ecs::Manager manager;
    EXPECT_TRUE(manager.createComponentStore<ComponentTest1a>());
    EXPECT_TRUE(manager.createComponentStore<ComponentTest2>());

    // Register Systems
    manager.addSystem(ecs::System::Ptr(new SystemTest1(manager)));
    manager.addSystem(ecs::System::Ptr(new SystemTest2(manager)));

    // Register first Entity (matching with System1)
    ecs::Entity entity1 = manager.createEntity();
    EXPECT_TRUE(manager.addComponent(entity1, ComponentTest1a()));
    EXPECT_EQ((size_t)1, manager.registerEntity(entity1));

    // Update Systems
    EXPECT_EQ((size_t)1, manager.updateEntities(0.016667f)); // 16.667ms
    EXPECT_FLOAT_EQ(0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity1).mValue);


    // Register second Entity (matching with System1)
    ecs::Entity entity2 = manager.createEntity();
    EXPECT_TRUE(manager.addComponent(entity2, ComponentTest1a()));
    EXPECT_EQ((size_t)1, manager.registerEntity(entity2));

    // Update Systems
    EXPECT_EQ((size_t)2, manager.updateEntities(0.016667f)); // 16.667ms
    EXPECT_FLOAT_EQ(2*0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity1).mValue);
    EXPECT_FLOAT_EQ(1*0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity2).mValue);


    // Register third Entity (matching with the two System1 & System2)
    ecs::Entity entity3 = manager.createEntity();
    EXPECT_TRUE(manager.addComponent(entity3, ComponentTest1a()));
    EXPECT_TRUE(manager.addComponent(entity3, ComponentTest2()));
    EXPECT_EQ((size_t)2, manager.registerEntity(entity3));

    // Update Systems
    EXPECT_EQ((size_t)4, manager.updateEntities(0.016667f)); // 16.667ms
    EXPECT_FLOAT_EQ(3*0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity1).mValue);
    EXPECT_FLOAT_EQ(2*0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity2).mValue);
    EXPECT_FLOAT_EQ(1*0.016667f, manager.getComponentStore<ComponentTest1a>().get(entity3).mValue);
    EXPECT_FLOAT_EQ(1*0.016667f, manager.getComponentStore<ComponentTest2>().get(entity3).mValue1);
    EXPECT_FLOAT_EQ(1*0.016667f, manager.getComponentStore<ComponentTest2>().get(entity3).mValue2);
}
