#include "fan_dev.h"

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

struct gdevice fan_dev = {
    .dev_name = "fan",
    .key = 0x43,
    .gpio_pin = 7,
    .gpio_mode = OUTPUT,
    .gpio_status = HIGH,
    .check_face_status = 0,
    .voice_set_status = 0,
    .next = NULL
};

struct gdevice* add_fan_dev_to_gdevice_list(struct gdevice *phead)
{
    return add_device_to_gdevice_list(phead, &fan_dev);
}