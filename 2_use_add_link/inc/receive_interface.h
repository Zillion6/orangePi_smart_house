#ifndef _RECEIVE_INTERFACE_H_
#define _RECEIVE_INTERFACE_H_

#include <mqueue.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "device.h"
#include "control.h"
#include "global.h"

typedef struct
{
    int msg_len;
    unsigned char *buffer;
    ctrl_info_t *ctrl_info;
}recv_msg_t;

int receive_interface_init();

void receive_final();

void* handler(void *arg);

void* receive_get(void *arg);

struct control* add_receive_to_ctrl_list(struct control* phead);

#endif