//
//  my_object.h
//  Proxy Server
//
//  Created by Максим on 20.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef Proxy_Server_my_object_h
#define Proxy_Server_my_object_h

struct my_object
{
    virtual void on_run() = 0;
    virtual int get_kq() = 0;
};

#endif
