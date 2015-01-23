//
//  Socket.cpp
//  Proxy Server
//
//  Created by Максим on 06.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "Socket.h"
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>

my_socket::my_socket()
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        throw my_exception("Error opening socket ");
    }
    fcntl(fd, F_SETFD, O_NONBLOCK);
}

my_socket::my_socket(int l_fd, sockaddr* client_addr, socklen_t* client_len)
{
    fd = accept(l_fd, client_addr, client_len);
    if (fd < 0)
    {
        throw my_exception("Error on accept ");
    }
    fcntl(fd, F_SETFD, O_NONBLOCK);
}

my_socket::my_socket(my_socket && s)
{
    fd = s.fd;
    s.fd = -1;
    fcntl(fd, F_SETFD, O_NONBLOCK);
}

my_socket::my_socket(my_socket & s)
{
    fd = s.fd;
    s.fd = -1;
    fcntl(fd, F_SETFD, O_NONBLOCK);
}

my_socket::~my_socket()
{
    close(fd);
}