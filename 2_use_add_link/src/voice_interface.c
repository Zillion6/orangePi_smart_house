#include "voice_interface.h"
#include "control.h"
#include "device.h"
#include "global.h"

static int serial_fd = -1;

int voice_init(void)
{
    printf("%s|%s|%d\n", __FILE__, __func__, __LINE__);
    
    serial_fd = my_serialOpen (SERIAL_DEV, BAUD);
    if(-1 == serial_fd)
    {
        perror("my_serialOpen");

        return -1;
    }
    printf("%s|%s|%d:serial_fd=%d\n", __FILE__, __func__, __LINE__,serial_fd);

    return serial_fd;
}

void voice_final()
{
    close(serial_fd);
}

void* voice_get_string_send_message(void *arg)
{
    printf("%s|%s|%d:tid = %ld\n", __FILE__, __FUNCTION__, __LINE__, pthread_self());
    unsigned char get_buf[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    ctrl_info_t *ctrl_info = NULL;
    mqd_t mqd = -1;
    int len = 0;

    if(arg != NULL)
    {
        ctrl_info = (ctrl_info_t*)arg;
    }
    
    if(ctrl_info != NULL)
    {
        mqd = ctrl_info->mqd;
    }

    if(mqd == -1)
    {
        pthread_exit(NULL);
    }

//    serial_fd = voice_init();
    if (-1 == serial_fd)
    {
        pthread_exit(NULL);
    }

    pthread_detach(pthread_self());

    while(1)
    {
        printf("%s|%s|%d:tid = %ld\n", __FILE__, __FUNCTION__, __LINE__, pthread_self());

        len = my_serialGets(serial_fd, get_buf);
        if(len > 0)
        {
            printf("%s|%s|%d|len = %d\n", __FILE__, __func__, __LINE__, len);
            
            if(get_buf[0] == 0xAA && get_buf[1] == 0x55 && get_buf[4] == 0X55 && get_buf[5] == 0XAA)
            {
                printf("%s|%s|%d|get_buf = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __FILE__, __func__, __LINE__, get_buf[0], get_buf[1], get_buf[2], get_buf[3], get_buf[4], get_buf[5]);
                
                message_queue_send(mqd, get_buf, len);
            }
            memset(get_buf, 0, sizeof(get_buf));
        }
    }
    
    pthread_exit(NULL);
}

void* voice_send_string_speaking(void *buf)
{
    pthread_detach(pthread_self());
    unsigned char *send_buf = (unsigned char *)malloc(sizeof(char) * 12);
    send_buf = (unsigned char *)buf;

    printf("\033[43;30m%s|%s|%d:serial_fd = %d\n\033[0m", __FILE__, __FUNCTION__, __LINE__, serial_fd);

//    serial_fd = voice_init();
    if(serial_fd == -1)
    {
        pthread_exit(NULL);
    }

    if(send_buf != NULL)
    {
        printf("%s|%s|%d:send_buf = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", __FILE__, __FUNCTION__, __LINE__, send_buf[0], send_buf[1], send_buf[2], send_buf[3], send_buf[4], send_buf[5]);
        my_serialPuts(serial_fd, send_buf, 6);
    }
    pthread_exit(NULL);
}

struct control voice_control = 
{
    .control_name = "voice",
    .init = voice_init,
    .final = voice_final,
    .get = voice_get_string_send_message,
    .set = voice_send_string_speaking,
    .next = NULL
};

struct control* add_voice_to_ctrl_list(struct control *phead)
{
    return add_control_to_ctrl_list(phead, &voice_control);
//    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
}