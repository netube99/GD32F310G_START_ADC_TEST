/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtconfig.h>

#ifndef RT_USING_FINSH
#error Please uncomment the line <#include "finsh_config.h"> in the rtconfig.h 
#endif

#ifdef RT_USING_FINSH

RT_WEAK char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    int ch = -1;
    if(usart_flag_get(SYSTEM_UART_PORT, USART_FLAG_RBNE))
        ch = usart_data_receive(SYSTEM_UART_PORT);
    return ch;
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';
    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            usart_data_transmit(SYSTEM_UART_PORT, a);
            while(RESET == usart_flag_get(SYSTEM_UART_PORT, USART_FLAG_TBE));
        }
        usart_data_transmit(SYSTEM_UART_PORT, *(str + i));
        while(RESET == usart_flag_get(SYSTEM_UART_PORT, USART_FLAG_TBE));
    }
}

#endif /* RT_USING_FINSH */

