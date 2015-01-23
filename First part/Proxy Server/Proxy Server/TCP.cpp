//
//  TCP.cpp
//  Proxy Server
//
//  Created by Максим on 09.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "TCP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <vector>
#include <map>

#define BACKLOG 100

TCP::TCP(my_kq& kq1, int port):kq(kq1)
{
    sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    int yes = 1;
    /*kq = kqueue();
    if (kq < 0)
    {
        throw my_exception("kqueue");
    }*/
    if (setsockopt(listener.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) < 0)
    {
        //close(kq);
        throw my_exception("setsockport");
    }
    if (bind(listener.fd, (sockaddr *) &addr, sizeof(addr)) < 0)
    {
        //close(kq);
        throw my_exception("bind");
    }
    if (listen(listener.fd, BACKLOG) < 0)
    {
        //close(kq);
        throw my_exception("listen");
    }
    kq.add(this);
}

int TCP::get_kq()
{
    return listener.fd;
}

void TCP::on_run()
{
    sockaddr_in addr;
    socklen_t len;
    try
    {
        my_socket tmp(listener.fd, (sockaddr*) &addr, &len);
        int fd = tmp.fd;
        client cl (this, tmp);
        clients.insert(std::make_pair(fd, cl));
        kq.add(&clients[fd]);
        accept_new_client(fd);
    }
    catch (my_exception e)
    {
        std::cout << e.message << std::endl;
    }
    catch (...)
    {
        std::cout << "Not my exception" << std::endl;
    }
}

/*TCP::~TCP()
{
    close(kq);
}

std::string TCP::read_from(int fd)
{
    std::string message = "";
    char buffer[512];
    ssize_t message_size = 0;
    bool first_here = true;
    bzero(buffer, 512);
    while (message_size == 511 || first_here)
    {
        first_here = false;
        message_size = recv(fd, buffer, 511, 0);
        if (message_size < 0)
        {
            throw my_exception("read");
        }
        else if (message_size == 0)
        {
            clients.erase(fd);
            std::string client_name = client_names.find(fd) -> second;
            disconnect_client(fd, client_name);
            return message;
        }
        else
        {
            message.append(buffer);
        }
    }
    return message;
}

void TCP::stop_server()
{
    running = false;
}

void TCP::send_to_client(int fd, std::string message)
{
    ssize_t sended = send(fd, message.c_str(), message.length(), 0);
    if (sended < 0)
    {
        throw my_exception("send exception");
    }
}

void TCP::run()
{
    running = true;
    struct kevent ev;
    sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    EV_SET(&ev, listener.fd, EVFILT_READ, EV_ADD, 0, 0, 0);
    int res = kevent(kq, &ev, 1, NULL, 0, NULL);
    if (res < 0)
    {
        throw my_exception("kevent 0");
    }
    bool client_connected_now = true;
    while (running)
    {
        int tmp_fd;
        memset(&ev, 0, sizeof(ev));
        res = kevent(kq, NULL, 0, &ev, 1, NULL);
        if (res < 0)
        {
            if (!running)
            {
                return;
            }
            throw my_exception("kevent 3");
        }
        else if (res > 0)
        {
            if (ev.ident == listener.fd)
            {
                try
                {
                    my_socket tmp_socket(listener.fd, (sockaddr *) &client_addr, &len);
                    tmp_fd = tmp_socket.fd;
                    clients.insert(std::make_pair(tmp_fd, tmp_socket));
                    EV_SET(&ev, tmp_fd, EVFILT_READ, EV_ADD, 0, 0, 0);
                    res = kevent(kq, &ev, 1, NULL, 0, NULL);
                    if (res == -1)
                    {
                        throw my_exception("kevent 4");
                    }
                    client_connected_now = true;
                }
                catch (my_exception e)
                {
                    std::cout << e.message << std::endl;
                }
                catch(...)
                {
                    std::cout << "NOT MY EXCEPTION" << std::endl;
                }
            }
            else
            {
                std::string mess = "";
                try
                {
                    mess = read_from((int) ev.ident);
                    if (client_connected_now)
                    {
                        client_connected_now = false;
                        std::string client_name = mess;
                        client_names.insert(std::make_pair(tmp_fd, client_name));
                        accept_new_client(client_name);
                    }
                    else
                    {
                        std::string client_name = client_names.find((int) ev.ident) -> second;
                        if (mess.size() > 0)
                        {
                            write_message(mess, client_name);
                        }
                    }
                }
                catch (my_exception e)
                {
                    std::cout << "EXCEPTION WHILE READ " << e.message << std::endl;
                }
                catch(...)
                {
                    std::cout << "NOT MY EXCEPTION" << std::endl;
                }
            }
        }
    }
}*/