/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
#include "tim.h"
#include "i2c.h"
extern uint8_t CR ; 
extern uint8_t TUI;
extern int sige;
uint8_t p=0;
extern uint8_t out_al;
extern uint32_t lev;
uint8_t p1=0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define reset_Pin GPIO_PIN_8
#define relay_on    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_SET)
#define relay_off    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_RESET)
#define MANUAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_SET)
#define MANUAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_RESET)
#define AUTOPILOT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_SET)
#define AUTOPILOT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_RESET)
#define PIR_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_SET)
#define PIR_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_RESET)
#define INTERNAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_SET)
#define INTERNAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_RESET)
#define EXT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_SET)
#define EXT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_RESET)
#define manu  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_0  )
uint32_t silent1=0;

 uint8_t yg=1;
uint8_t h=0;
extern uint8_t TIMO;
extern uint8_t dg;
extern uint8_t sw;

uint8_t lev1=0;
uint8_t FGK=0;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
extern uint8_t TX_Buffer7[1];
extern	float AD_AC;
extern  float AD_DC;
 
extern uint8_t dtc;
extern uint8_t REP;


  
/* Private variables ---------------------------------------------------------*/


extern I2C_HandleTypeDef hi2c1;


  
extern uint8_t hg;
extern int rese;
extern int rese;
  extern uint16_t KEY;
extern char MENU[20];
extern uint16_t gpi;
extern float frequency ;
extern uint16_t KEY ;
 uint8_t STAR =0;
extern uint8_t JU ;

 uint8_t CONT=0 ;
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
 
/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
		  HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}
/* TIM3 init function */

/* TIM4 init function */
  void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
	  HAL_TIM_Base_Start_IT(&htim4);

}
  void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72000 ;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
		  HAL_TIM_Base_Start_IT(&htim3);

  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* TIM4 interrupt Init */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
}
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* TIM4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
}
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	    if(htim==&htim2){		
			 ADC_CHECK();
				if(sige==1){
 
		
					  
				sige=1;
    }
					if(dtc==1 && p==1){
				
				 if(h==0){
					 h=1;
					 TX_Buffer7[0]=~((~TX_Buffer7[0])|0x08);
					  HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
					 yg=1;
				 }
				 else{
					 TX_Buffer7[0]= (( TX_Buffer7[0])|0x08);
					  HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
					 h=0;
				 }
				
			}
			else{
				if(yg==1 && p==1){
						TX_Buffer7[0]= (( TX_Buffer7[0])|0x08);
					  HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
					 h=0;
					yg=0;
				}

			}
						
				if(p==100){
					p=0;
				}
					p++;
				 
    				/*	if(dg==1 && p1==100){
								  lev1++;
						  if(lev1%2==0){	
							 INTERNAL_ON;
             
							}
							else{
								 INTERNAL_OFF;	
							}
									 }*/

				  				if(p1==100){
					       p1=0;
								if(KEY==reset_Pin){
                 INTERNAL_OFF;
					       KEY=0;
									dg=0;
     
			}
				 }
									
				         	p1++;
			 }
    if(htim==&htim3){
			 	//TX_Buffer7[0]=2;
			   HAL_TIM_Base_Stop(&htim3);
								rese=1;
			  // ADC_CHECK();

			CONT=0;

 			if(  HAL_GPIO_ReadPin( GPIOA,  gpi)==0){

 				  KEY=gpi;
				
          if(KEY==auto_Pin){
						
						AUTOPILOT();
				    JU=1;		
						hg=1;
					 INTERNAL_OFF;
	        EXT_OFF;
						 TX_Buffer7[0]=((TX_Buffer7[0])|0x20);//LED OFF
					}

		}
	}
		    if(htim==&htim4){
 			if(  out_al==1){
							lev+=1;
				if(KEY==reset_Pin){
            silent1++;
					   KEY=0;}
				if(silent1>=1){
				  silent1=0;
			    INTERNAL_OFF;
	        EXT_OFF;
					out_al=0;
				
					TX_Buffer7[0]=((TX_Buffer7[0])|0x20);
			    HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
				  TX_Buffer7[0]=((TX_Buffer7[0])|0x10);
					HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);

				  lev=0;

				}
        else if(lev<120){
			   	first_buzzer();

				}
				else if(lev>=120){
					 sw=1;
					second_buzzer();

				}
				
				
				
			}
					   if(manu==1&& hg==1){
					   manual();

							   // ADC_CHECK();

							  JU=1;		
							hg=0;
						 INTERNAL_OFF;
	           EXT_OFF;
					
	
			}
			if(REP==30){	
           			
  			if(  dtc==1 ){			
             dtc=0;
			}
				else{
			 KEY=0;
 					
				}
				REP=0;
			}

				if(STAR==1){//THIS PART IS USED THAT IF USER NOT USING THE MENU ABOVE 30SEC IT WILL BACK TO THE HOURS AND DATE DISPLAY AUTOMATICALLY
					if(CONT==30){
						   //ADC_CHECK();

 						KEY=esc_Pin;	
 					}
	    	if(CONT==31){
						
						STAR=0;
						KEY=esc_Pin;	
						CONT=0;
					}

					 CONT+=1;
				
				}
				
			REP+=1;
 
		   if(AD_AC<0XdfA  ){
				       TX_Buffer7[0]=~((~TX_Buffer7[0])|0x40);

			 }	
				else if(AD_AC>0XdfA ) {
						  TX_Buffer7[0]=((TX_Buffer7[0])|0x40);
				}
		  if(AD_DC<0XCFA   ){
				    TX_Buffer7[0]=~((~TX_Buffer7[0])|0x80);

 			 }	
				   else if(AD_DC>0XCFA  ) {
						 TX_Buffer7[0]= (( TX_Buffer7[0])|0x80);
				}
					 

	       __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
              if(TIMO==1){
				  HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,10);
							}
				
		}
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
