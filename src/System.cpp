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
#include <ecs/Manager.h>

namespace ecs {

System::System(Manager& aManager) :
    mManager(aManager) {
}

System::~System() {
}

/**
 * @brief Update function - for all matching Entities.
 *
 * @param[in] aElapsedTime  Elapsed time since last update call, in seconds.
 */
size_t System::updateEntities(float aElapsedTime) {
    size_t nbUpdatedEntities = 0;

    for (auto entity  = mMatchingEntities.begin();
              entity != mMatchingEntities.end();
            ++entity) {
        // For each matching Entity, call the specialized System update method.
        updateEntity(aElapsedTime, *entity);
        ++nbUpdatedEntities;
    }

    return nbUpdatedEntities;
}

/* virtual pure method to be specialized by user classes
void System::updateEntity(float aElapsedTime, Entity aEntity) {
}
*/

} // namespace ecs
