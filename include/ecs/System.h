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

/**
 * @brief A System manages all Entity having all required Component.
 * @ingroup ecs
 *
 *  A System is a program running logic and updating data on any Entity holding a certain set of Components.
 * Systems run repeatedly on all corresponding Entities.
 *
 *  This is a virtual base class that needs to be subclassed.
 *
 * @todo unregister(aEntity)
 */
class System {
public:
    /// A shared pointer to a System is needed to add multiple entry into the vector of Systems, for multi-execution.
    typedef std::shared_ptr<System> Ptr;

    /**
     * @brief Constructor.
     *
     * @param[in] aRequiredComponents   List the Types of all the Components required by the System.
     */
    explicit System(ComponentTypeSet&& aRequiredComponents);

    /**
     * @brief Destructor.
     */
    virtual ~System();

    /**
     * @brief Update function - for all matching Entities.
     *
     * @param[in] aDeltaTime  Elapsed time since last update call, in seconds.
     */
    void updateEntities(float aDeltaTime);

    /**
     * @brief Update function - for a given matching Entity - virtual pure.
     *
     * @param[in] aDeltaTime    Elapsed time since last update call, in seconds.
     * @param[in] aEntity       Matching Entity
     */
    virtual void updateEntity(float aDeltaTime, Entity aEntity) = 0;

    /**
     * @brief Register a matching Entity, having all required Components.
     *
     * @param[in] aEntity   Matching Entity
     */
    inline bool registerEntity(Entity aEntity) {
        return mMatchingEntities.insert(aEntity).second;
    }

    /**
     * @brief Get the Types of all the Components required by the System.
     */
    inline const ComponentTypeSet& getRequiredComponents() const {
        return mRequiredComponents;
    }

private:
    /**
     * @brief List the Types of all the Components required by the System.
     */
    const ComponentTypeSet  mRequiredComponents;

    /**
     * @brief List all the matching Entities having required Components.
     */
    std::set<Entity>        mMatchingEntities;
};

} // namespace ecs
