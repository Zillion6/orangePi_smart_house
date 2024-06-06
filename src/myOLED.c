#include "myOLED.h"

struct display_info disp;

void oled_show(void *arg)
{
    int i;
    unsigned char *buffer = (unsigned char *)arg;
    
    oled_clear(&disp);

    oled_putstrto(&disp, 1, 9+1, buffer);
    disp.font = font2;
    oled_send_buffer(&disp);
}

void show_error(int err, int add)
{
	printf("\nERROR: %i, %i\n\n", err, add);
}

int myOled_init(void)
{
    int e;
    disp.address = OLED_I2C_ADDR;
    disp.font = font2;

    e = oled_open(&disp, FILENAME);
    if (e < 0)
    {
		show_error(1, e);
	}
    else
    {
		e = oled_init(&disp);
        oled_clear(&disp);
    }

    return e;
}