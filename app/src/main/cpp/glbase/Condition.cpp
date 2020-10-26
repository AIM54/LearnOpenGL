//
// Created by tom1 on 2020/10/26.
//

#include "Condition.h"
#include <pthread.h>

int Condition::init() {
    return pthread_cond_init(&cond, nullptr);
}

int Condition::broadcast() {
    return pthread_cond_broadcast(&cond);
}

int Condition::signal() {
    return pthread_cond_signal(&cond);
}
