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

System::System() :
    mRequiredComponents() {
}

System::~System() {
}

/* virtual pure to force subclassing by user
void System::update(float aDeltaTime) {
}
*/

} // namespace ecs
