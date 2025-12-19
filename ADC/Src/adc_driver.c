
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

// Private variables
// Container of ADC ranks to return rank's register while number of rank is given
static 			uint32_t ADC_RANKS_REGS[16] = {
    ADC_RANK1_REG, ADC_RANK2_REG, ADC_RANK3_REG, ADC_RANK4_REG,
    ADC_RANK5_REG, ADC_RANK6_REG, ADC_RANK7_REG, ADC_RANK8_REG,
    ADC_RANK9_REG, ADC_RANK10_REG, ADC_RANK11_REG, ADC_RANK12_REG,
    ADC_RANK13_REG, ADC_RANK14_REG, ADC_RANK15_REG, ADC_RANK16_REG
};

// Container of ADC ranks bit position to return provide correct flow of bit shifting
static 			uint32_t ADC_RANKS_BITPOS[16] = {
    ADC_RANK1_BITPOS, ADC_RANK2_BITPOS, ADC_RANK3_BITPOS, ADC_RANK4_BITPOS,
    ADC_RANK5_BITPOS, ADC_RANK6_BITPOS, ADC_RANK7_BITPOS, ADC_RANK8_BITPOS,
    ADC_RANK9_BITPOS, ADC_RANK10_BITPOS, ADC_RANK11_BITPOS, ADC_RANK12_BITPOS,
    ADC_RANK13_BITPOS, ADC_RANK14_BITPOS, ADC_RANK15_BITPOS, ADC_RANK16_BITPOS
};

/**
  * @brief  ADC1 Initialization Function, performs calibration and starts conversions.
  * @param  hadc  Pointer to ADC handle.
  * @param  badc  Pointer to ADC buffer configuration/structure.
  * @param  cadc  Pointer to ADC channels configuration/structure.
  * @retval ADC_StatusTypeDef  ADC driver status.
  */
ADC_StatusTypeDef ADC_Init(ADC_HandleTypeDef* hadc, ADC_BufferTypeDef* badc, ADC_ChannelsTypeDef* cadc){

	// check if ADC is started to stop it to calibrate ADC
	if(__ADC_IS_CONV_STARTED(hadc) != 0){
		if(HAL_ADC_Stop(hadc) != HAL_OK){
			return ADC_Error;
		}
	}



	// check if dual mode is enabled
	if(__ADC_IS_DMA_MULTIMODE(hadc) == 0){

		    // checking if DMA is enabled
			if(__ADC_IS_DMA_ENABLED(hadc) != 0){

				// starting DMA with ADC in Independent mode
				if(HAL_ADC_Start_DMA(hadc, (uint32_t*)badc->idma.BufferADC, ADC_BUFF_SIZE) != HAL_OK){
					return ADC_Error;
				}
			}
	}


	// launching calibration
	if(HAL_ADCEx_Calibration_Start(hadc) != HAL_OK){
		return ADC_Error;
	}

	// launching ADC
	if(HAL_ADC_Start(hadc) != HAL_OK){
		return ADC_Error;
	}

	// getting ranks config
	if(ADC_ConfigGetRanksOfChannels(hadc, cadc, badc)!= ADC_OK){
		return ADC_Error;
	}

	return ADC_OK; // returning positive status
}


/**
  * @brief ADC Init function, initialize ADC in dual mode | Should be called in init function of slave ADC
  * @param  hadc    - pointer to ADC Master handle
  * @param  badc    - pointer to ADC buffer structure used in dual mode
  * @retval status  - HAL status if init went successfully
  */
ADC_StatusTypeDef ADC_InitMultimode(ADC_HandleTypeDef* hadcMaster, ADC_BufferTypeDef* badc){

	// checking if correct parameter was provide
	if(hadcMaster->Instance != ADC1){
		return ADC_Error;
	}
	// checking if buff struct is initialized
	if(badc == NULL){
		return ADC_Error;
	}

	// starting calibration
	if(HAL_ADCEx_Calibration_Start(hadcMaster) != HAL_OK){
		return ADC_Error;
	}

	// launching dual mode conversion
	if(HAL_ADCEx_MultiModeStart_DMA(hadcMaster, badc->ddma.BufferMultiMode, ADC_BUFF_SIZE) != HAL_OK){
		return ADC_Error;
	}


	return ADC_OK;

}


/**
  * @brief ADC Reading channel function
  * @param  hadc    - pointer to ADC handle
  * @param  channel - number of channel to be read
  * @param  retval  - pointer to variable, whose contains return value
  * @retval status  - HAL status if Reading channel went successfully
  */
ADC_StatusTypeDef ADC_ReadChannel(ADC_HandleTypeDef* hadc, ADC_ChannelsTypeDef* cadc, ADC_BufferTypeDef* badc, uint8_t channel, uint16_t*  retval){


	// checking ADC status | is launched?
	if(__ADC_IS_CONV_STARTED(hadc) == 0){ // ADC not started
		return ADC_Error;
	}

	// security check | is given number of channel correct
	if(channel < 0 || channel > 16){
		return ADC_Error;
	}

	uint8_t rank  = 0; // initialize variable that stores the rank of the given channel

	// reading rank of given channel and writing it to correct variable
	if(ADC_GetRank(cadc, channel, &rank) != ADC_OK){
		return ADC_Error;
	}

	// checking status of DMA
	if(__ADC_IS_DMA_ENABLED(hadc) == 0){  // DMA Disabled

		// iterating through all ranks to read value from correct channel's rank in ADC without DMA
		for(int i  = 0 ; i <= rank ; ++i){

			 if(__ADC_IS_DMA_MULTIMODE(hadc) == 0){  // single conversion | independent mode

				 uint16_t value = 0;

				 // getting converted value
				 value = HAL_ADC_GetValue(hadc);

				 // checking if converted value is valid
				 if(value > __ADC_RESOLUTION(hadc) || value < 0){
					 return ADC_Error;
				 }

				 // overwriting value in buffer only if process of reading from given channel is executed
				 if(i == rank){
					 badc->ADC_Buff[rank] = value;
				 }

			}else{
				// single conversion | dual mode

				uint32_t value = 0;

				// getting converted value
				value = HAL_ADCEx_MultiModeGetValue(hadc);

				// checking if converted value is valid
				if(value > __ADC_RESOLUTION(hadc) || value < 0){
					 return ADC_Error;
				}

				// overwriting value in buffer only if process of reading from given channel is executed
				if(i == rank){
					value = HAL_ADCEx_MultiModeGetValue(hadc);
				}
			}
		}

		// security check | if converted value is higher than ADC's resolution or less than 0
		if(badc->ADC_Buff[channel] > __ADC_RESOLUTION(hadc) || badc->ADC_Buff[channel] < 0){
			return  ADC_Error;
		}

		//overwriting converted value of ADC | otherwise no assign of value will be conducted
		*(retval) = badc->ADC_Buff[rank];

		// re-launching ADC if its mode is non-continuous
		if(__ADC_MODE(hadc) == 0){
			if(HAL_ADC_Start(hadc) != HAL_OK){
				return ADC_Error;
			}
		}

	}else{								  // DMA Enabled

		// averaging converted values from given channel
		if(ADC_Averaging(hadc, badc, cadc, channel, retval) != ADC_OK){ // averaging transfer
			return ADC_Error;
		}

		// re-launching conversion for DMA in normal mode | with checking if ADC/ADCs are in independent or dual mode
		if(__ADC_IS_DMA_MULTIMODE(hadc) != 0){ // ADC in dual mode | DMA [ON]

			// re-launching ADC in dual mode conversion with DMA
			if(__ADC_DMA_MODE(hadc) == 0){
				if(HAL_ADCEx_MultiModeStart_DMA(hadc, badc->ddma.BufferMultiMode, ADC_BUFF_SIZE) != HAL_OK){
					return ADC_Error;
				}
			}

		}else{									   // ADC in independent mode | DMA [ON]

			// re-launching ADC in independent conversion with DMA
			if(__ADC_DMA_MODE(hadc) != 0){
				if(HAL_ADC_Start_DMA(hadc, (uint32_t*)badc->idma.BufferADC, ADC_BUFF_SIZE) != HAL_OK){
					return ADC_Error;
				}
			}
		}


	}


	return ADC_OK;
}

/**
  * @brief ADC Basic function of returning value
  * 	   if calculating value's logic is different, then developer should implement his function
  * @param  hadc    - pointer to ADC handle
  * @param  channel - number of channel to be read
  * @param  retval  - pointer to variable, whose contains return value
  * @retval status  - HAL status if Reading channel went successfully
  */
__weak ADC_StatusTypeDef  ADC_GetValue(ADC_HandleTypeDef* hadc, ADC_ChannelsTypeDef* cadc, ADC_BufferTypeDef* badc, float max, uint8_t channel, float * retval){

	uint16_t binaryType = 0; 							// init of variable which stores converted value from channel
	uint32_t adcResolutiion = __ADC_RESOLUTION(hadc);  // reading ADC resolution

	// reading channel's cconverted value
	if(ADC_ReadChannel(hadc, cadc, badc, channel, &binaryType) != ADC_OK){
		return ADC_Error;
	}

	// Basic math here | calculating float value with formula, example: voltage = binary/value/adc_resoltuion * maxVoltage
	*retval = max * ((float)binaryType / (float)adcResolutiion);


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
ADC_StatusTypeDef  ADC_ConfigGetRanksOfChannels(ADC_HandleTypeDef* hadc, ADC_ChannelsTypeDef* cadc, ADC_BufferTypeDef* badc){

	//Reading number of channels to be converted
	uint32_t numberOfConversions = ((uint8_t)(hadc->Instance->SQR1 >> 20)) + 1;


	// Security check
	if(numberOfConversions > ADC_MAX_CHANNELS){
		return ADC_Error;
	}

	// Overwriting macro which stores info of number of channels to be converted
	ADC_CONVERTED_CHANNELS = numberOfConversions;


	// reading ranks' assigned channels
	for(int i = 0; i < numberOfConversions; ++i){

			#if defined(ADC_SQR4_SQ15_Pos) // if core has 4 registers of SQRx

				switch(ADC_RANKS_REGS[i]){ // reading register to which rank is assigned
						case SQR_1:
							cadc->ranks[i] = ((hadc->Instance->SQR1 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR1
							break;
						case SQR_2:
							cadc->ranks[i] = ((hadc->Instance->SQR2 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR2
							break;
						case SQR_3:
							cadc->ranks[i] = ((hadc->Instance->SQR3 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR3
							break;
						case SQR_4:
							cadc->ranks[i] = ((hadc->Instance->SQR4 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR4
							break;
						default:
							break;
					}


			#else							// the rest of cores, for which driver is built, has only 3 registers of SQRx

				switch(ADC_RANKS_REGS[i]){  // reading register to which rank is assigned
					case SQR_1:
						cadc->ranks[i] = ((hadc->Instance->SQR1 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR1
						break;
					case SQR_2:
						cadc->ranks[i] = ((hadc->Instance->SQR2 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR2
						break;
					case SQR_3:
						cadc->ranks[i] = ((hadc->Instance->SQR3 >> ADC_RANKS_BITPOS[i]) & 0x1f); // extracting binary value on correct position in SQR3
						break;
					default:
						break;
				}

			#endif


	}

	return ADC_OK;
}

/**
  * @brief ADC channels' ranks return function. In case of wanting channel's rank, function returns it
  * @param  hadc    - pointer to ADC handle
  * @retval status  - ADC status
  */
ADC_StatusTypeDef  ADC_GetRank(ADC_ChannelsTypeDef *cadc, uint8_t channel, uint8_t* rank){

	// iterating though all buffer's elements to return given channel's rank
	for(int i = 0 ; i < ADC_MAX_CHANNELS; ++i ){
		if(cadc->ranks[i] == channel){
			*rank = (uint8_t)i;

			break;
		}
	}

	// Checking if read rank is correct | ADC has maximum 16 ranks
	if(*rank >= ADC_MAX_CHANNELS){
		return ADC_Error;
	}

	return ADC_OK;
}

/**
  * @brief ADC averaging function. ADC's channels' values oscillate in 40 Hz, function averages measures from exact number of conversions.
  * 	   Macro: ADC_AVERAGED_MEASURES stores information about number of latest conversions to be measured
  * @param  hadc    - pointer to ADC handle
  * @param  badc    - ADC buffer, which stores converted values
  * @param  retval  - pointer to returning value | overwrite value from 0 to 15
  * @retval status  - ADC status
  */
ADC_StatusTypeDef ADC_Averaging(ADC_HandleTypeDef* hadc, ADC_BufferTypeDef* badc, ADC_ChannelsTypeDef* cadc, uint8_t channel , uint16_t* retval){

	uint64_t sum = 0; // sum of values from averaged channel
	uint8_t rank;     // channel's rank

	// Getting channel rank
	if(ADC_GetRank(cadc, channel, &rank) != ADC_OK){
		return ADC_Error;
	}

	if(__ADC_IS_DMA_MULTIMODE(hadc) == 0){ // ADC in independent mode
		if(sizeof(badc->idma.BufferADC)/sizeof(badc->idma.BufferADC[0]) < ADC_AVERAGED_MEASURES){
			return ADC_Error;
		}


	}else{								   // ADC in dual mode

		if(hadc->Instance == ADC1){

			// Extracting ADC1 values from dual mode buffer
			for(int  i = 0 ; i < ADC_BUFF_SIZE ; ++i){
				badc->ddma.BufferADC_Master[i] = (uint16_t)((badc->ddma.BufferMultiMode[i] >> 16));
			}

		}else{

			// Extracting ADC2 values from dual mode buffer
			for(int  i = 0 ; i < ADC_BUFF_SIZE ; ++i){
				badc->ddma.BufferADC_Slave[i] = (uint16_t)((badc->ddma.BufferMultiMode[i]));
			}

		}


	}


	int id = 0; // current position of averaged value

	for( int i = 0; i < ADC_AVERAGED_MEASURES; ++i){
		id = (i * ADC_CONVERTED_CHANNELS + rank); // id calculation base on multiplying current iteration by number of conversions to be measures, cause DMA stores continuously conversion though channels until last index of DMA buffer occurs

		// security check | if calculated id is beyond array limits
		if(id >= ADC_BUFF_SIZE){
			return ADC_Error;
		}

		// adding to sum variable next value correlated to current channel
		sum += ((__ADC_IS_DMA_MULTIMODE(hadc) == 0)
					 ? badc->idma.BufferADC[id] 							 // adding value of ADC in independent mode
				      :((hadc->Instance == ADC1)
					 ? badc->ddma.BufferADC_Master[id]
	                  : badc->ddma.BufferADC_Slave[id]));                   // adding value of ADC in dual mode | checking instance
	}

	*retval = (uint16_t)(sum / ADC_AVERAGED_MEASURES); // averaging by dividing sum with number of averaged conversions

	return ADC_OK;
}





