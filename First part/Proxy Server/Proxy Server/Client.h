//
//  Client.h
//  Proxy Server
//
//  Created by Максим on 20.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#ifndef __Proxy_Server__Client__
#define __Proxy_Server__Client__

#include <stdio.h>
#include <string>
#include <map>
#include "TCP.h"
#include "my_object.h"

struct TCP;

struct client: my_object
{
    client(){name = ""; is_name = false;};
    client(const client& client) = delete;
    client(client& client):socket(client.socket), server(client.server){name = ""; is_name = false;};
    client(client&& client):socket(client.socket), server(client.server){name = ""; is_name = false;};
    client(TCP* serv, my_socket &s):socket(s), server(serv){name = ""; is_name = false;};
    
    std::string read();
    void send(std::string message);
    virtual int get_kq();
    virtual void on_run();
    
    
private:
    my_socket socket;
    TCP* server;
    friend struct TCP;
    std::string name;
    bool is_name;
};

#endif /* defined(__Proxy_Server__Client__) */
