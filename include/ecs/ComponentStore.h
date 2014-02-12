/**
 * @file    ComponentStore.h
 * @ingroup ecs
 * @brief   A ecs::ComponentStore keep the data of a certain ecs::ComponentType for all concerned Entities.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <ecs/Entity.h>
#include <ecs/Component.h>

#include <unordered_map>

namespace ecs {

/**
 * @brief   A ComponentStore keep all the data of a certain ComponentType for all concerned Entities.
 * @ingroup ecs
 */
typedef std::unordered_map<Entity, Component>   ComponentStore;

} // namespace ecs
