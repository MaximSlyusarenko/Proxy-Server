//
//  Client.cpp
//  Proxy Server
//
//  Created by Максим on 20.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "Client.h"

int client::get_kq()
{
    return socket.fd;
}

void client::on_run()
{
    std::string message = "";
    char buffer[512];
    ssize_t message_size = 0;
    bool first_here = true;
    bzero(buffer, 512);
    while (message_size == 511 || first_here)
    {
        first_here = false;
        message_size = recv(socket.fd, buffer, 511, 0);
        if (message_size < 0)
        {
            throw my_exception("read");
        }
        else if (message_size < 511)
        {
            //server -> clients.erase(socket.fd);
            //clients.erase(socket.fd);
            //std::string client_name = client_names.find(socket.fd) -> second;
            //disconnect_client(fd, client_name);
            //return message;
            message.append(buffer);
            if (!is_name)
            {
                name = message;
                is_name = true;
            }
            else if (message != "disconnect")
            {
                server -> write_message(message, name);
            }
            else
            {
                int tmp = socket.fd;
                server -> clients.erase(tmp);
                server -> disconnect_client(name);
            }
        }
        else
        {
            message.append(buffer);
        }
    }
    //return message;
}

void client::send(std::string message)
{
    ssize_t s;
    s = ::send(socket.fd, message.c_str(), message.size(), 0);
    if (s < 0)
    {
        throw my_exception("send error");
    }
}