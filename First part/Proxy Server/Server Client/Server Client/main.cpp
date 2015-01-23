//
//  main.cpp
//  Server Client
//
//  Created by Максим on 11.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "client.h"

int main()
{
    try
    {
        client client("localhost");
        client.connect();
        
        std::string name;
        std::cout << "Enter your name: ";
        std::cin >> name;
        client.send(name);
        
        std::string message;
        std::string tmp;
        while (tmp != "disconnect")
        {
            std::cout << "Please enter the message: ";
            std::getline(std::cin, message);
            tmp = message;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            //if (tmp != "disconnect")
            //{
                client.send(message);
            //}
        }
        
    }
    catch (...)
    {
        std::cout << "something" << std::endl;
    }
}
