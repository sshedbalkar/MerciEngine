set(CLIENT_NAME merci_client)
add_executable(${CLIENT_NAME} main_client.cpp)

# set a client version
set(${CLIENT_NAME}_VERSION_MAJOR 0)
set(${CLIENT_NAME}_VERSION_MINOR 1)
set(${CLIENT_NAME}_VERSION_PATCH 1)
set(${CLIENT_NAME}_VERSION "${${CLIENT_NAME}_VERSION_MAJOR}.${${CLIENT_NAME}_VERSION_MINOR}.${${CLIENT_NAME}_VERSION_PATCH}")
set(CLIENT_VERSION ALIAS ${${CLIENT_NAME}_VERSION})

# set client properties
set_target_properties(${CLIENT_NAME}
PROPERTIES
    VERSION ${CLIENT_VERSION}
    SOVERSION ${CLIENT_VERSION}
)

# set compiler options
target_compile_options(${CLIENT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /EHsc /MTd /W2 /c>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -mconsole>
)

# set compiler defines
target_compile_definitions(${CLIENT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
)

# set compiler features
target_compile_features(${CLIENT_NAME} PUBLIC 
    cxx_std_17
    cxx_static_assert
    cxx_variadic_macros
)

# link dependencies
target_link_libraries(${CLIENT_NAME}
    PUBLIC
        merci::net
        merci::debug
)