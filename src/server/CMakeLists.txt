set(SERVER_NAME merci_server)
add_executable(${SERVER_NAME} main_server.cpp)

# set a server version
set(${SERVER_NAME}_VERSION_MAJOR 0)
set(${SERVER_NAME}_VERSION_MINOR 1)
set(${SERVER_NAME}_VERSION_PATCH 1)
set(${SERVER_NAME}_VERSION "${${SERVER_NAME}_VERSION_MAJOR}.${${SERVER_NAME}_VERSION_MINOR}.${${SERVER_NAME}_VERSION_PATCH}")
set(SERVER_VERSION ALIAS ${${SERVER_NAME}_VERSION})

# set client properties
set_target_properties(${SERVER_NAME}
PROPERTIES
    VERSION ${SERVER_VERSION}
    SOVERSION ${SERVER_VERSION}
)

# set compiler options
target_compile_options(${SERVER_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /EHsc /MTd /W2 /c>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-Wall -Wextra -pedantic -Werror -mconsole>
)

# set compiler defines
target_compile_definitions(${SERVER_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
)

# set compiler features
target_compile_features(${SERVER_NAME} PUBLIC 
    cxx_std_17
    cxx_static_assert
    cxx_variadic_macros
)

# link dependencies
target_link_libraries(${SERVER_NAME}
    PUBLIC
        merci::net
)

# copy the executable to the bin directory
add_custom_command(TARGET ${SERVER_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:${SERVER_NAME}>
        "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>" VERBATIM)