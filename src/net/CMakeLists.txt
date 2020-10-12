set(LIB_NAME net)
add_library(${LIB_NAME} SHARED 
    apiClass.cpp
    ../interface/apiClassIntf.cpp
)
add_library(merci::net ALIAS ${LIB_NAME})

# include files
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

find_package(asio CONFIG REQUIRED)
target_link_libraries(${LIB_NAME} PRIVATE asio asio::asio)