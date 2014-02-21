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
 *
 * @todo Add a ComponentStore::extract() method to move out a Component.
 * @todo Throw instead of returning false in case of error?
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
     * @brief Add (move) a Component (of the same type as the ComponentStore) associated to an Entity.
     *
     *  Move a new Component into the Store, associating it to its Entity.
     * Using 'rvalue' (using the move semantic of C++11) requires:
     * - calling add() with 'std::move(component)', for instance;
     *   store.add(entity1, ComponentTest1(123);
     * - calling add() with a new temporary 'ComponentXxx(args)', for instance;
     *   ComponentTest1 component1(123);
     *   store.add(entity1, std::move(component1));
     *
     * @param[in] aEntity       Id of the Entity with the Component to add.
     * @param[in] aComponent    'rvalue' to a new Component (of the store type) to add.
     *
     * @return true if insertion succeeded
     */
    inline bool add(const Entity aEntity, C&& aComponent) {
        return mStore.insert(std::make_pair(aEntity, std::move(aComponent))).second;
    }

    /**
     * @brief Remove (destroy) the specified Component associated to an Entity.
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
     * @return true if finding the Entity and its associated Component succeeded.
     */
    inline bool has(Entity aEntity) const {
        return (mStore.end() != mStore.find(aEntity));
    }

    /**
     * @brief Get the Component associated with the specified Entity.
     *
     *  Throws std::out_of_range exception if the Entity and its associated Component is found.
     *
     * @param[in] aEntity   Id of the Entity to find.
     *
     * @return Reference to the Component associated with the specified Entity (or throw).
     */
    inline C& get(Entity aEntity) {
        return mStore.at(aEntity);
    }

private:
    std::unordered_map<Entity, C>   mStore;             ///< Hash map of stored Components
    static const ComponentType      _mType = C::_mType; ///< Type of stored Components
};

} // namespace ecs
