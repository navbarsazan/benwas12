/*author:maziar soleimani
linkedin:https://www.linkedin.com/in/maziar-soleimani-a260689a/
company:nmnj
file:pag2.c
****/
#include "main.h"
#include "LCD.h"
#include "menu.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "page2.h"
#include "page3.h"
#define MANUAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_SET)
#define MANUAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_RESET)
#define AUTOPILOT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_SET)
#define AUTOPILOT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_RESET)
#define  sec_key  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_15  )
extern uint8_t JU ;
extern uint8_t JI;
 uint8_t courser2=0;
extern 	uint8_t mj2;
 uint8_t TUI=0;
extern uint8_t dtc;
extern uint16_t KEY ;
char voldc[20];
char volac[20];
uint8_t status_watch_timer=1;
uint8_t CR=0;
extern	float AD_AC ;
 extern float AD_DC;
extern	 ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern uint8_t minu;
extern uint8_t sec; 
 #define res        IWDG->KR  = 0xAAAA;
  void VOLTAGE_SOURCES(void){
		
				lcd_clear();
			  lcd_set_cursor(0, 0); 
		    lcd_write_string("  #VOLTAGE SOURCE: ");		
		   	LCD_Blinkoff();
		
		   while(KEY!=esc_Pin )	{
       res;				 
			   	LCD_Blinkoff();	
 			     HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 1);
	      AD_AC = HAL_ADC_GetValue(&hadc1);
		   if(AD_AC<3000){
          lcd_set_cursor(1, 4); 
		    lcd_write_string("DC POWER");
				 HAL_Delay(400);
				 
			 }	
				else  {
					   lcd_set_cursor(1, 4); 
		         lcd_write_string("AC POWER");
					   HAL_Delay(400);
					// relay_off; 
 
				}				 
				 
				 
				 
			 }
		
	}
  void VOLTAGE_STATUS(void){
		   	lcd_clear();
			  lcd_set_cursor(0, 0); 
	    	lcd_write_string("#VOLTAGE DC:");	
			  lcd_set_cursor(1, 0); 
	    	lcd_write_string("#VOLTAGE AC:");				
 
		   	LCD_Blinkoff();
		   while(KEY!=esc_Pin )	{
				 res;	
 					HAL_ADC_Start(&hadc1);
          HAL_ADC_PollForConversion(&hadc1, 1);
          AD_AC = HAL_ADC_GetValue(&hadc1);
 					HAL_ADC_Start(&hadc2);
          HAL_ADC_PollForConversion(&hadc2, 1);
          AD_DC = HAL_ADC_GetValue(&hadc2);
 				 sprintf(volac,"%0.2fV",(AD_AC*12)/4095);
				 
				 sprintf(voldc,"%0.2fV",(AD_DC*12)/4095);
				 
	       lcd_set_cursor(0, 14); 
				 lcd_write_string(voldc);	
         lcd_set_cursor(1, 14); 				 
		     lcd_write_string(volac);	
  }
	}

	  void page2_list(void){
		  
				lcd_clear();
			  lcd_set_cursor(0, 0); 
			  lcd_write_string("1.CONNECTION");	
			  lcd_set_cursor(1, 0); 
			  lcd_write_string("2.VOLTAGE SOURCES");				
			  lcd_set_cursor(2,0); 
			  lcd_write_string("3.VOLTAGES STATUS");
 			  lcd_set_cursor(3,0); 
			  lcd_write_string("4.MODE->"); 	
			  lcd_set_cursor(3,18); 
			  lcd_write_string("->");
				lcd_set_cursor(3,16); 
			  lcd_write_string("<-");
        if(TUI==1){
     	  lcd_set_cursor(3,8); 
			  lcd_write_string("AUTO");
 
				}
        else	{
     	  lcd_set_cursor(3,8); 
			  lcd_write_string("MAN");

				}					
	}
		void CHECK(void){
	     if(dtc==1){
			 lcd_set_cursor(2, 13);
			 lcd_write_string("OK  ");
		 }
		 
		 else{
			    lcd_set_cursor(2,13);
			  lcd_write_string("FAIL");
		 }
}
		void MODE(void){
			 	lcd_clear();
			  lcd_set_cursor(0, 0); 
		  	KEY=0;
			  lcd_write_string("#MANUAL");	
			  lcd_set_cursor(1, 0); 
			  lcd_write_string("#AUTO(PILOT)");
        lcd_set_cursor(CR, 13);		
		 	  lcd_write_string("*");
       	LCD_BlinkOn();	
        lcd_set_cursor(CR, 0);		
        courser2	=0;		
		  	 
				while(KEY!=esc_Pin )	{	
					res;	
 
						switch(KEY) {
						case up_Pin:
							if(courser2==0){
								courser2=1;
								lcd_set_cursor(courser2, 0); 
								LCD_BlinkOn();
								KEY=0;
							
							}
							else{
							 courser2-=1;
							 lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();}
								KEY=0;
							break;
							
						
						
						case down_Pin:

							if(courser2==1){
								courser2=0;
							lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();
								KEY=0;
							}
							else{
							courser2+=1;
							lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();
							}
							KEY=0;
							break;		

								
						
							case ok_Pin:
									
							switch(courser2) {
						case 0:
							
							// code block
						      courser2=0;
								  lcd_set_cursor(courser2, 13);		
		 	            lcd_write_string("*");
									lcd_set_cursor(1, 13);		
		 	            lcd_write_string(" ");									
									lcd_set_cursor(courser2, 0); 
						      status_watch_timer=1;
									LCD_BlinkOn();
								  AUTOPILOT_OFF;
				          MANUAL_ON;
						      TUI=0;
									KEY=0;
					      	lk();
							 break;
								case 1:
									courser2=1;
							   	TUI=1;
									 lcd_set_cursor(courser2, 13);		
		 	            lcd_write_string("*");
									lcd_set_cursor(0, 13);		
		 	            lcd_write_string(" ");
									lcd_set_cursor(courser2, 0); 
									LCD_BlinkOn();
								  AUTOPILOT_ON;
									MANUAL_OFF;
									KEY=0;	
								  status_watch_timer=0;
 
								  minu=5;
								  mj2=5;
								  sec=0;
  
										
							}
							}
						}
				CR=courser2;
					}
	void conection(void){
	
		lcd_clear();
 	lcd_set_cursor(2, 2);
	LCD_Blinkoff();
	lcd_write_string("CONNECTION: ");
 	  while(KEY!=esc_Pin){
			res;	
 		 	     for(int y=0;y<=3;y++){ 
      lcd_set_cursor(0, 0);						 
       lcd_write_string( "***   checking   ***") ;	
 
				 HAL_Delay(250);
 					if(KEY==esc_Pin){
						break;
					}
						 CHECK();
			 lcd_set_cursor(0, 0);	
				 lcd_write_string("****  checking  ****") ;
 
				HAL_Delay(250);
 						if(KEY==esc_Pin){
							
						break;
					}
						 CHECK();
				 lcd_set_cursor(0, 0);	
				 lcd_write_string("***** checking *****") ;
 
				 HAL_Delay(250);
 				if(KEY==esc_Pin){
						break;
					}
						 CHECK();
				 lcd_set_cursor(0, 0);	
				 lcd_write_string("******checking******") ; 
 
				 HAL_Delay(250);
   
											if(KEY==esc_Pin){
						break;
					}
						 CHECK();
			 }
}
		}
	
	
	
  void page2_menu (void){
		
		
		 page2_list();
	   lcd_set_cursor(0, 0);	
	   LCD_BlinkOn();
		 KEY=0;
		 courser2=0;
     while(KEY!=esc_Pin )	{	
			 res;	
 	      if(JU==1 ){
					  if(TUI==1){
							 lcd_set_cursor(3,8); 
							 lcd_write_string("AUTO");
					 
									}
						 else	{
									lcd_set_cursor(3,8); 
									lcd_write_string("MAN");

									}	
			    JU=0;
								}
							    
				  lcd_set_cursor(courser2, 0);
				 	LCD_BlinkOn();
									
				  switch(KEY) {
						 case right_Pin:
							 page3_menu();
						
						 break;
						 case left_Pin:
							 page1_menu();
						
						 break;
							
						case up_Pin:
							if(courser2==0){
								courser2=3;
								lcd_set_cursor(courser2, 0); 
								LCD_BlinkOn();
							
							}
							else{
							 courser2-=1;
							 lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();}
								KEY=0;
							break;
							
						
						
						case down_Pin:

							if(courser2==3){
								courser2=0;
							lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();
								KEY=0;
							}
							else{
							courser2+=1;
							lcd_set_cursor(courser2, 0); 
							LCD_BlinkOn();
							}
							KEY=0;
							break;		

								
						
							case ok_Pin:
									
			  switch(courser2) {
						case 0:
							
								conection ();
							// code block
										page2_list();
									courser2=0;
									lcd_set_cursor(courser2, 0); 
									LCD_BlinkOn();
									KEY=0;
							 break;
								case 1:
									VOLTAGE_SOURCES();
									page2_list();
									courser2=1;
									lcd_set_cursor(courser2, 0); 
									LCD_BlinkOn();
									KEY=0;	
								
							
							KEY=0;
							break;

							 case 2:
									VOLTAGE_STATUS();
									page2_list();
									courser2=2;
									lcd_set_cursor(courser2, 0); 
									LCD_BlinkOn();
									KEY=0;
								 
							 break;

							 
							 case 3:
							 if(sec_key==0){
								 MODE();
							 }
							 else{
								 lcd_clear();
								 lcd_set_cursor(0, 0);	
								 lcd_write_string("   Access denied") ; 
								LCD_Blinkoff();
								for(int i=0;i<40;i++){
													 HAL_Delay(50);
						
								}
							 }
							 page2_list();
							 courser2=3;
							 lcd_set_cursor(courser2, 0); 
							 LCD_BlinkOn();
							 KEY=0;
							 break;
							 
							 
							 
					}	
							break;
						}
					}	
							
						}
