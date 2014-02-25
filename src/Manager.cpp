/**
 * @file    Manager.cpp
 * @ingroup ecs
 * @brief   Manage associations of ecs::Entity, ecs::Component and ecs::System.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <ecs/Manager.h>

#include <algorithm>

namespace ecs {

Manager::Manager() :
    mLastEntity(_invalidEntity),
    mEntities(),
    mComponentStores(),
    mSystems() {
}

Manager::~Manager() {
}

// Add a System.
void Manager::addSystem(const System::Ptr& aSystemPtr) {
    // Check that required Components are specified
    if ((!aSystemPtr) || (aSystemPtr->getRequiredComponents().empty())) {
        throw std::runtime_error("System shall specified required Components");
    }
    // Simply copy the pointer (instead of moving it) to allow for multiple insertion of the same shared pointer.
    mSystems.push_back(aSystemPtr);
    // TODO Register the System with existing matching Entities? Or only allow Systems to be added during init?
}

// Register an Entity to all matching Systems.
size_t Manager::registerEntity(const Entity aEntity) {
    size_t nbAssociatedSystems = 0;

    // TODO throw if no Entity found
    auto entity = mEntities.find(aEntity);
    if (mEntities.end() != entity) {
        auto entityComponents = (*entity).second;

        for (auto system  = mSystems.begin();
                  system != mSystems.end();
                ++system) {
            auto systemRequiredComponents = (*system)->getRequiredComponents();
            // Check if all Components Required by the System are in the Entity (use sorted sets)
            if (std::includes(entityComponents.begin(), entityComponents.end(),
                              systemRequiredComponents.begin(), systemRequiredComponents.end())) {
                // Register the matching Entity
                (*system)->registerEntity(aEntity);
                ++nbAssociatedSystems;
            }
        }
    }

    return nbAssociatedSystems;
}

} // namespace ecs
