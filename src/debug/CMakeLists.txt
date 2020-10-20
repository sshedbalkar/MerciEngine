set(LIB_NAME debug)
add_library(${LIB_NAME} SHARED 
    debug.cpp
    ../interface/debugIntf.cpp
    stacktrace.cpp
)
add_library(merci::${LIB_NAME} ALIAS ${LIB_NAME})

target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
    $<$<CXX_COMPILER_ID:GNU>:WIN_EXPORT>
)
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    message("Windows...")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    list(APPEND CMAKE_MODULE_PATH "/usr/share/cmake-3.16/Modules/**")
    set_source_files_properties(stacktrace.cpp 
        PROPERTIES 
            COMPILE_OPTIONS 
                "$<$<CXX_COMPILER_ID:GNU>:-ggdb3;-O0;-no-pie;-ldw>"
            INCLUDE_DIRECTORIES
                "$<$<CXX_COMPILER_ID:GNU>:/usr/include/elfutils>"
    )
    find_package(Elfutils REQUIRED)
endif()
# target_compile_options(${LIB_NAME} PRIVATE
#     $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-mconsole>
# )

target_compile_options(${LIB_NAME} PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-mconsole>
)


# include files
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
        $<$<PLATFORM_ID:Linux>:${LIBDW_INCLUDE_DIRS}>
)

target_link_libraries(${LIB_NAME}
    PUBLIC
        $<$<PLATFORM_ID:Linux>:${LIBDW_LIBRARIES}>
    PRIVATE
        $<$<PLATFORM_ID:Windows>:dbghelp>
)

# copy the library to the bin directory
add_custom_command(TARGET ${LIB_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:${LIB_NAME}>
        "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>" VERBATIM)