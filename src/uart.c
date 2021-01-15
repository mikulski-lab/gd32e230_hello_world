#include "uart.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_usart.h"

#define UART_CH	1	/* UART channel to use = 0: USART0, 1: USART1 */

#if UART_CH == 0		/* PA9:USART0_TX, PA10:USART0_RX */
#define USART_PIN_TX	GPIO_PIN_9
#define USART_PIN_RX	GPIO_PIN_10
#define USART_PORT		GPIOA
#define USARTx          USART0
#define RCU_USARTx      RCU_USART0
#define RCU_GPIOx       RCU_GPIOA
#elif UART_CH == 1		/* PA2:USART1_TX, PA3:USART1_RX */
#define USART_PIN_TX	GPIO_PIN_2
#define USART_PIN_RX	GPIO_PIN_3
#define USART_PORT		GPIOA
#define USARTx          USART1
#define RCU_USARTx      RCU_USART1
#define RCU_GPIOx       RCU_GPIOA
#endif

static void com_init_gpio();
static void com_init_usart();

void uart_setup() {
    com_init_gpio();
    com_init_usart();
}

static void com_init_gpio() {
	rcu_periph_clock_enable(RCU_GPIOx);
	
	/* configure the USARTx Tx/Rx pin */
    gpio_af_set(USART_PORT, GPIO_AF_1, USART_PIN_TX|USART_PIN_RX);

    /* configure USARTx Tx as alternate function push-pull */
    gpio_mode_set(USART_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART_PIN_TX);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, USART_PIN_TX);
	
	/* configure USARTx Rx as alternate function push-pull */
    gpio_mode_set(USART_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART_PIN_RX);
    gpio_output_options_set(USART_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, USART_PIN_RX);
}

static void com_init_usart() {
    rcu_periph_clock_enable(RCU_USARTx);
	
    /* USART configure */
    usart_deinit(USARTx);
    usart_word_length_set(USARTx, USART_WL_8BIT);
    usart_stop_bit_set(USARTx, USART_STB_1BIT);
    usart_parity_config(USARTx, USART_PM_NONE);
    usart_baudrate_set(USARTx, 115200U);
    usart_receive_config(USARTx, USART_RECEIVE_ENABLE);
    usart_transmit_config(USARTx, USART_TRANSMIT_ENABLE);

    usart_enable(USARTx);
}
