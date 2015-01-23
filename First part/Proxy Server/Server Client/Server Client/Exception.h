//
//  Exception.h
//  Proxy Server
//
//  Created by Максим on 06.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Proxy_Server__Exception__
#define __Proxy_Server__Exception__

#include <stdio.h>
#include <string>

struct my_exception
{
    std::string message;
    my_exception(std::string mess);
};

#endif /* defined(__Proxy_Server__Exception__) */
