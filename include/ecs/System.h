/**
 * @file    System.h
 * @brief   A System manages all Entities having all required Components.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

namespace ecs {


/**
 * @brief A System manages all Entities having all required Components.
 *
 * This is a virtual base class that needs to be subclassed.
 */
class System {
public:
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
    // std::set<ComponentType> mRequiredComponents
};


} // namespace ecs
