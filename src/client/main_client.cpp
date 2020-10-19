#include <iostream>

#include "../common/net_common.h"
#include "../include/apiClass.h"
#include "../include/debugIntf.h"
#include "../include/memory.h"

void print1( const char *msg ) {
    std::cout << "Printing: " << msg << std::endl;
}
void my_func_2() {
    std::cout << merci::memory::getStackTrace() << std::endl;
    std::cout.flush();
}

void my_func_1( double f ) {
    (void)f;
    my_func_2();
}

void my_func_1( int i ) {
    (void)i;
    my_func_2();
}
int main() {
    registerDebugCallback( print1 );
    std::cout << "main_client" << std::endl;
    apiClass api;
    int c = api.add( 11, 22 );
    std::cout << "The sum is: " << c << std::endl;
    std::cout.flush();
    my_func_1( 1 );
    my_func_1( 2.0 );
    return 0;
}