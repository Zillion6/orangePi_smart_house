#ifndef _MSG_QUEUE_H_
#define _MSG_QUEUE_H_

#include <mqueue.h> 
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define QUEUE_NAME "/test_queue"

mqd_t message_queue_create();

int message_queue_send(mqd_t mqd, void *message,int len);

void message_queue_final(mqd_t mqd);

#endif