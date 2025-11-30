/**
  ******************************************************************************
  * @file    adc_driver.h
  * @author  Bartosz Rychlicki

  * @Title   Universal driver for ADC peripheral (Built for F1, F2, F3 and F4 families, but can be implemented for all families)

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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------*/
#include "main.h"
#include "stm32_family.h"
//#include "stm32f105xc.h"

/* Exported Macros (Object Type)---------------------------------------------------------- */
#define ADC_MAX_CHANNELS       16
#define ADC_AVERAGED_MEASURES  5
#define ADC_BUFF_SIZE (ADC_MAX_CHANNELS * ADC_AVERAGED_MEASURES)

/* Exported Private Variables---------------------------------------------------------- */
extern 			ADC_HandleTypeDef   hadc1;
static volatile int                 ADC_CONVERTED_CHANNELS = 1;

/* Private Typedefs ------------------------------------------------------------------- */
/**
  * @brief  DMA buffer typedef for ADCs in multimode
  */
typedef union{
		uint32_t BufferMultiMode[ADC_BUFF_SIZE];
		uint16_t BufferADC_Master[ADC_BUFF_SIZE];
		uint16_t BufferADC_Slave[ADC_BUFF_SIZE];

}DMA_DualmodeBufferTypeDef;

/**
  * @brief  DMA buffer typedef for ADCs in independent mode
  */
typedef union{
	uint16_t BufferADC[ADC_BUFF_SIZE];

}DMA_IndependentModeBufferTypeDef;

typedef struct{

	DMA_DualmodeBufferTypeDef 		 ddma;				// dma buffer for dualmode

	DMA_IndependentModeBufferTypeDef idma;				// dma buffer for independent mode

	uint32_t ADC_Buff[ADC_BUFF_SIZE];								// adc buff for all channels, in situation ADC is single shot mode

}ADC_BufferTypeDef;


/**
  * @brief  ADC's channels' ranks definotion
  */
typedef struct{

	uint8_t channels[ADC_MAX_CHANNELS];						// Channels for all ranks | auto detect

}ADC_ChannelsTypeDef;


/**
  * @brief  ADC Status structures definition
  */
typedef enum{
	ADC_Timeout = 0,
	ADC_Busy,
	ADC_NotStarted,
	ADC_DMA_NotEnabled,
	ADC_DMA_NotInDualMode,
	ADC_CalibrationFailed,
	ADC_OK,
	ADC_Error

}ADC_StatusTypeDef;


/* Private Macros (Function type)------------------------------------------------------------------- */
#if defined(STM32F1_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE(__HANDLE__)                                              												\
											((((((__HANDLE__)->Instance->CR1      >> ADC_CR1_DUALMOD_Pos) & 0xF) == 0U) ? 0U : 1U))

	#define __ADC_IS_CONV_STARTED(__HANDLE__)                                               												\
											(((((__HANDLE__)->Instance->SR)       >> ADC_SR_STRT_Pos ) & 0x1U))

	#define __ADC_IS_DMA_ENABLED(__HANDLE__)                                                												\
											(((((__HANDLE__)->Instance->CR2)      >> ADC_CR2_DMA_Pos) & 0x1U))

	#define __ADC_RESOLUTION(__HANDLE__)                                                    												\
											(4095U)

	#define __ADC_DMA_MODE(__HANDLE__)                                                      												\
											((((__HANDLE__)->DMA_Handle->Instance->CCR >> DMA_CCR_CIRC_Pos) & 0x1U))

	#define __ADC_EOC(__HANDLE__)                                                           												\
											((((__HANDLE__)->Instance->SR          >> ADC_SR_EOC_Pos) & 0x1U))

	#define __ADC_MODE(__HANDLE__)                                                          												\
											((((__HANDLE__)->Instance->CR2         >> ADC_CR2_CONT_Pos) & 0x1U))

#elif defined(STM32F2_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE                                                          												\
											((READ_REG(ADC_COMMON->CCR, ADC_CCR_MULTI_Msk) == ADC_CCR_MULTI_0) ? 0U : 1U)

	#define __ADC_IS_CONV_STARTED(__HANDLE__)                                               												\
											(((((__HANDLE__)->Instance->SR) >> ADC_SR_STRT_Pos) & 0x1U))

	#define __ADC_IS_DMA_ENABLED(__HANDLE__)                                                												\
											(((((__HANDLE__)->Instance->CR2) >> ADC_CR2_DMA_Pos) & 0x1U))

	#define __ADC_RESOLUTION(__HANDLE__)                                                    												\
											(((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b00) ? 4095U : 				\
											 ((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b01) ? 1023U : 				\
											 ((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b10) ? 255U  : 63U )

	#define __ADC_DMA_MODE(__HANDLE__)                                                      												\
											((((__HANDLE__)->DMA_Handle->Instance->CCR >> DMA_CCR_CIRC_Pos) & 0x1U))

	#define __ADC_EOC(__HANDLE__)                                                           												\
											((((__HANDLE__)->Instance->SR >> ADC_SR_EOC_Pos) & 0x1U))

	#define __ADC_MODE(__HANDLE__)                                                          												\
											((((__HANDLE__)->Instance->CR2 >> ADC_CR2_CONT_Pos) & 0x1U))

#elif defined(STM32F3_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE                                                          												\
											((READ_REG(ADC_COMMON->CCR, ADC12_CCR_MULTI_Msk) == 0U) ? 0U : 1U)

	#define __ADC_IS_CONV_STARTED(__HANDLE__)                                               												\
											(((((__HANDLE__)->Instance->CR >> ADC_CR_ADSTART_Pos) & 0x1U)))

	#define __ADC_IS_DMA_ENABLED(__HANDLE__)                                                												\
											((READ_BIT((__HANDLE__)->Instance->CFGR, ADC_CFGR_DMAEN)))

	#define __ADC_RESOLUTION(__HANDLE__)                                                    												\
											(((((__HANDLE__)->Instance->CFGR >> ADC_CFGR_RES_Pos) & 0b11) == 0b00) ? 4095U : 			\
											 ((((__HANDLE__)->Instance->CFGR >> ADC_CFGR_RES_Pos) & 0b11) == 0b01) ? 1023U : 			\
											 ((((__HANDLE__)->Instance->CFGR >> ADC_CFGR_RES_Pos) & 0b11) == 0b10) ? 255U  : 63U )

	#define __ADC_DMA_MODE(__HANDLE__)                                                      												\
											(((((__HANDLE__)->Instance->CFGR >> ADC_CFGR_DMACFG_Pos) & 0x1U)))

	#define __ADC_EOC(__HANDLE__)                                                           												\
											((((__HANDLE__)->Instance->ISR >> ADC_ISR_EOC_Pos) & 0x1U))

	#define __ADC_MODE(__HANDLE__)                                                          												\
											((((__HANDLE__)->Instance->CFGR >> ADC_CFGR_CONT_Pos) & 0x1U))

#elif defined(STM32F4_FAMILY)

	#define __ADC_IS_DMA_MULTIMODE                                                          												\
											((READ_REG(ADC_COMMON->CCR, ADC_CCR_MULTI_Msk) == ADC_CCR_MULTI_0) ? 0U : 1U)

	#define __ADC_IS_CONV_STARTED(__HANDLE__)                                               												\
											(((((__HANDLE__)->Instance->SR) >> ADC_SR_STRT_Pos) & 0x1U))

	#define __ADC_IS_DMA_ENABLED(__HANDLE__)                                                												\
											(((((__HANDLE__)->Instance->CR2) >> ADC_CR2_DMA_Pos) & 0x1U))

	#define __ADC_RESOLUTION(__HANDLE__)                                                    												\
											(((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b00) ? 4095U : 				\
											 ((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b01) ? 1023U : 				\
											 ((((__HANDLE__)->Instance->CR1 >> ADC_CR1_RES_Pos) & 0b11) == 0b10) ? 255U  : 63U )

	#define __ADC_DMA_MODE(__HANDLE__)                                                      												\
											((((__HANDLE__)->DMA_Handle->Instance->CR >> DMA_SxCR_CIRC_Pos) & 0x1U))

	#define __ADC_EOC(__HANDLE__)                                                           												\
											((((__HANDLE__)->Instance->SR >> ADC_SR_EOC_Pos) & 0x1U))

	#define __ADC_MODE(__HANDLE__)                                                          												\
											((((__HANDLE__)->Instance->CR2 >> ADC_CR2_CONT_Pos) & 0x1U))


#endif


/* Private functions Prototypes -------------------------------------------------------  */
HAL_StatusTypeDef        ADC_Init(ADC_HandleTypeDef* hadc);

ADC_StatusTypeDef        ADC_ReadChannel(ADC_HandleTypeDef* hadc, uint8_t channel, uint16_t*  retval);

__weak ADC_StatusTypeDef ADC_GetValue(ADC_HandleTypeDef* hadc, float max, uint8_t channel, float * retval);

void                     HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

ADC_StatusTypeDef        ADC_Config_GetRanksOfChannels(ADC_HandleTypeDef* hadc);

ADC_StatusTypeDef        ADC_GetRank(ADC_ChannelsTypeDef *cadc, uint8_t channel, uint8_t* rank);

ADC_StatusTypeDef        ADC_Averaging(ADC_HandleTypeDef* hadc, ADC_BufferTypeDef* badc, uint8_t channel , uint16_t* retval);


#endif /* INC_ADC_DRIVER_H_ */
