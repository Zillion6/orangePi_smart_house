#ifndef _SMOKE_INTERFACE_H_
#define _SMOKE_INTERFACE_H_

#include "global.h"
#include "control.h"
#include "device.h"

#include <wiringPi.h>
#include <stdlib.h>

#define SMOKE_PIN 6
#define SMOKE_MODE INPUT

int smoke_interface_init();

void smoke_final();

void *smoke_get(void *arg);

void *add_smoke_to_ctrl_list(struct control *phead);

#endif