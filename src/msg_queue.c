#include "msg_queue.h"

mqd_t message_queue_create()
{
    mqd_t mqd = -1;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    mqd = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if(mqd == -1)
    {
        perror("mq_open");

        return -1;
    }

    return mqd;
}

int message_queue_send(mqd_t mqd, void *message,int len)
{
    int n_mq_send = mq_send(mqd, (char *)message, len, 0);
    if(n_mq_send == -1)
    {
        perror("mq_send");

        return -1;
    }

    return n_mq_send;
}

void message_queue_final(mqd_t mqd)
{
    mq_close(mqd);
    
    mq_unlink(QUEUE_NAME);
}