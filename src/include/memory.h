#pragma once

#include "../common/exported.h"
#include "../common/typedefs.h"

namespace merci {
    namespace memory {
        /**
         * @brief Call this function to get a stacktrace of the point where it
         is being called from

         Currently only works on Linux. Windows systems require .pdb files to
         load symbol information
         *
         */
        EXPORTED extern pFnStrVoid getStackTrace;
    }    // namespace memory
}    // namespace merci