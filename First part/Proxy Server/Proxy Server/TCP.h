//
//  TCP.h
//  Proxy Server
//
//  Created by Максим on 09.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Proxy_Server__TCP__
#define __Proxy_Server__TCP__

#include <stdio.h>
#include "Socket.h"
#include "KQ.h"
#include "Client.h"
#include "my_object.h"
#include <map>

struct client;

struct TCP: my_object
{
    TCP(my_kq& kq, int port);
    //~TCP();
    virtual void on_run();
    virtual int get_kq();
    /*void stop_server();
    std::string read_from(int fd);
    void send_to_client(int fd, std::string message);*/
    
    std::function <void(int fd)> accept_new_client;
    std::function <void(std::string name)> disconnect_client;
    std::function <void(std::string message, std::string name)> write_message;
    
    std::map <int, client> clients;
    
/*private:
    bool running;
    my_socket listener;
    int kq;
    std::map <int, my_socket> clients;
    std::map <int, std::string> client_names;*/
    
private:
    my_kq& kq;
    my_socket listener;
};

#endif /* defined(__Proxy_Server__TCP__) */
