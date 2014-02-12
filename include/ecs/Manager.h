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
    /**
     * @brief Constructor
     */
    Manager();
    /**
     * @brief Destructor
     */
    virtual ~Manager();

private:
    /**
     * @brief Hashmap of all registered entities, listing the Type of their Components.
     *
     * This only associates the ID of each Entity with Types of all it Components.
     */
    std::unordered_map<Entity, ComponentTypeSet>        mEntities;

    /**
     * @brief Hashmap of all Components by type and Entity.
     *
     * Store Component of each Entity, by ComponentType.
     */
    std::unordered_map<ComponentType, ComponentStore>   mComponents;

    /**
     * @brief List of all Systems, ordered by insertion (first created, first executed).
     *
     * If a pointer to a System is inserted twice, it is executed twice.
     */
    std::vector<System::Ptr>                            mSystems;
};

} // namespace ecs
