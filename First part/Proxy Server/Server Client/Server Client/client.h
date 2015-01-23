//
//  client.h
//  Server Client
//
//  Created by Максим on 11.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Server_Client__client__
#define __Server_Client__client__

#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Socket.h"

struct client
{
    client(std::string addr);
    void connect();
    void send(std::string message);
    
private:
    my_socket socket;
    sockaddr_in serv_addr;
    hostent *server;
};

#endif /* defined(__Server_Client__client__) */
