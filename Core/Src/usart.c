/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "EVENT_SAVE.h"
#include "string.h"
#include "stdio.h"
extern int sw;
uint8_t temp1=1;
uint8_t temp2=1;
uint8_t temp3=1;
 uint8_t moh1=0;
uint8_t moh2=0;
uint8_t moh3=0;
  DMA_HandleTypeDef hdma_usart1_rx;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 #define res        IWDG->KR  = 0xAAAA;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#include "tim.h"
extern uint8_t CR ; 
extern uint8_t TUI;
extern int sige;
  uint8_t dg=0;;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define relay_on    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_SET)
#define relay_off    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_RESET)
#define MANUAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_SET)
#define MANUAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_RESET)
#define AUTOPILOT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_SET)
#define AUTOPILOT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_RESET)
#define INTERNAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_SET)
#define INTERNAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_RESET)
#define EXT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_SET)
#define EXT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_RESET)
#define manu  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_0  )
 
  extern uint8_t TIMO;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
uint8_t RxBuf1[100]; 
 uint8_t TX_Buffer7[1]={0xff} ;


 uint8_t dtc;

 
/* Private variables ---------------------------------------------------------*/


extern int rese;

  extern uint16_t KEY;
extern char MENU[20];
extern uint16_t gpi;
extern float frequency ;
extern uint16_t KEY ;
 
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */



/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 4800;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
     hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}



void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	
	if (huart->Instance == USART1)
	{
		dtc=1;
		  // ADC_CHECK();

			  if(RxBuf1[0]=='T' && RxBuf1[1]=='!'){//comp1--led1
 
					    TX_Buffer7[0]=~((~TX_Buffer7[0])|0x01);
					    if(temp1==1){
								event_save(1);
								temp1=0;
								dg=1;
								moh1=1;
								
							}
				}
				else if(RxBuf1[0]=='O' && RxBuf1[1]=='!'){//comp1--led1
 
					    TX_Buffer7[0]=((TX_Buffer7[0])|0x01);
					    temp1=1;
              if(moh3==0 && moh2==0){
					    dg=0;
							}
				}
	 	      if(RxBuf1[2]=='T' && RxBuf1[3]==0x22){//comp2--led2

							 
					    TX_Buffer7[0]=~((~TX_Buffer7[0])|0x02);
						  
						    moh2=1;
							 if(temp2==1){
								event_save(2);
								temp2=0;
								  dg=1;
								
							}
					}
			  else if(RxBuf1[2]=='O' && RxBuf1[3]==0x22){//comp2--led2
					
					    TX_Buffer7[0]=((TX_Buffer7[0])|0x02);
					    temp2=1;
					    
					  if(moh1==0 && moh3==0){
					    dg=0;
							}
					
				}							
	 	      if(RxBuf1[4]=='T' && RxBuf1[5]==0x23){//comp3--led3
					    TX_Buffer7[0]=~((~TX_Buffer7[0])|0x04);
						    moh3=1;
					    
							 if(temp3==1){
								event_save(3);
								 	dg=1;
								
							}
					}
			 else if(RxBuf1[4]=='O' && RxBuf1[5]==0x23){//comp3--led3
					 if(moh2==0 && moh1==0){
					    dg=0;
							}
 					    TX_Buffer7[0]=((TX_Buffer7[0])|0x04);
				    	temp3=1;
				}				 						
						 
							
				  if(RxBuf1[0]=='c'  && RxBuf1[1]=='a' && RxBuf1[2]=='l' && RxBuf1[3]=='l' && RxBuf1[4]=='o' && RxBuf1[5]=='n' ){//fail----led4
					
					EXT_ON;
					
				}
				 if(RxBuf1[0]=='c'  && RxBuf1[1]=='a' && RxBuf1[2]=='l' && RxBuf1[3]=='l' && RxBuf1[4]=='o' && RxBuf1[5]=='f' && sw==0){//fail----led4
					
					EXT_OFF;
	 
				}					
	}
  		  memset(RxBuf1,0,10);
 
		  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *) RxBuf1, 10);
		 __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
 }
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
