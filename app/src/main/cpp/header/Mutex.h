//
// Created by tom1 on 2020/10/26.
//

#ifndef LEARNOPENGL_MUTEX_H
#define LEARNOPENGL_MUTEX_H

#include "Condition.h"
#include <sys/types.h>

class Mutex {
    friend class Condition;

public:
    pthread_mutex_t mutex_t;

};


#endif //LEARNOPENGL_MUTEX_H
