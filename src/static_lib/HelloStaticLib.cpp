#include "HelloStaticLib.h"
#include <iostream>

HelloStaticLib::HelloStaticLib(){
    std::cout << "Hello Lib Constructed." << std::endl;
}

HelloStaticLib::~HelloStaticLib(){
    std::cout << "Hello Lib Destructed." << std::endl;
}
