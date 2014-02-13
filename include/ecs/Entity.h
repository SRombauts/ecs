/**
 * @file    Entity.h
 * @ingroup ecs
 * @brief   An ecs::Entity is an Id referencing a game object.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

namespace ecs {

/**
 * @brief   An Entity is a positive Id referencing a game object. Its data are in Components, and logic in Systems.
 * @ingroup ecs
 *
 *  An Entity represents an object, but does not contain any data by its own, nor any logic.
 * It is only defined as a aggregation of Components, processed and updated by associated Systems.
 */
typedef unsigned int Entity;

/**
 * @brief   Entities are strictly positive Ids.
 * @ingroup ecs
 */
static const Entity _invalidEntity = 0;

} // namespace ecs
