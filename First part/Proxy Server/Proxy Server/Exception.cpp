//
//  Exception.cpp
//  Proxy Server
//
//  Created by Максим on 06.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "Exception.h"
#include <iostream>

my_exception::my_exception(std::string mess)
{
    message = mess + ": " + strerror(errno);
}