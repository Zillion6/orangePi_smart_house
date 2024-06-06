#ifndef _MYSERIAL_H_
#define _MYSERIAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERIAL_DEV "/dev/ttyS5"
#define BAUD 115200

#include "mySerial.h"

int my_serialOpen (const char *device, const int baud);

void my_serialPuts(const int fd, const char *s, int len);

int my_serialGets(const int fd, unsigned char *buffer);

char* serialGetchar (const int fd);

#endif