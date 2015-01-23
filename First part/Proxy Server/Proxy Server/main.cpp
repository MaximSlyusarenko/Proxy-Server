//
//  main.cpp
//  Proxy Server
//
//  Created by Максим on 06.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include <iostream>
#include "TCP.h"

int main()
{
    try
    {
        my_kq kq;
        TCP server(kq, 2578);
        server.accept_new_client = [&server](int fd)
        {
            std::cout << "client " << fd << " connected" << std::endl;
        };
        server.disconnect_client = [&server](std::string name)
        {
            std::cout << "client " << name << " disconnected. Good bye" << std::endl;
        };
        server.write_message = [&server](std::string message, std::string name)
        {
            std::cout << "client " << name << " say: " << message << std::endl;
        };
        kq.run();
    }
    catch (my_exception e)
    {
        std::cout << e.message << std::endl;
    }
    return 0;
}
