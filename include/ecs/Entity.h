/**
 * @file    Entity.h
 * @ingroup ecs
 * @brief   An ecs::Entity is an ID referencing a game object.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

namespace ecs {


/**
 * @brief An Entity is a positive ID referencing a game object.
 * @ingroup ecs
 *
 *  Its data are in Components, and game logic is in associated Systems.
 */
typedef unsigned int Entity;

/// Entities are strictly positive IDs.
static const Entity _invalidEntity = 0;


} // namespace ecs
