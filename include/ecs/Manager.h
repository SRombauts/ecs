/**
 * @file    Manager.h
 * @brief   Manage associations of Entities and Components.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "ecs/Entity.h"
#include "ecs/Component.h"
#include "ecs/System.h"

#include <map>
#include <set>
#include <vector>
#include <memory>   // std::shared_ptr

namespace ecs {


/**
 * @brief Manage associations of Entities and Components.
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
    /// Map of all registerd entities with the type of their components
    std::map<Entity, std::set<ComponentType>>               mEntities;
    /// List of all Systems
    std::vector<std::shared_ptr<System>>                    mSystems;
    /// Map of all Components by type and Entity
    std::map<ComponentType, std::map<Entity, Component>>    mComponents;
};


} // namespace ecs
