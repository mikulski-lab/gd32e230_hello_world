#include "logger.h"
#include "systick.h"
#include "led.h"
#include "retarget.h"

int main(void)
{
    /* setup */
    systick_config();
    led_setup();
    retarget_init();

	while (1) {
		led_off();
		delay_1ms(500);
		led_on();
		LOG(DEBUG, "LED ON");
		delay_1ms(500);
	}
}
