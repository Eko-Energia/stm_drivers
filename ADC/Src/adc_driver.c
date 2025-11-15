#include "adc_driver.h"
#include "stm32f1xx_hal_mock_adc.h"

ADC_ChannelsTypeDef chadc;

uint32_t ADC_ReadChannel(ADC_HandleTypeDef* hadc,uint32_t channel){
    uint32_t retval;

    HAL_ADC_Start(hadc);

    for(int i = 0 ; i <= channel; ++i){
        retval = HAL_ADC_GetValue(hadc);
    }
    
    HAL_ADC_Stop(hadc);

    return retval;
}


float ADC_GetValue(ADC_HandleTypeDef* hadc, float max, uint32_t channel){

    // error handler
    if(hadc == NULL)
        return -1.0f;

    if(channel < 1)
        return -1.0f;
    
    uint32_t adc_value;

    
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, 1000);

    adc_value = ADC_ReadChannel(hadc, channel);

    return (adc_value/4095 * max);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // Handle ADC conversion complete callback
        hadc->State = HAL_ADC_STATE_READY;
    }
}


void ADC_Config_GetRanksOfChannels(ADC_HandleTypeDef* hadc){
	uint32_t numberOfConversions = ((hadc->Instance->SQR1 >> 20) & 0xF) + 1;

	for(int i = 0; i < numberOfConversions; ++i){

		if(i > 6 && i < 13){
			chadc.channels[i] = ((hadc->Instance->SQR2 >> (5 * (i - 6))) & 0x1F);
		}else if(i > 12){
			chadc.channels[i] = ((hadc->Instance->SQR2 >> (5 * (i - 2 * 6))) & 0x1F);
		}else{
			chadc.channels[i] = ((hadc->Instance->SQR3 >> (5 * i)) & 0x1F);
		}
		if(i == 16)
			return;
	}
}

uint8_t ADC_GetRank(uint8_t channel){
	for(uint8_t i = 0; i < (sizeof(chadc.channels)/sizeof(chadc.channels[0])); ++i){
		if(chadc.channels[i] == channel){
			return i;
		}
	}
	return -1;
}