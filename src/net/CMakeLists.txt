set(LIB_NAME net)
add_library(${LIB_NAME} SHARED 
    apiClass.cpp
    ../interface/apiClassIntf.cpp
)
add_library(merci::net ALIAS ${LIB_NAME})

#target_compile_options(${LIB_NAME} PRIVATE
#    $<$<CXX_COMPILER_ID:GNU>:-DWIN_EXPORT>
#)

target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:WIN_EXPORT>
    $<$<CXX_COMPILER_ID:GNU>:WIN_EXPORT>
)

# include files
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

find_package(asio CONFIG)
if(asio_FOUND)
	message("asio found")
	target_link_libraries(${LIB_NAME} PRIVATE asio asio::asio)
else()
	message("asio not found, considered configs: ${asio_CONSIDERED_CONFIGS}")
endif()