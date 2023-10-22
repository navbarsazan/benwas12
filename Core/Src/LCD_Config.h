
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H 

#define _LCD_USE_FREERTOS 1
#define _LCD_COLS         20
#define _LCD_ROWS         4

#define LCD_RS_Pin GPIO_PIN_3
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RW_Pin GPIO_PIN_4
#define LCD_RW_GPIO_Port GPIOB
#define LCD_EN_Pin GPIO_PIN_5
#define LCD_EN_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_6
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_7
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_8
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_9
#define LCD_D7_GPIO_Port GPIOB
#define _LCD_RS_PIN       LCD_RS_Pin

#define _LCD_E_PORT       LCD_EN_GPIO_Port
#define _LCD_E_PIN        LCD_EN_Pin

#define _LCD_RW_PORT      LCD_RW_GPIO_Port
#define _LCD_RW_PIN       LCD_RW_Pin

#define _LCD_D4_PORT      LCD_D4_GPIO_Port
#define _LCD_D4_PIN				LCD_D4_Pin

#define _LCD_D5_PORT      LCD_D5_GPIO_Port
#define _LCD_D5_PIN       LCD_D5_Pin

#define _LCD_D6_PORT      LCD_D6_GPIO_Port
#define _LCD_D6_PIN       LCD_D6_Pin

#define _LCD_D7_PORT      LCD_D7_GPIO_Port
#define _LCD_D7_PIN       LCD_D7_Pin

#endif

