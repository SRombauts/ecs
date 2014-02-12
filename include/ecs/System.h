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

#include <set>
#include <memory>

namespace ecs {

/**
 * @brief A System manages all Entity having all required Component.
 * @ingroup ecs
 *
 *  A System is a program runing logic and updating data on any Entity holding a certain set of Components.
 * Systems run repeteadly on all corresponding Entities.
 *
 *  This is a virtual base class that needs to be subclassed.
 */
class System {
public:
    /// Shared pointer to a System
    typedef std::shared_ptr<System> Ptr;

    /**
     * @brief Constructor
     */
    System();
    /**
     * @brief Destructor
     */
    virtual ~System();

    /**
     * @brief Update function - virtual
     *
     * @param[in] aDeltaTime  Elapsed time since last update call, in seconds.
     */
    virtual void update(float aDeltaTime) = 0;

private:
    /**
     * @brief List the Types of all the Components requiered by the System.
     */
    ComponentTypeSet    mRequiredComponents;
};

} // namespace ecs
