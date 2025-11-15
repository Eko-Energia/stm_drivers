/**
  ******************************************************************************
  * @file    adc_driver.h
  * @author  Bartosz Rychlicki
  * @Title   Universal driver for ADC peripheral
  * @brief   This file contains common defines, flags and macros that are used to prevent high quality of driver's functionalities.
  * 		 All flags, macros and typedefs are built to sense ADC settings and its linked DMA settings
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 AGH Eko-Energy.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32_family.h"

/* Private Macros ------------------------------------------------------------------- */
#define ADC_CCR_ADDR_F2XX 		   ((volatile uint32_t*)0x40012304)		// Address of CCR register for ADC


#if defined(STM32F1_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE (__HANDLE__) 																     \
											if((((__HANDLE__)->Instance->CR1 >> 16) & 0b1111) == 0b0000){ 			 \
												return 0;													 	 	 \
											}else{ 																     \
												return 1;															 \

	#define __ADC_IS_CONV_STARTED  (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR) >> 4) & 0b1);						 \


	#define __ADC_IS_DMA_ENABLED   (__HANDLE__)																		 \
											return((((__HANDLE__)->Instance->CR2) >> 8) & 0b1);						 \

	#define __ADC_RESOLUTION 	   (__HANDLE__)																	     \
											return 4095;															 \

	#define __ADC_DMA_MODE 		   (__HANDLE__)																		 \
											return (((__HANDLE__)->DMA_Handle->Init.Mode >> 8) & 0b1);			 	 \

	#define __ADC_EOC			   (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR >> 1) & 0b1);						 \

	#define __ADC_MODE			   (__HANDLE__)																	     \
											return (((__HANDLE__)->Instance->CR2 >> 1) & 0b1);						 \

#elif defined(STM32F2_FAMILY)



	#define __ADC_IS_DMA_MULTIMODE (__HANDLE__) 																     \
											if((*(ADC_CCR_ADDR_F2XX) & 0x1F) == 0){ 				 				 \
												return 0;													 	 	 \
											}else{ 						 										     \
												return 1;															 \

	#define __ADC_IS_CONV_STARTED  (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR) >> 4) & 0b1);						 \


	#define __ADC_IS_DMA_ENABLED   (__HANDLE__)																		 \
											return((((__HANDLE__)->Instance->CR2) >> 8) & 0b1);						 \

	#define __ADC_RESOLUTION 		(__HANDLE__)																	 \
											if((((_HANDLE__)->Instance->CR1 >> 24) & 0b11) == 0b00){				 \
												return 4095;														 \
											}else if((((_HANDLE__)->Instance->CR1 >> 24) & 0b11) == 0b01){			 \
												return 1023;														 \
											}else if((((_HANDLE__)->Instance->CR1 >> 24) & 0b11) == 0b10){			 \
												return 255;															 \
											}else{																	 \
												return 63;															 \
											}


	#define __ADC_DMA_MODE 		   (__HANDLE__)																		 \
											return (((__HANDLE__)->DMA_Handle->Init.Mode) & 0b1);			 		 \

	#define __ADC_EOC			   (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR >> 1) & 0b1);						 \

	#define __ADC_MODE			   (__HANDLE__)																	     \
											return (((__HANDLE__)->Instance->CR2 >> 1) & 0b1);				     	 \

#elif defined(STM32F3_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE (__HANDLE__) 																     \
											if((((__HANDLE__)->DMA_Handle->Instance->CCR) & 0b1111) == 0b0000){ 	 \
												return 0;													 	 	 \
											}else{ 																     \
												return 1;															 \

	#define __ADC_IS_CONV_STARTED  (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR) >> 4) & 0b1);						 \


	#define __ADC_IS_DMA_ENABLED   (__HANDLE__)																		 \
											return((((__HANDLE__)->Instance->CFGR)) & 0b1);						     \

	#define __ADC_RESOLUTION 		(__HANDLE__)																	 \
											if((((_HANDLE__)->Instance->CFGR >> 3) & 0b11) == 0b00){				 \
												return 4095;														 \
											}else if((((_HANDLE__)->Instance->CFGR >> 3) & 0b11) == 0b00){			 \
												return 1023;														 \
											}else if((((_HANDLE__)->Instance->CFGR >> 3) & 0b11) == 0b00){			 \
												return 255;															 \
											}else{																	 \
												return 63;


	#define __ADC_DMA_MODE 		   (__HANDLE__)																		 \
											return (((__HANDLE__)->Intance->CFGR >> 1) & 0b1);			             \

	#define __ADC_EOC			   (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->ISR >> 1) & 0b1);						 \

	#define __ADC_MODE			   (__HANDLE__)																	     \
											return (((__HANDLE__)->Instance->CFGR >> 13) & 0b1);					 \


#elif defined(STM32F4_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE (__HANDLE__) 																     \
											if((((__HANDLE__)->DMA_Handle->Instance->CCR) & 0b1111) == 0b0000){ 	 \
												return 0;													 	 	 \
											}else{ 																     \
												return 1;															 \


	#define __ADC_IS_CONV_STARTED  (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR) >> 4) & 0b1);						 \


	#define __ADC_IS_DMA_ENABLED   (__HANDLE__)																		 \
											return((((__HANDLE__)->Instance->CR2) >> 8) & 0b1);						 \

	#define __ADC_RESOLUTION 		(__HANDLE__)																	 \
											if((((_HANDLE__)->Instance->CR1 >> 3) & 0b11) == 0b00){					 \
												return 4095;														 \
											}else if((((_HANDLE__)->Instance->CR1 >> 3) & 0b11) == 0b00){			 \
												return 1023;														 \
											}else if((((_HANDLE__)->Instance->CR1 >> 3) & 0b11) == 0b00){			 \
												return 255;															 \
											}else{																	 \
												return 63;															 \
											}																		 \


	#define __ADC_DMA_MODE 		   (__HANDLE__)																		 \
											return (((__HANDLE__)->DMA_Handle->Init.mode));							 \

	#define __ADC_EOC			   (__HANDLE__)																		 \
											return (((__HANDLE__)->Instance->SR >> 1) & 0b1);						 \

	#define __ADC_MODE			   (__HANDLE__)																	     \
											return (((__HANDLE__)->Instance->CFGR >> 13) & 0b1);					 \

#endif



// Exported structs
#if (DMA_IsMultimode == 1)
	typedef struct{
		uint32_t BufferMultiMode[16];
		uint16_t BufferADC1[16];
		uint16_t BufferADC2[16];

	}DMA_BufferTypeDef;

#else
	typedef struct{
			uint16_t BufferADC[16];				// Buffer for all ranks

		}DMA_BufferTypeDef;

#endif

/* Private Typedefs ------------------------------------------------------------------- */
typedef struct{

	uint8_t channels[16];

}ADC_ChannelsTypeDef;



extern ADC_ChannelsTypeDef chadc;


/* Private functions Prototypes -------------------------------------------------------  */
uint32_t ADC_ReadChannel(ADC_HandleTypeDef* hadc, uint32_t channel);

float ADC_GetValue(ADC_HandleTypeDef* hadc, float max, uint32_t channel);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

void ADC_Config_GetRanksOfChannels(ADC_HandleTypeDef* hadc);

uint8_t ADC_GetRank(uint8_t channel);



#endif /* INC_ADC_DRIVER_H_ */
