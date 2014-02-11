/**
 * @file    Manager.cpp
 * @brief   Manage associations of Entities and Components.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "ecs/Manager.h"

namespace ecs {


Manager::Manager() :
    mEntities(),
    mSystems(),
    mComponents() {
}

Manager::~Manager() {
}


} // namespace ecs
