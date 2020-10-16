set(LIB_NAME debug)
add_library(${LIB_NAME} SHARED 
    debug.cpp
    ../interface/debugIntf.cpp
)
add_library(merci::${LIB_NAME} ALIAS ${LIB_NAME})

target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
    $<$<CXX_COMPILER_ID:GNU>:WIN_EXPORT>
)

# target_compile_options(${LIB_NAME} PRIVATE
#     $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-mconsole>
# )

target_compile_options(${LIB_NAME} PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-mconsole>
)

# include files
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
)

# copy the library to the bin directory
add_custom_command(TARGET ${LIB_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:${LIB_NAME}>
        "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>" VERBATIM)