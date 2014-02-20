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

namespace ecs {

Manager::Manager() :
    mLastEntity(_invalidEntity),
    mEntities(),
    mComponentStores(),
    mSystems() {
}

Manager::~Manager() {
}

} // namespace ecs
