#pragma once

#include "typedefs.h"

namespace merci {
    namespace utility {
        unsigned Round( float num );
        unsigned UpperPowerOfTwo( unsigned v );
        Cstr MemSizeToText( size_t size );
    }    // namespace utility
}    // namespace merci