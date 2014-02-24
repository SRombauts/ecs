/**
 * @file    ComponentType.h
 * @ingroup ecs
 * @brief   A ecs::ComponentType is a positive Id referencing a type of ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <set>

namespace ecs {

/**
 * @brief   A ComponentType is a positive Id referencing a type of Component.
 * @ingroup ecs
 */
typedef unsigned int ComponentType;

/**
 * @brief   ComponentType are strictly positive Ids.
 * @ingroup ecs
 */
static const ComponentType _invalidComponentType = 0;

/**
 * @brief   Sorted List (set) of ComponentType (of an Entity, or required by a System)
 * @ingroup ecs
 */
typedef std::set<ComponentType> ComponentTypeSet;

} // namespace ecs
