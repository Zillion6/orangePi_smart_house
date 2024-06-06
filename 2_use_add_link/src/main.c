#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "control.h"
#include "device.h"
#include "msg_queue.h"
#include "myOLED.h"
#include "mySerial.h"
#include "tcp_socket_interface.h"
#include "voice_interface.h"
#include "smoke_interface.h"
#include "receive_interface.h"
#include "global.h"

#include <wiringPi.h>

#if 0

typedef struct
{
    mqd_t mqd;
    struct  control *ctrl_phead;
}ctrl_info_t;

struct control
{
	char control_name[128]; //监听模块名称 
	int (*init)(void); //初始化函数
	void (*final)(void);//结束释放函数
	void *(*get)(void *arg);//监听函数，如语音监听
	void *(*set)(void *arg); //设置函数，如语音播报
	struct control *next;
};

#endif

int main(int argc, char **argv)
{
    struct control *p = NULL;
    ctrl_info_t *ctrl_info = NULL;
    int node_num = 0;
    int i = 0;

    if (-1 == wiringPiSetup())
    {
        exit(1);
    }

    ctrl_info = (ctrl_info_t *)malloc(sizeof(ctrl_info_t));
    ctrl_info->ctrl_phead = NULL;
    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    ctrl_info->mqd = message_queue_create();
    if(-1 == ctrl_info->mqd)
    {
        perror("message_queue_create");

        return -1;
    }

    ctrl_info->ctrl_phead = add_voice_to_ctrl_list(ctrl_info->ctrl_phead);
    ctrl_info->ctrl_phead = add_tcp_socket_to_ctrl_list(ctrl_info->ctrl_phead);
    ctrl_info->ctrl_phead = add_smoke_to_ctrl_list(ctrl_info->ctrl_phead);
    ctrl_info->ctrl_phead = add_receive_to_ctrl_list(ctrl_info->ctrl_phead);
    
    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
    
    p = ctrl_info->ctrl_phead;
    while(NULL != p)
    {
        if(NULL != p->init)
        {
            p->init();
        }

        node_num++;
        printf("%s|%s|%d:node_num = %d\n", __FILE__, __FUNCTION__, __LINE__, node_num);
        
        p = p->next;

    }

    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * node_num);
    p = ctrl_info->ctrl_phead;

    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    for(i = 0; i < node_num; i++)
    {
        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

        if(NULL != p->get)
        {
            printf("%s|%s|%d:i = %d\n", __FILE__, __FUNCTION__, __LINE__, i);

            int result_pthread_create = pthread_create(&tid[i], NULL, (void *)p->get, (void *)ctrl_info);
            
            printf("%s|%s|%d: %d\n", __FILE__, __FUNCTION__, __LINE__, result_pthread_create);
            
            if(result_pthread_create)
            {
                perror("pthread_create");
                return -1;
            }
        }
        p = p->next;
    }

    p = ctrl_info->ctrl_phead;
    printf("%s|%s|%d:node_num = %d\n", __FILE__, __FUNCTION__, __LINE__,node_num);

    for(i = 0; i < node_num; i++)
    {
        printf("%s|%s|%d:i = %d\n", __FILE__, __FUNCTION__, __LINE__, i);
        int result_pthread_join = pthread_join(tid[i], NULL);
        if(!result_pthread_join)
        {
            printf("%s|%s|%d:i = %d, %ld\n", __FILE__, __FUNCTION__, __LINE__, i, tid[i]);
            perror("pthread_join");

            return -1;
        }
        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
    }

    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    for(i = 0; i < node_num; i++)
    {
        if(NULL != p->final)
        {
            p->final();
        }

        p = p->next;
    }
    
    while(1);

    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    message_queue_final(ctrl_info->mqd);

    return 0;
}