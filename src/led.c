#include "led.h"
#include "peripheral.h"
#include "gd32e23x_rcu.h"

void led_setup() {
    rcu_periph_clock_enable(LED_CLK);
    gpio_mode_set(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_output_options_set(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
}

void led_on() {
    gpio_bit_reset(LED_PORT, LED_PIN);
}

void led_off() {
    gpio_bit_set(LED_PORT, LED_PIN);
}
