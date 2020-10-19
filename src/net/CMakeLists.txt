set(LIB_NAME net)
add_library(${LIB_NAME} SHARED 
    apiClass.cpp
    ../interface/apiClassIntf.cpp
)
add_library(merci::${LIB_NAME} ALIAS ${LIB_NAME})

#target_compile_options(${LIB_NAME} PRIVATE
#    $<$<CXX_COMPILER_ID:GNU>:-DWIN_EXPORT>
#)

target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
    $<$<CXX_COMPILER_ID:GNU>:WIN_EXPORT>
)

target_compile_options(${LIB_NAME} PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-mconsole>
)

target_link_options(${LIB_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-pthread>
)
# add_compile_options("${_opts}")

# include files
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
           $ENV{VCPKG_ROOT}/installed/x64-linux/include
)

find_package(asio CONFIG)
if(asio_FOUND)
	message("asio found")
    target_link_libraries(${LIB_NAME} PRIVATE asio asio::asio)
    target_include_directories(${LIB_NAME} PRIVATE ${asio_INCLUDE_DIR})
else()
	message("asio not found, considered configs: ${asio_CONSIDERED_CONFIGS}")
endif()
find_package(Threads REQUIRED)

# link dependencies
target_link_libraries(${LIB_NAME}
    PUBLIC
        merci::debug
        Threads::Threads
)

# copy the library to the bin directory
add_custom_command(TARGET ${LIB_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:${LIB_NAME}>
        "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>" VERBATIM)