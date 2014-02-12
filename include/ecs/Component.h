/**
 * @file    Component.h
 * @ingroup ecs
 * @brief   A ecs::Component keep the data for one aspect of an ecs::Entity.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <ecs/ComponentType.h>

namespace ecs {

/**
 * @brief   A Component keep the data for one aspect of an Entity.
 * @ingroup ecs
 *
 *  A Component is a data structure that maintain a sub-state of an entity.
 * The state of any Entity can be described by a few standard Components.
 *
 *  Every Component class must derived from this struct and define its own/unique positive #ComponentType.
 */
struct Component {
    /// Default invalid component type
    static const ComponentType _mType = _invalidComponentType;
};

} // namespace ecs
