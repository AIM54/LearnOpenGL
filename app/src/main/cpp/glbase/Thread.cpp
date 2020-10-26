//
// Created by tom1 on 2020/10/26.
//

#include "Thread.h"
#include <pthread.h>

void Thread::start() {
    pthread_create(&pthread, NULL, onStart, this);
}

void Thread::detach() {
    pthread_detach(pthread);

}

void *Thread::onStart(void *arg) {
    Thread *currentThread = static_cast<Thread *>(arg);

    currentThread->run();
}

void Thread::join() {
    pthread_join(pthread, NULL);
}


