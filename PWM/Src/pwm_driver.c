#include "pwm_driver.h"
#include"main.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

volatile uint32_t IC_Val1 = 0;
volatile uint32_t IC_Val2 = 0;
volatile uint8_t Capture_count = 0;

void PWM_Initialize(PWM_Signal* signal,int frequency) {
	signal->PWM_Width = 69.f;
	signal->Read_Flag = false;
	signal->Frequency = frequency;
}


void PWM_Update(TIM_HandleTypeDef *htim, PWM_Signal *PWM, uint32_t channel)
{
    if (Capture_count == 0)
    {
        IC_Val1 = HAL_TIM_ReadCapturedValue(htim, channel);
        if (PWM->Read_Flag)
        {
            PWM->PWM_Width = (float)IC_Val2 / ((float)IC_Val1);
        }
        __HAL_TIM_SET_COUNTER(htim, 0);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, channel, TIM_INPUTCHANNELPOLARITY_FALLING);
        Capture_count = 1;
    }
    else
    {
        IC_Val2 = HAL_TIM_ReadCapturedValue(htim, channel);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, channel, TIM_INPUTCHANNELPOLARITY_RISING);
        Capture_count = 0;
    }

    PWM->Read_Flag = true;
}
