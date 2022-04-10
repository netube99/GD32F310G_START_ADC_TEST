#include "bsp_adc.h"

uint16_t adc_test_raw_data = 0 ;    //adc测试输出原始结果（平均值）
float adc_test_voltage = 0.0 ;      //adc测试输出电压值（平均值）

void Test_Adc_Init(void)
{
    //设置模拟输入IO
    rcu_periph_clock_enable(TEST_ADC_GPIO_PERCLK);
    gpio_mode_set(TEST_ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, TEST_ADC_GPIO_PIN);     //设置测试通道的GPIO为模拟模式
    //设置ADC外设
    rcu_periph_clock_enable(TEST_ADC_PERCLK);
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);                                                  //ADC时钟源设置
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);                                             //数据对齐模式：右对齐
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1U);                                         //规则转换通道长度：1
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);          //触发源设置：软件触发
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);                                   //触发设置：开启规则转换触发
    adc_enable();                                                                               //ADC启动
    rt_thread_mdelay(1);                                                                        //延时稳定
    adc_calibration_enable();                                                                   //ADC使用内部校准
}
INIT_BOARD_EXPORT(Test_Adc_Init);

//开始一次AD转换
uint16_t Test_Adc_Sample(void)
{
    adc_regular_channel_config(0U, TEST_ADC_CHANNEL, ADC_SAMPLETIME_239POINT5);                 //设置测试通道至规则转换队列头，设置采样时间
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);                                           //软件触发使能，ADC开始转换
    while(!adc_flag_get(ADC_FLAG_EOC));                                                         //等待转换结束
    adc_flag_clear(ADC_FLAG_EOC);
    return (adc_regular_data_read());                                                           //返回转换结果
}

//ADC自动转换线程入口
void Test_Adc_Value_Update_Thread(void)
{
    //转换次数记录，转换结果累加
    uint32_t cunt = 0, data_cunt = 0;
    while (1)
    {
        if(cunt < TEST_ADC_SAMPLES_REPEATED_NUMBER)                                             //转换次数未满
        {
            data_cunt += Test_Adc_Sample();                                                     //进行一次转换并累加结果原始数据
            cunt ++;                                                                            //转换次数 +1
        }
        else                                                                                    //转换次数已满
        {
            adc_test_raw_data = data_cunt/TEST_ADC_SAMPLES_REPEATED_NUMBER ;                    //累加的原始数据求平均值
            adc_test_voltage = 3.3 / 4096 * adc_test_raw_data ;                                 //平均的累加数据转换为电压值
            data_cunt = 0 ;                                                                     //重新开始下一轮转换
            cunt = 0 ;
            rt_thread_mdelay(100);                                                              //释放线程
        }
    }
}

//上电后开启ADC自动转换线程
void Test_Adc_Value_Update_Thread_Init(void)
{
    rt_thread_t i = rt_thread_create("ADC", Test_Adc_Value_Update_Thread, RT_NULL, 512, 4, 10);
    rt_thread_startup(i);
}
INIT_APP_EXPORT(Test_Adc_Value_Update_Thread_Init);

//获取原始结果
uint16_t Test_Adc_Get_Raw(void)
{
    return adc_test_raw_data ;
}

//获取转换电压值
float Test_Adc_Get_Voltage(void)
{
    return adc_test_voltage ;
}