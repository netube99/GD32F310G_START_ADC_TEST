#include "bsp_uart.h"

//系统串口打印初始化
void System_Uart_Init(void)
{
    //初始化串口IO
    rcu_periph_clock_enable(SYSTEM_UART_GPIO_PERCLK);
    gpio_af_set(SYSTEM_UART_GPIO_PORT, GPIO_AF_1, SYSTEM_UART_GPIO_TX_PIN);
    gpio_af_set(SYSTEM_UART_GPIO_PORT, GPIO_AF_1, SYSTEM_UART_GPIO_RX_PIN);
    gpio_mode_set(SYSTEM_UART_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SYSTEM_UART_GPIO_TX_PIN);
    gpio_output_options_set(SYSTEM_UART_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, SYSTEM_UART_GPIO_TX_PIN);
    gpio_mode_set(SYSTEM_UART_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SYSTEM_UART_GPIO_RX_PIN);
    gpio_output_options_set(SYSTEM_UART_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, SYSTEM_UART_GPIO_RX_PIN);
    //初始化串口外设
    rcu_periph_clock_enable(SYSTEM_UART_PERCLK);
    usart_deinit(SYSTEM_UART_PORT);
    usart_word_length_set(SYSTEM_UART_PORT, USART_WL_8BIT);
    usart_stop_bit_set(SYSTEM_UART_PORT, USART_STB_1BIT);
    usart_parity_config(SYSTEM_UART_PORT, USART_PM_NONE);
    usart_baudrate_set(SYSTEM_UART_PORT, 115200U);
    usart_receive_config(SYSTEM_UART_PORT, USART_RECEIVE_ENABLE);
    usart_transmit_config(SYSTEM_UART_PORT, USART_TRANSMIT_ENABLE);
    usart_enable(SYSTEM_UART_PORT);
}
INIT_BOARD_EXPORT(System_Uart_Init);    //系统串口初始化加入RTT板级自动初始化

//系统串口打印函数重定向
// int fputc(int ch, FILE *f)
// {
//     usart_data_transmit(SYSTEM_UART_PORT, (uint8_t)ch);
//     while(RESET == usart_flag_get(SYSTEM_UART_PORT, USART_FLAG_TBE));
//     return ch;
// }