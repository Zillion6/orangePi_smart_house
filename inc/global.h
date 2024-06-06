#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "msg_queue.h"

typedef struct
{
    mqd_t mqd;
    struct control *ctrl_phead;
}ctrl_info_t;

#endif