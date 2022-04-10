#include "main.h"
#include <string.h>

//打印ADC数据线程
void App_Print_Adc_Data_Thread(void)
{
    uint8_t str[32];
    while(1)
    {
        rt_thread_mdelay(2000);
        sprintf(str, "RAW:%d VOL:%f\r\n", Test_Adc_Get_Raw(), Test_Adc_Get_Voltage());
        rt_kprintf(str);
    }
}

int main(void)
{
    rt_thread_t i = rt_thread_create("test", App_Print_Adc_Data_Thread, RT_NULL, 1024, 4, 10);
    rt_thread_startup(i);
}
