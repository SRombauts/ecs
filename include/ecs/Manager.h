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

#include "ecs/Entity.h"
#include "ecs/Component.h"
#include "ecs/System.h"

#include <map>
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
    /// Map of all registered entities with the type of their components
    std::map<Entity, std::set<ComponentType>>               mEntities;
    /// List of all Systems
    std::vector<std::shared_ptr<System>>                    mSystems;
    /// Map of all Components by type and Entity
    std::map<ComponentType, std::map<Entity, Component>>    mComponents;
};


} // namespace ecs


/**
 * @defgroup ecs ecs
 * @brief    A simple C++ Entity-Component-System library.
 */
/**
 * @dir     src
 * @brief   Source directory of the #ecs library.
 * @ingroup ecs
 */
/**
 * @dir     include
 * @brief   Include directory of the #ecs library.
 * @ingroup ecs
 */
