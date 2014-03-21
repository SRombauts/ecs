/**
 * @file    Utils.h
 * @ingroup ecs
 * @brief   Utilities and compatibility macros.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once


// Detect whether the compiler supports C++11 virtual override specifiers.
#if (defined(__GNUC__) && (__GNUC__ == 4)) // We do not care of GCC prior 4.x (without any form of C++11 support)
    /// GCC 4.7 and following have "override" and "final" support when called with -std=c++0x (or -std=c++11 starting with GCC 4.7)
    #if ((__GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
        /// GCC 4.6 and below does not know the "override" specifier, so we define it as nothing
        #define override  // nothing
    #endif
#endif
