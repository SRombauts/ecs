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
 * @brief   Abstract base class for all templated ComponentStore.
 * @ingroup ecs
 */
class ComponentStoreBase {
};

/**
 * @brief   A ComponentStore keep all the data of a certain ComponentType for all concerned Entities.
 * @ingroup ecs
 *
 * @tparam C    A structure derived from Component, of a certain ComponentType
 */
template<typename C>
class ComponentStore : public ComponentStoreBase {
    static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
    static_assert(C::_mType != _invalidComponentType, "C must define a valid non-zero _mType");

public:
    /// Constructor.
    ComponentStore() {
    }
    /// Destructor.
    ~ComponentStore() {
    }

    /**
     * @brief Adding an Entity with a Component of ComponentType
     *
     * @param[in] aEntity       Id of the Entity with the Component to add
     * @param[in] aComponent    Component of ComponentType to add
     *
     * @return true if insertion succedded
     */
    inline bool add(Entity aEntity, C&& aComponent) {
        return mStore.insert(std::make_pair(aEntity, aComponent)).second;
    }

    // TODO Remove

    // TODO Doc
    inline bool has(Entity aEntity) {
        return (mStore.end() != mStore.find(aEntity));
    }

private:
    std::unordered_map<Entity, C>   mStore;
};

} // namespace ecs
