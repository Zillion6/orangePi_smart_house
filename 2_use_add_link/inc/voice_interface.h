#ifndef _VOICE_INTERFACE_H_
#define _VOICE_INTERFACE_H_

#include "global.h"
#include "msg_queue.h"
#include "mySerial.h"

int voice_init(void);

void voice_final(void);

void* voice_get_string_send_message(void *arg);

void* voice_send_string_speaking(void *buf);

struct control* add_voice_to_ctrl_list(struct control *phead);

#endif