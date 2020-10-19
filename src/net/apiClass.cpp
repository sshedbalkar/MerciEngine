#include "../include/apiClass.h"

#include <iostream>
#include <iterator>
#include <tuple>

#include "../include/debug.h"

apiClass::apiClass() {
    std::cout << "apiClass: Default Constructor" << std::endl;
    merci::debug::log( "apiClass: Default Constructor" );
}

apiClass::~apiClass() {
    std::cout << "apiClass: Destructor" << std::endl;
    merci::debug::log( "apiClass: Destructor" );
}

apiClass::apiClass( const apiClass &other ) {
    std::cout << "apiClass: Copy Constructor" << std::endl;
    merci::debug::log( "apiClass: Copy Constructor" );
    std::ignore = other;
}

apiClass &apiClass::operator=( const apiClass &other ) {
    std::cout << "apiClass: Copy assignment operator" << std::endl;
    merci::debug::log( "apiClass: Copy assignment operator" );
    if ( this != &other ) { }
    return *this;
}

apiClass::apiClass( apiClass &&other ) noexcept {
    std::cout << "apiClass: Move Constructor" << std::endl;
    merci::debug::log( "apiClass: Move Constructor" );
    std::ignore = other;
}

apiClass &apiClass::operator=( apiClass &&other ) noexcept {
    std::cout << "apiClass: Move assignment operator" << std::endl;
    merci::debug::log( "apiClass: Move assignment operator" );
    if ( this != &other ) { }
    return *this;
}

int apiClass::add( int a, int b ) {
    merci::debug::log( "apiClass: Adding..." );
    return a + b;
}