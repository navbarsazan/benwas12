/*author:maziar soleimani
linkedin:https://www.linkedin.com/in/maziar-soleimani-a260689a/
company:nmnj
file:page3.c
****/
#include "main.h"
#include "LCD.h"
#include "menu.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "page3.h"

#include "page2.h"
 #define res        IWDG->KR  = 0xAAAA;

#define MANUAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_SET)
#define MANUAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_RESET)
#define AUTOPILOT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_SET)
#define AUTOPILOT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_RESET)
#define INTERNAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_SET)
#define INTERNAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_RESET)
#define EXT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_SET)
#define EXT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_RESET)
#define  sec_key  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_15  )
volatile uint8_t REP31 ;
#define PIR_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_SET)
#define PIR_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_RESET)
#define pir_check    HAL_GPIO_ReadPin(GPIOA,  GPIO_PIN_12 )
extern uint8_t mj2;
int sw=0;
extern uint8_t WARN;
extern uint8_t WARN1;
extern uint8_t WARN2;
extern uint8_t WARN3;
extern uint8_t dtc;
 uint8_t TIMO=1;
extern uint16_t KEY ;
extern uint8_t TUI;
uint8_t led_buf=0;
extern I2C_HandleTypeDef hi2c1;
extern	 ADC_HandleTypeDef hadc1;
extern   ADC_HandleTypeDef hadc2;
extern uint8_t minu;
extern uint8_t sec; 
uint8_t courser3=0;
uint8_t LED_STATUS=0;
char le;
extern uint8_t TX_Buffer7[1] ;
 void ALARAM_EXTERNAL_TEST(void){  
	      KEY=0;
		   	lcd_clear();
			  lcd_set_cursor(0, 0); 
	    	lcd_write_string("#PRESS OK TO ALARM:");	
	      LCD_Blinkoff();
 			  HAL_Delay(500);
				while(KEY!=esc_Pin )	{	
					 res;
					
 					switch(KEY) {
					 case ok_Pin:
						 sw=1;
						 		 	 lcd_set_cursor(2, 0); 
	              	lcd_write_string("ALARMING.....");	
					 EXT_ON; 
							 for(int r=0;r<3;r++){

							  	EXT_ON; 
 									HAL_Delay(1000);
								 
								 if (KEY==esc_Pin){
									 EXT_OFF;
									 sw=0;
									 KEY=0;
                     HAL_Delay(100);
									 break;
								 
							 }
					 
				     }
             	 EXT_OFF;
						   sw=0;

							lcd_clear();
			        lcd_set_cursor(0, 0); 
	    	      lcd_write_string("#PRESS OK TO ALARM:");	
					    KEY=0;
					 break;		
					 }
	}
}
	
 void	 ALARAM_FAULT( void){
				  uint8_t courser=0;
		      KEY=0;
		   	lcd_clear();
			  lcd_set_cursor(0, 0);
	 				if(WARN==1){ 
	         lcd_set_cursor(courser, 0); 
	  	    lcd_write_string("VOLTAGE DC FAIL");	
          courser=+1;
	 
			}
			if(WARN1==1){ 
	         lcd_set_cursor(courser, 0); 
	  	    lcd_write_string("VOLTAGE AC FAIL");	

	 
			}
			if(WARN1==0 && WARN==0){
				         lcd_set_cursor(0, 0); 
	  	    lcd_write_string("NO FAULT....");		
				
			}
		while(KEY!=esc_Pin )	{	
 res;			
          LCD_Blinkoff();
		    	 res;
 
		    }
		   	 }

   void ALARAM_INTERNAL_TEST(void){  
	      KEY=0;
		   	lcd_clear();
			  lcd_set_cursor(0, 0); 
	    	lcd_write_string("#PRESS OK TO ALARM:");	
	      LCD_Blinkoff();
		   	HAL_Delay(500);
				while(KEY!=esc_Pin )	{	
					 res;
 					switch(KEY) {
					 case ok_Pin:
						
						 		 	 lcd_set_cursor(2, 0); 
	              	lcd_write_string("ALARMING.....");	
							 for(int r=0;r<3;r++){

								INTERNAL_ON;
									HAL_Delay(1000);
 								 
								 if (KEY==esc_Pin){
									 INTERNAL_OFF;
 									 HAL_Delay(500);
                    KEY=0;
									 break;
								 
							 }
					 
				     }
             	 INTERNAL_OFF;

							 		   	lcd_clear();
			        lcd_set_cursor(0, 0); 
	    	     lcd_write_string("#PRESS OK TO ALARM:");	
					    KEY=0;
					 break;		
					 }
	}
}
  void LED_TEST(void){
		   	lcd_clear();
			  lcd_set_cursor(0, 0); 
	    	lcd_write_string("#LED TEST:");	
	       LCD_Blinkoff();
        led_buf=0xff;
		     TIMO=0;
		  	 AUTOPILOT_OFF;
				 MANUAL_OFF;
	    	 HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				 HAL_Delay(1000);
		     LED_STATUS=1;

		   for(int b=0;b<4;b++){
				 led_buf=led_buf<<1;
				 HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				  lcd_set_cursor(1, 2*b);          		
	      	lcd_send_data(0xff);
		      HAL_Delay(1000);
	       res;
			 }
	      	led_buf=0xb0;
				 HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				    lcd_set_cursor(2, 8);          		
	      	lcd_send_data(0xff);
					HAL_Delay(1000);
				  led_buf=0x30;
				  HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				  lcd_set_cursor(2, 10);          		
	      	lcd_send_data(0xff);
					HAL_Delay(1000);
           res;
				  led_buf=0x20;
				  HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				  lcd_set_cursor(1, 12);          		
	      	lcd_send_data(0xff);
					HAL_Delay(1000);
					led_buf=0x00;
				  HAL_I2C_Master_Transmit(&hi2c1,0x41,&led_buf,1,100);
				  lcd_set_cursor(1, 14);          		
	      	lcd_send_data(0xff);
					HAL_Delay(1000);
		
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
				  lcd_set_cursor(3, 6);  
	      	lcd_send_data(0xff);
					HAL_Delay(1000);
      res;
				  lcd_set_cursor(3, 8);          		
	      	lcd_send_data(0xff);					 
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
					HAL_Delay(1000);

					  lcd_set_cursor(3, 10);          		
	      	lcd_send_data(0xff);					 
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
					HAL_Delay(1000);
		     LED_STATUS=0;

          TIMO=1;
	} 
 	  void page3_list(void){
		  
				lcd_clear();
			  lcd_set_cursor(0, 0); 
			  lcd_write_string("1.LED TEST");	
			  lcd_set_cursor(1, 0); 
			  lcd_write_string("2.TEST EXT ALARM");				
			  lcd_set_cursor(2,0); 
			  lcd_write_string("3.TEST INT ALARM");
 			  lcd_set_cursor(3,0); 
			  lcd_write_string("4.ALARM FAULT"); 	
			  lcd_set_cursor(3,18); 
				lcd_set_cursor(3,16); 
			  lcd_write_string("<-");			
	}
  void page3_menu (void){
		
		
					 page3_list();
					 lcd_set_cursor(0, 0);	
					 LCD_BlinkOn();
					 KEY=0;
						while(KEY!=esc_Pin )	{
            res;							
							switch(KEY) {
							 case left_Pin:
								 page2_menu();
							
							 break;
							
							case up_Pin:
								if(courser3==0){
									courser3=3;
									lcd_set_cursor(courser3, 0); 
									LCD_BlinkOn();
								
								}
								else{
								 courser3-=1;
								 lcd_set_cursor(courser3, 0); 
								LCD_BlinkOn();}
									KEY=0;
								break;
								
							
							
							case down_Pin:

								if(courser3==3){
									courser3=0;
								lcd_set_cursor(courser3, 0); 
								LCD_BlinkOn();
									KEY=0;
								}
								else{
								courser3+=1;
								lcd_set_cursor(courser3, 0); 
								LCD_BlinkOn();
								}
								KEY=0;
								break;		

									
							
								case ok_Pin:
										
								switch(courser3) {
							case 0:
								
								 // code block
									 LED_TEST();

										HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
										HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_3|GPIO_PIN_2, GPIO_PIN_RESET);
										page3_list();
										courser3=0;
										lcd_set_cursor(courser3, 0); 
										LCD_BlinkOn();
										KEY=0;
											if(TUI==1){
											AUTOPILOT_ON;
											MANUAL_OFF;
											
										}
										else{
											
											AUTOPILOT_OFF;
											MANUAL_ON;			
										}
									if(pir_check==0){
											PIR_ON;
											
										}
									 else{
										 PIR_OFF;
										 
									 }
								 break;
									case 1:
										ALARAM_EXTERNAL_TEST();
										HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
										page3_list();
										courser3=1;
										lcd_set_cursor(courser3, 0); 
										LCD_BlinkOn();
										KEY=0;	
									
								
								KEY=0;
								break;

								 case 2:
										 ALARAM_INTERNAL_TEST();
										page3_list();
										courser3=2;
										lcd_set_cursor(courser3, 0); 
										LCD_BlinkOn();
										KEY=0;
									 
								 break;

								 
								 case 3:
								 ALARAM_FAULT();

								 page3_list();
								 courser3=3;
								 lcd_set_cursor(courser3, 0); 
								 LCD_BlinkOn();
								 KEY=0;
								 break;
								 
								 
								 
						}	
								break;
							}
						}	
								
							}