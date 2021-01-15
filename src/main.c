#include "logger.h"
#include "systick.h"
#include "led.h"
#include "retarget.h"
#include "metadata.h"

int main(void)
{
    /* setup */
    systick_config();
    led_setup();
    retarget_init(USART1);
    
	LOG(DEBUG, "Application");
	LOG(DEBUG, "M: %d, M: %d, R: %d", VERSION[0], VERSION[1], VERSION[2]);
	LOG(DEBUG, "%s", INFO);

	while (1) {
		led_off();
		delay_1ms(500);
		led_on();
		delay_1ms(500);
	}
}
