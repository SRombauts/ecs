/**
 * @file    System.h
 * @ingroup ecs
 * @brief   A ecs::System manages all ecs::Entity having all required ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <ecs/ComponentType.h>
#include <ecs/Entity.h>

#include <set>
#include <memory>

namespace ecs {

class Manager;

/**
 * @brief A System manages any Entity having all required Component.
 * @ingroup ecs
 *
 *  A System is a program running logic and updating data on any Entity holding a certain set of Components.
 * Systems run repeatedly on all corresponding Entities.
 *
 *  This is a base class that needs to be subclassed.
 *
 * @todo Add an additionnal Entity list, matching an other Component list, to work with (for collision for instance)
 */
class System {
public:
    /// A shared pointer to a System is needed to add multiple entry into the vector of Systems, for multi-execution.
    typedef std::shared_ptr<System> Ptr;

    /**
     * @brief Constructor.
     *
     * @param[in] aManager  Reference to the manager needed to access Entity Components.
     */
    explicit System(Manager& aManager);

    /**
     * @brief Destructor.
     */
    virtual ~System();

    /**
     * @brief Get the Types of all the Components required by the System.
     */
    inline const ComponentTypeSet& getRequiredComponents() const {
        return mRequiredComponents;
    }

    /**
     * @brief Register a matching Entity, having all required Components.
     *
     * @param[in] aEntity   Matching Entity
     *
     * @return true if the Entity has been inserted successfully
     */
    inline bool registerEntity(Entity aEntity) {
        return mMatchingEntities.insert(aEntity).second;
    }

    /**
     * @brief Register a matching Entity, having all required Components.
     *
     * @param[in] aEntity   Matching Entity
     *
     * @return 1 if the Entity has been removed successfully, 0 otherwize
     */
    inline size_t unregisterEntity(Entity aEntity) {
        return mMatchingEntities.erase(aEntity);
    }

    /**
     * @brief Test if the System has registered this Entity.
     *
     * @param[in] aEntity   Id of the Entity to find.
     *
     * @return true if finding the Entity succeeded.
     */
    inline bool hasEntity(Entity aEntity) const {
        return (mMatchingEntities.end() != mMatchingEntities.find(aEntity));
    }

    /**
     * @brief Update function - for all matching Entities.
     *
     * @param[in] aElapsedTime  Elapsed time since last update call, in seconds.
     *
     * @return Number of updated Entities
     */
    size_t updateEntities(float aElapsedTime);

    /**
     * @brief Update function - for a given matching Entity - virtual pure.
     *
     * @param[in] aElapsedTime  Elapsed time since last update call, in seconds.
     * @param[in] aEntity       Matching Entity
     */
    virtual void updateEntity(float aElapsedTime, Entity aEntity) = 0;

protected:
    /**
     * @brief Specify what are required Components of te System.
     *
     * @param[in] aRequiredComponents   List the Types of all the Components required by the System.
     */
    inline void setRequiredComponents(ComponentTypeSet&& aRequiredComponents) {
        mRequiredComponents = std::move(aRequiredComponents);
    }

    /**
     * @brief Reference to the manager needed to access Entity Components.
     */
    Manager&            mManager;

private:
    /**
     * @brief List the Types of all the Components required by the System.
     */
    ComponentTypeSet    mRequiredComponents;

    /**
     * @brief List all the matching Entities having required Components for the System.
     */
    std::set<Entity>    mMatchingEntities;
};

} // namespace ecs
