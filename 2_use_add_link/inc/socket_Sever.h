#ifndef _SOCKET_SEVER_H_
#define _SOCKET_SEVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "msg_queue.h"
#include "global.h"

#define MY_IP_ADDRESS "192.168.1.57"
#define MY_PORT       "9999"
#define BUF_SIZE      6

int socket_init();

#endif