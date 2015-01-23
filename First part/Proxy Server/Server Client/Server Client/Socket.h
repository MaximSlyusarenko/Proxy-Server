//
//  Socket.h
//  Proxy Server
//
//  Created by Максим on 06.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Proxy_Server__Socket__
#define __Proxy_Server__Socket__

#include <stdio.h>
#include <sys/socket.h>
#include "Exception.h"

struct my_socket
{
    int fd;
    my_socket();
    my_socket(int l_fd, sockaddr* client_addr, socklen_t* client_len);
    my_socket(my_socket && s);
    my_socket(my_socket const & s) = delete;
    my_socket(my_socket & s);
    ~my_socket();
    
};

#endif /* defined(__Proxy_Server__Socket__) */
