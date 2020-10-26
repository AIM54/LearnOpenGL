//
// Created by tom1 on 2020/10/26.
//

#ifndef LEARNOPENGL_THREAD_H
#define LEARNOPENGL_THREAD_H


#include <sys/types.h>

class Thread {
private:
    pthread_t pthread;

    static void *onStart(void *arg);

public:
    virtual void run() = 0;

    void join();

    void start();

    void detach();


};


#endif //LEARNOPENGL_THREAD_H
