/**
 * @file    System.h
 * @brief   A System manages any Entity having the required Components.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

namespace ecs {


/**
 * @brief A System manages any Entity having the required Components.
 *
 * This is a base class that need to be subclassed.
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
     * @brief Update function
     *
     * @param[in] aDeltaTime  Elpased time since last update call, in seconds.
     */
    virtual void update(float aDeltaTime);
};


} // namespace ecs
