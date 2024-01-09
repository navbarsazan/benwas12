/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define right_Pin GPIO_PIN_3
#define right_GPIO_Port GPIOA
#define right_EXTI_IRQn EXTI3_IRQn
#define left_Pin GPIO_PIN_4
#define left_GPIO_Port GPIOA
#define left_EXTI_IRQn EXTI4_IRQn
#define ok_Pin GPIO_PIN_5
#define ok_GPIO_Port GPIOA
#define ok_EXTI_IRQn EXTI9_5_IRQn
#define page_Pin GPIO_PIN_6
#define page_GPIO_Port GPIOA
#define page_EXTI_IRQn EXTI9_5_IRQn
#define up_Pin GPIO_PIN_7
#define up_GPIO_Port GPIOA
#define up_EXTI_IRQn EXTI9_5_IRQn
#define auto_Pin GPIO_PIN_0
#define auto_GPIO_Port GPIOB
#define auto_EXTI_IRQn EXTI0_IRQn
#define reset_Pin GPIO_PIN_8
#define reset_GPIO_Port GPIOA
#define reset_EXTI_IRQn EXTI9_5_IRQn
#define esc_Pin GPIO_PIN_11
#define esc_GPIO_Port GPIOA
#define esc_EXTI_IRQn EXTI15_10_IRQn
#define pir_Pin GPIO_PIN_12
#define pir_GPIO_Port GPIOA
#define pir_EXTI_IRQn EXTI15_10_IRQn
#define down_Pin GPIO_PIN_15
#define down_GPIO_Port GPIOA
#define down_EXTI_IRQn EXTI15_10_IRQn
void manual(void);
void AUTOPILOT(void);
void second_buzzer(uint32_t lec);
void first_buzzer(void);

/* USER CODE BEGIN Private defines */
void ADC_CHECK(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
