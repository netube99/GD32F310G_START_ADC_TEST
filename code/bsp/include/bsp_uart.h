#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "main.h"

#define SYSTEM_UART_PORT            USART1
#define SYSTEM_UART_PERCLK          RCU_USART1
#define SYSTEM_UART_GPIO_PORT       GPIOA
#define SYSTEM_UART_GPIO_PERCLK     RCU_GPIOA
#define SYSTEM_UART_GPIO_TX_PIN     GPIO_PIN_2
#define SYSTEM_UART_GPIO_RX_PIN     GPIO_PIN_3

void System_Uart_Init(void);

#endif