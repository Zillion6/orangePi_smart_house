#ifndef _TCP_SOCKET_INTERFACE_H_
#define _TCP_SOCKET_INTERFACE_H_

#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>

#include "global.h"
#include "device.h"
#include "control.h"

int tcp_socket_interface_init();

void tcp_socket_final();

void* tcp_socket_get(void *arg);

struct control* add_tcp_socket_to_ctrl_list(struct control* phead);

#endif