#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "main.h"

#define TEST_ADC_GPIO_PERCLK                RCU_GPIOA
#define TEST_ADC_GPIO_PORT                  GPIOA
#define TEST_ADC_GPIO_PIN                   GPIO_PIN_1
#define TEST_ADC_CHANNEL                    ADC_CHANNEL_1
#define TEST_ADC_PERCLK                     RCU_ADC

#define TEST_ADC_SAMPLES_REPEATED_NUMBER    100

void Test_Adc_Init(void);
uint16_t Test_Adc_Init_Sample(void);
void Test_Adc_Value_Update_Thread(void);
void Test_Adc_Value_Update_Thread_Init(void);
uint16_t Test_Adc_Get_Raw(void);
float Test_Adc_Get_Voltage(void);

#endif