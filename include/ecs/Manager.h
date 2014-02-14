/**
 * @file    Manager.h
 * @ingroup ecs
 * @brief   Manage associations of ecs::Entity, ecs::Component and ecs::System.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <ecs/Entity.h>
#include <ecs/Component.h>
#include <ecs/ComponentType.h>
#include <ecs/ComponentStore.h>
#include <ecs/System.h>

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <memory>   // std::shared_ptr
#include <cassert>
#include <limits>

/**
 * @brief   A simple C++ Entity-Component-System library.
 * @ingroup ecs
 */
namespace ecs {

/**
 * @brief   Manage associations of Entity, Component and System.
 * @ingroup ecs
 */
class Manager {
public:
    /// Constructor
    Manager();
    /// Destructor
    virtual ~Manager();

    /**
     * @brief   Create a new Entity - simply allocate an new Id.
     *
     * @return  Id of the new Entity
     */
    inline Entity createEntity();

private:
    /// Id of the last created Entity (start with invalid Id 0).
    Entity                                                  mLastEntity;

    /**
     * @brief Hashmap of all registered entities, listing the Type of their Components.
     *
     * This only associates the Id of each Entity with Types of all it Components.
     */
    std::unordered_map<Entity, ComponentTypeSet>            mEntities;

    /**
     * @brief Hashmap of all Components by type and Entity.
     *
     * Store Component of each Entity, by ComponentType.
     */
    std::unordered_map<ComponentType, ComponentStoreBase*>  mComponents;

    /**
     * @brief List of all Systems, ordered by insertion (first created, first executed).
     *
     * If a pointer to a System is inserted twice, it is executed twice.
     */
    std::vector<System::Ptr>                                mSystems;
};


inline Entity Manager::createEntity() {
    assert(mLastEntity < std::numeric_limits<Entity>::max());
    return (++mLastEntity);
}


} // namespace ecs
