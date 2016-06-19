#ifndef HELLO_LIB_H
#define HELLO_LIB_H
#include "HelloStaticLib.h"

class HelloLib: public HelloStaticLib{
public:
    HelloLib();
    virtual ~HelloLib();
};

#endif
