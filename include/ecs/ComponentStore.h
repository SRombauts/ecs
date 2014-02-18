/**
 * @file    ComponentStore.h
 * @ingroup ecs
 * @brief   A ecs::ComponentStore keep the data of a certain type of ecs::Component for all concerned Entities.
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
#include <memory>

namespace ecs {

/**
 * @brief   Abstract base class for all templated ComponentStore.
 * @ingroup ecs
 */
class IComponentStore {
public:
    /// Unique pointer to a ComponentStore
    typedef std::unique_ptr<IComponentStore> Ptr;
};

/**
 * @brief   A ComponentStore keep all the data of a certain type of Component for all concerned Entities.
 * @ingroup ecs
 *
 * @tparam C    A structure derived from Component, of a certain type of Component.
 */
template<typename C>
class ComponentStore : public IComponentStore {
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
     * @brief Add an Component (of a certain type Component corresponding to the store type) associated to an Entity.
     *
     * @param[in] aEntity       Id of the Entity with the Component to add.
     * @param[in] aComponent    Component of a certain Component to add.
     *
     * @return true if insertion succeeded
     */
    inline bool add(Entity aEntity, C&& aComponent) {
        return mStore.insert(std::make_pair(aEntity, aComponent)).second;
    }

    /**
     * @brief Remove the specified Component associated to an Entity.
     *
     * @param[in] aEntity   Id of the Entity to remove.
     *
     * @return true if finding and removing the Entity succeeded.
     */
    inline bool remove(Entity aEntity) {
        return (0 < mStore.erase(aEntity));
    }

    /**
     * @brief Test if the store contains a Component for the specified Entity.
     *
     * @param[in] aEntity   Id of the Entity to find.
     *
     * @return true if finding the Entity succeeded.
     */
    inline bool has(Entity aEntity) {
        return (mStore.end() != mStore.find(aEntity));
    }

private:
    std::unordered_map<Entity, C>   mStore;             ///< Hash map of stored Components
    static const ComponentType      _mType = C::_mType; ///< Type of stored Components
};

} // namespace ecs
