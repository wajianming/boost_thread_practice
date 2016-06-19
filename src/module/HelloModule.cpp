#include "HelloModule.h"
#include <iostream>

HelloModule::HelloModule(){
    std::cout << "HelloModule constructed." << std::endl;
}

HelloModule::~HelloModule(){
    std::cout << "HelloModule destructed." << std::endl;
}
