#include "device.h"

#if 0

struct gdevice *add_device_to_gdevice_list(struct gdevice *phead, struct gdevice *device)
{
	struct gdevice *p = phead;
    printf("%s|%s|%d:%p\n", __FILE__, __FUNCTION__, __LINE__, p);

    if(p == NULL)
    {
        phead = device;
        
        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

        return phead;
    }
    else
    {
        device->next = phead;
        phead = device;

        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

        return phead;
    }

    return phead;
}

#endif

struct gdevice *find_gdevice_by_key(struct gdevice *pdev, unsigned char key)
{
    struct gdevice *p = pdev;
    printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

    if(p == NULL)
    {
        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
        return NULL;
    }

    while(p != NULL)
    {
        if(p->key == key)
        {
            printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);
            return p;
        }

        p = p->next;

        if(p == NULL)
        {
            p = pdev;
        }
    }

    return NULL;
}

#if 0

struct gdevice
{
	char dev_name[128]; //设备名称
	int key; //key值，用于匹配控制指令的值
	int gpio_pin; //控制的gpio引脚
	int gpio_mode; //输入输出模式
	int gpio_status; //高低电平状态
	int check_face_status; //是否进行人脸检测状态
	int voice_set_status; //是否语音语音播报
	struct gdevice *next;
};

#endif

int set_gpio_gdevice_status(struct gdevice *pdev)
{
//    printf("\033[41;30m%s|%s|%d:pdev->gpio_status = %d\033[0m\n", __FILE__, __FUNCTION__, __LINE__, pdev->gpio_status);
    if (pdev != NULL)
    {
        printf("%s|%s|%d:pdev->gpio_status = %d\n", __FILE__, __FUNCTION__, __LINE__, pdev->gpio_status);
        if (pdev->gpio_pin != -1)
        {
            pinMode(pdev->gpio_pin, pdev->gpio_mode);
            printf("\033[45;30m%s|%s|%d:gpio_pin = %d, gpio_mode = %d\033[0m\n", __FILE__, __FUNCTION__, __LINE__, pdev->gpio_pin, pdev->gpio_mode);
        }

        if(pdev->gpio_status != -1)
        {
            digitalWrite(pdev->gpio_pin, pdev->gpio_status);
            printf("%s|%s|%d:pdev->gpio_status = %d\n", __FILE__, __FUNCTION__, __LINE__, pdev->gpio_status);
        }

        return 0;
    }
    else
    {
//        printf("%s|%s|%d: \033[41;36m something here \033[0m\n", __FILE__, __FUNCTION__, __LINE__);
        return -1;
    }
}
