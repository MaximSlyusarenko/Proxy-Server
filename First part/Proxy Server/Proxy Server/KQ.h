//
//  KQ.h
//  Proxy Server
//
//  Created by Максим on 20.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Proxy_Server__KQ__
#define __Proxy_Server__KQ__

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <vector>
#include <map>
#include "my_object.h"
#include "Socket.h"

struct my_kq
{
    my_kq();
    ~my_kq();
    void add(my_object* obj);
    void run();
    void finish();
    int get_kq();
    
private:
    int kq;
    bool running;
    std::map <int, my_object*> objects;
};

#endif /* defined(__Proxy_Server__KQ__) */
