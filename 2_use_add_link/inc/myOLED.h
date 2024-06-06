#ifndef _MYOLED_H_
#define _MYOLED_H_

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "oled.h"
#include "font.h"

#define FILENAME  "/dev/i2c-3"

void oled_show(void *argv);

int myOled_init(void);

#endif