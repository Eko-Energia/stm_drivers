
/**
  ******************************************************************************
  * @file      adc_driver.c
  * @author    Bartosz Rychlicki
  * @Title     Universal driver for ADC peripheral
  * @brief     This file contains common functions' bodies with ADC Driver's functions implementation
  ******************************************************************************
  * @attention Error codes are called when exact incorrect use of function is made
  *
  * Copyright (c) 2025 AGH Eko-Energy.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/


#include "adc_driver.h"

/* Private Variables-------------------------------------------------------  */
ADC_ChannelsTypeDef    cadc;
ADC_BufferTypeDef 	   badc;
/**
  * @brief ADC1 Initialization Function, does calibration
  * @param  hadc   - pointer to ADC handle
  * @retval status - HAL status
  */
HAL_StatusTypeDef ADC_Init(ADC_HandleTypeDef* hadc){

	// check if ADC is not started
	if(__ADC_IS_CONV_STARTED(hadc) == 0){
		HAL_ADC_Start(hadc);
	}

	// check if dma is enabled
	if(__ADC_DMA_MODE(hadc) != 0){

		// check if multimode is enabled
		if(__ADC_MULTIMODE_IS_ENABLED(hadc) != 0){

			// starting DMA with ADC in dual mode
			if(HAL_ADCEx_MultiModeStart_DMA(hadc, badc.ddma.BufferMultiMode, ADC_CONVERTED_CHANNELS) != HAL_OK){
				return ADC_Error;
			}

		}else{

			// starting DMA with ADC in Independent mode
			if(HAL_ADC_Start_DMA(hadc, (uint32_t*)badc.idma.BufferADC, ADC_CONVERTED_CHANNELS) != HAL_OK){
				return ADC_Error;
			}

		}

	}

	// launching calibration
	return HAL_ADCEx_Calibration_Start(hadc);
}

/**
  * @brief ADC Reading channel function
  * @param  hadc    - pointer to ADC handle
  * @param  channel - number of channel to be read
  * @param  retval  - pointer to variable, whose contains return value
  * @retval status  - HAL status if Reading channel went successfully
  */
ADC_StatusTypeDef ADC_ReadChannel(ADC_HandleTypeDef* hadc, uint8_t channel, uint16_t*  retval){

	ADC_StatusTypeDef status;

	if(__ADC_IS_CONV_STARTED(hadc) == 0){ // ADC not started
		return ADC_NotStarted;
	}
	if(channel < 0 || channel > 16){
		return ADC_Error;
	}

	uint8_t rank  = 0;

	if(ADC_GetRank(&cadc, channel, &rank) != ADC_OK){
		return ADC_Error;
	}


	if(__ADC_IS_DMA_ENABLED(hadc) == 0){  // DMA Disabled


		for(int i  = 0 ; i <= rank ; ++i){
			 if(__ADC_IS_DMA_MULTIMODE(hadc) == 0){  // single conversion | independent mode
				 badc.ADC_Buff[channel]          = HAL_ADC_GetValue(hadc);

			}else{									 // single conversion | dual mode
				 badc.ddma.BufferMultiMode[rank] = HAL_ADCEx_MultiModeGetValue(hadc);
			}
		}

		if(badc.ADC_Buff[channel] > __ADC_RESOLUTION(hadc) || badc.ADC_Buff[channel] < 0){
			return  ADC_Error;
		}

		status =  ADC_OK;

	}else{								  // DMA Enabled


		if(ADC_Averaging(hadc, &badc, channel, retval) != ADC_OK){ // averaging transfer
			return ADC_Error;
		}


		if(__ADC_MULTIMODE_IS_ENABLED(hadc) != 0){ // ADC in dual mode | DMA [ON]


			if(__ADC_DMA_MODE(hadc) == 0){
				if(HAL_ADCEx_MultiModeStart_DMA(hadc, badc.ddma.BufferMultiMode, ADC_CONVERTED_CHANNELS) != HAL_OK){
					return ADC_Error;
				}
			}

		}else{									   // ADC in independent mode | DMA [ON]


			if(__ADC_DMA_MODE(hadc) == 0){
				if(HAL_ADC_Start_DMA(hadc, (uint32_t*)badc.idma.BufferADC, ADC_CONVERTED_CHANNELS) != HAL_OK){
					return ADC_Error;
				}
			}
		}


	}


	return status;
}

/**
  * @brief ADC Basic function of returning value
  * 	   if calculating value's logic is different, then developer should implement his function
  * @param  hadc    - pointer to ADC handle
  * @param  channel - number of channel to be read
  * @param  retval  - pointer to variable, whose contains return value
  * @retval status  - HAL status if Reading channel went successfully
  */
__weak ADC_StatusTypeDef  ADC_GetValue(ADC_HandleTypeDef* hadc, float max, uint8_t channel, float * retval){
	uint16_t binary_value = 0;
	uint32_t adc_resolutiion = __ADC_RESOLUTION(hadc);

	if(ADC_ReadChannel(hadc, channel, &binary_value) != ADC_OK){
		return ADC_Error;
	}

	*retval = (float)binary_value / (float)adc_resolutiion * max;


	return ADC_OK;

}

/*
 * @brief Empty implementation of callback function | If body of this function should does some functionalities, then implementation is required
 */
void               HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){

	UNUSED(hadc); // unused variable to avoid warnings

}

/**
  * @brief ADC channels configuration function | auto detects ranks and overwrite ADC_ChannelsTypeDef object's content
  * @param  hadc    - pointer to ADC handle
  * @retval status  - ADC status
  */
ADC_StatusTypeDef  ADC_Config_GetRanksOfChannels(ADC_HandleTypeDef* hadc){

	uint32_t numberOfConversions = ((hadc->Instance->SQR1 >> 20) & 0xF) + 1;


	if(numberOfConversions > 16 || numberOfConversions < 0){
		return ADC_Error;
	}


	ADC_CONVERTED_CHANNELS = numberOfConversions;

	for(int i = 0; i < numberOfConversions; ++i){

		if(i > 6 && i < 13){
			cadc.channels[i] = ((hadc->Instance->SQR1 >> (5 * (i - 6))) & 0x1F);
		}else if(i > 12){
			cadc.channels[i] = ((hadc->Instance->SQR2 >> (5 * (i - 2 * 6))) & 0x1F);
		}else{
			cadc.channels[i] = ((hadc->Instance->SQR3 >> (5 * i)) & 0x1F);
		}

		if(cadc.channels[i] > 16 || cadc.channels[i] < 0){
			return ADC_Error;
		}

	}

	return ADC_OK;
}

/**
  * @brief ADC channels' ranks return function. In case of wanting channel's rank, function returns it
  * @param  hadc    - pointer to ADC handle
  * @retval status  - ADC status
  */
ADC_StatusTypeDef  ADC_GetRank(ADC_ChannelsTypeDef *cadc, uint8_t channel, uint8_t* rank){

	for(int i = 0 ; i <= ADC_MAX_CHANNELS; ++i ){
		if(cadc->channels[i] == channel){
			*rank = (uint8_t)i;

			break;
		}
	}

	if(*rank > 16 || *rank < 0){
		return ADC_Error;
	}

	return ADC_OK;
}

/**
  * @brief ADC averaging function. ADC's channels' values oscillate in 40 Hz, function averages measures from exact number of conversions.
  * 	   Macro: ADC_AVERAGED_MEASURES stores information about number of latest conversions to be measured
  * @param  hadc    - pointer to ADC handle
  * @param  badc    - ADC buffer, which stores converted values
  * @param  retval  - pointer to returning value
  * @retval status  - ADC status
  */
ADC_StatusTypeDef ADC_Averaging(ADC_HandleTypeDef* hadc, ADC_BufferTypeDef* badc, uint8_t channel , uint16_t* retval){
	uint64_t sum = 0; // sum of averaged values
	uint8_t rank;     // channel rank

	// Getting channel rank
	if(ADC_GetRank(&cadc, channel, &rank) != ADC_OK){
		return ADC_Error;;
	}

	if(__ADC_IS_DMA_MULTIMODE(hadc) != 0){ // ADC in dual mode
		if(sizeof(badc->idma.BufferADC)/sizeof(badc->idma.BufferADC[0]) < ADC_AVERAGED_MEASURES){
			return ADC_Error;
		}


	}else{								   // ADC in independent mode
		if(sizeof(badc->ddma.BufferMultiMode)/sizeof(badc->ddma.BufferMultiMode) < ADC_AVERAGED_MEASURES){
			return ADC_Error;
		}

		if(hadc->Instance == ADC1){

			// Extracting ADC1 values from dual mode buffer
			for(int  i = 0 ; i <= ADC_BUFF_SIZE ; ++i){
				badc->ddma.BufferADC_Master[i] = ((badc->ddma.BufferMultiMode[i] >> 16) & 0xFF);
			}

		}else if(hadc->Instance == ADC2){

			// Extracting ADC2 values from dual mode buffer
			for(int  i = 0 ; i <= ADC_BUFF_SIZE ; ++i){
				badc->ddma.BufferADC_Slave[i] = (badc->ddma.BufferMultiMode[i] & 0xFF);
			}

		}


	}


	int16_t id = 0; // current position of averaged value
	for( int i = 0; i <= ADC_AVERAGED_MEASURES; ++i){
		id = (i * ADC_AVERAGED_MEASURES + rank);

		// adding to sum variable next value correlated to current channel
		sum += ((__ADC_IS_DMA_MULTIMODE(hadc) == 0)
					 ? badc->idma.BufferADC[id] 							 // adding value of ADC in independent mode
				      :((hadc->Instance == ADC1)
					 ? badc->ddma.BufferADC_Master[id]
	                  : badc->ddma.BufferADC_Slave[id]));                   // adding value of ADC in dual mode | checking instance
	}

	*retval = (sum / ADC_AVERAGED_MEASURES); // averaging by dividing sum with number of averaged conversions

	return HAL_OK;
}





