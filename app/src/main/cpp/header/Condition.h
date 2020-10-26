//
// Created by tom1 on 2020/10/26.
//

#ifndef LEARNOPENGL_CONDITION_H
#define LEARNOPENGL_CONDITION_H

#include <sys/types.h>
class Condition {
private:
    pthread_cond_t cond;
public:
    int init();

    int signal();

    int broadcast();


};


#endif //LEARNOPENGL_CONDITION_H
