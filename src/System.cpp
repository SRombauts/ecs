/**
 * @file    System.cpp
 * @ingroup ecs
 * @brief   A ecs::System manages all ecs::Entity having all required ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/System.h>

namespace ecs {

System::System() {
}

System::~System() {
}

/**
 * @brief Update function - for all matching Entities.
 *
 * @param[in] aDeltaTime  Elapsed time since last update call, in seconds.
 */
void System::updateEntities(float aDeltaTime) {
    for (auto entity  = mMatchingEntities.begin();
              entity != mMatchingEntities.end();
            ++entity) {
        // For each matching Entity, call the specialized System update method.
        updateEntity(aDeltaTime, *entity);
    }
}

/* virtual pure method to be specialized by user classes
void System::updateEntity(float aDeltaTime, Entity aEntity) {
}
*/

} // namespace ecs
