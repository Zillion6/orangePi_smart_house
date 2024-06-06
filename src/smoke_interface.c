#include "smoke_interface.h"

int smoke_interface_init()
{   
    pinMode(SMOKE_PIN, SMOKE_MODE);

    return 0;
}

void smoke_final()
{
    //do nothing
}

void *smoke_get(void *arg)
{
    char buffer[6]={0xAA, 0x55, 0x00, 0x00, 0x55, 0xAA};
    ctrl_info_t *ctrl_info = NULL;
    mqd_t mqd = -1;
    int status = HIGH;
    int smoke_flag = 0;

    if(arg != NULL)
    {
        ctrl_info = (ctrl_info_t *)arg;
    }

    if(ctrl_info != NULL)
    {
        mqd = ctrl_info->mqd;
    }

    if(mqd == -1)
    {
        pthread_exit(NULL);
    }

    pthread_detach(pthread_self());

    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    int result_smoke_interface_init = smoke_interface_init();

    while(1)
    {
        printf("%s|%s|%d:smoke_flag = %d status = %d\n", __FILE__, __FUNCTION__, __LINE__, smoke_flag, status);
        
        status = digitalRead(SMOKE_PIN);
        if(status == LOW)
        {
            buffer[2] = 0x45;
            buffer[3] = 0x00;
            printf("%s|%s|%d:send 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", __FILE__, __func__, __LINE__, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4],buffer[5]); 
            message_queue_send(mqd, buffer, 6);

            smoke_flag = 1;
        }
        else if(status == HIGH && smoke_flag == 1)
        {
            buffer[2] = 0x45;
            buffer[3] = 0x01;
            printf("%s|%s|%d:send 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", __FILE__, __func__, __LINE__, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4],buffer[5]);
            message_queue_send(mqd, buffer, 6);
            
            smoke_flag = 0;
            continue;
        }
        sleep(3);
    }

    pthread_exit(NULL);
}

struct control smoke = 
{
    .control_name = "smoke",
    .init = smoke_interface_init,
    .final = smoke_final,
    .get = smoke_get,
    .set = NULL,
    .next = NULL
};

void *add_smoke_to_ctrl_list(struct control *phead)
{
    return add_control_to_ctrl_list(phead, &smoke);
//    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
}