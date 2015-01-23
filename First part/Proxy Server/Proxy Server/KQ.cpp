//
//  KQ.cpp
//  Proxy Server
//
//  Created by Максим on 20.12.14.
//  Copyright (c) 2014 Maxim Slyusarenko. All rights reserved.
//

#include "KQ.h"

my_kq::my_kq()
{
    kq = kqueue();
    if (kq == -1)
    {
        throw my_exception("kqueue");
    }
}

my_kq::~my_kq()
{
    close(kq);
}

int my_kq::get_kq()
{
    return kq;
}

void my_kq::add(my_object* obj)
{
    struct kevent ev;
    EV_SET(&ev, obj -> get_kq(), EVFILT_READ, EV_ADD, 0, 0, 0);
    int res = kevent(kq, &ev, 1, NULL, 0, NULL);
    if (res < 0)
    {
        throw my_exception("kevent");
    }
    objects.insert(std::make_pair(obj -> get_kq(), obj));
}

void my_kq::finish()
{
    std::cout << "finish server" << std::endl;
    running = false;
}

void my_kq::run()
{
    running = true;
    struct kevent ev;
    signal(SIGINT, SIG_IGN);
    EV_SET(&ev, SIGINT, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
    int res = kevent(kq, &ev, 1, NULL, 0, NULL);
    if (res < 0)
    {
        throw my_exception("kevent");
    }
    signal(SIGTERM, SIG_IGN);
    EV_SET(&ev, SIGTERM, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
    res = kevent(kq, &ev, 1, NULL, 0, NULL);
    if (res < 0)
    {
        throw my_exception("kevent");
    }
    while (running)
    {
        res = kevent(kq, NULL, 0, &ev, 1, NULL);
        if (res < 0)
        {
            throw my_exception("kevent");
        }
        else if (res > 0)
        {
            if (ev.filter = EVFILT_SIGNAL && (ev.ident == SIGINT || ev.ident == SIGTERM))
            {
                finish();
            }
            else
            {
                objects[ev.ident] -> on_run();
            }
        }
    }
}