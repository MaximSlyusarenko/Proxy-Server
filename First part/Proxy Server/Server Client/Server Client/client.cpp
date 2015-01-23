//
//  client.cpp
//  Server Client
//
//  Created by Максим on 11.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "client.h"

const int my_port = 2578;

client::client(std::string addr)
{
    server = gethostbyname(addr.c_str());
    if (server == NULL)
    {
        throw my_exception("no such host");
    }
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(my_port);
}

void client::connect()
{
    if (::connect(socket.fd, (const sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "connect problem " << std::endl;;
    }
}

void client::send(std::string message)
{
    std::string buf;
    int n;
    n = (int) ::send(socket.fd, message.c_str(), message.length(), 0);
    if (n < 0)
    {
        std::cout << "ERROR writing to socket" << std::endl;
    }
}