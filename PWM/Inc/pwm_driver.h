#ifndef PWM_SIGNAL_H
#define PWM_SIGNAL_H

#include "main.h"
#include <math.h>
#include <stdbool.h>


typedef struct {
    uint32_t Frequency;
    float PWM_Width;
    bool Read_Flag;
} PWM_Signal;

extern volatile uint32_t IC_Val1;
extern volatile uint32_t IC_Val2;
extern volatile uint8_t Capture_count;

void PWM_Initialize(PWM_Signal* signal, int frequency);
void PWM_Update(TIM_HandleTypeDef *htim, PWM_Signal *PWM, uint32_t channel);

#endif /* PWM_SIGNAL_H */
