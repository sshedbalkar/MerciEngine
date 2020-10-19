#pragma once
#include <string>

namespace merci {
    using pFnVoidStr  = void ( * )( const char *str );
    using pFnVoidVoid = void ( * )();
    using pFnStrVoid  = std::string ( * )();
    using Cstr        = const char *;
}    // namespace merci