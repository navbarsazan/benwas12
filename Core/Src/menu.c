/*author:maziar soleimani
linkedin:https://www.linkedin.com/in/maziar-soleimani-a260689a/
company:nmnj
file:menu.c
****/
#include "main.h"
#include "LCD.h"
#include "menu.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "EVENT_SAVE.h"
#include "page2.h"
 #define res        IWDG->KR  = 0xAAAA;

extern uint8_t STAR;
extern uint8_t CONT ;
#define  sec_key  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_15  )
extern 	uint8_t mj2;

uint16_t axis=0;
extern uint8_t status_watch_timer;

int by=0;
extern uint8_t minu;
extern uint8_t sec; 
extern RTC_HandleTypeDef hrtc;
uint8_t POSITION_VAL[]={ 6 ,9, 12, 8 ,11, 14};
  RTC_TimeTypeDef sTime = {0};
extern  RTC_DateTypeDef DateToUpdate1 ;
   /* USER CODE BEGIN 1 */
   RTC_TimeTypeDef  current_time;
   RTC_DateTypeDef current_date;
extern uint16_t KEY ;
uint8_t courser=0 ;
uint8_t hex=0 ;
uint8_t mj=0 ;

extern char time[20];

	
	
	
	
 
uint8_t save(void){	
	    uint8_t stat=5;
    	uint8_t esc=0;
			lcd_clear();
			  lcd_set_cursor(5, 0); 
			  lcd_write_string("  save?");		
			
			  lcd_set_cursor(2, 2); 
			  lcd_write_string("Yes         No ");	
      	lcd_set_cursor(2, 5); 
		  while(esc==0){
				res;
 		if(STAR==0){
			return 0 ;
			
		}
			switch(KEY) {
        case ok_Pin:
					
				  if(stat==5){
						esc=1;
						 return 1;}
					else if(stat==16){
						esc=1;
						return 0;
					}
				 KEY=0;
				break;
				
				
				case left_Pin:
					
					if(stat==5){
							lcd_set_cursor(2, 16); 
					  	stat=16;
					}
					else{
					lcd_set_cursor(2, 5);		
           stat=5;					}
					KEY=0;
				break;
				case right_Pin:
					KEY=0;
					if(stat==5){
							lcd_set_cursor(2, 16); 
						stat=16;
					}
					else{
					lcd_set_cursor(2, 5);
           stat=5;					}
					KEY=0;
				break;					
				
			}
			
		}
	 
}

void save_dis_watchtimer(uint8_t en){

			sprintf(time,"%02x  minute",en);
		  lcd_set_cursor(2, 0); 
	    lcd_write_string( time  );
	    mj=en;
	
}

void set_time_watch(void){
	
	
 	   uint32_t ad =  0x08009010;
      uint8_t ti = *(__IO uint8_t *)(0x0801fa00);
 		 lcd_clear(); 

			 // 
   	//FLASH_PageErase(ad);
 
    if(ti==0){
			ti=0x05;
		}
   else{

	    ti=*(__IO uint8_t *)(0x0801ff22);
	 }
	 	 if(ti==0xff){
		 ti=0x30;
	 }
	    lcd_set_cursor(2, 0); 
		  sprintf(time,"%02x minute",ti);
 	   
  		lcd_set_cursor(0, 0); 
	    lcd_write_string("choose watchtimer:");	
 		  lcd_set_cursor(2, 0); 
	    lcd_write_string( time  );	
 					//switch()
       save_dis_watchtimer(ti);
  
	   LCD_BlinkOn();
 	  while(KEY!=esc_Pin){
			
			res;
 		switch(KEY) {
        
			case up_Pin:
				switch(ti){
				
				case 0x05:
						ti=0x30;
					//switch()
       save_dis_watchtimer(ti);

			

				break;
				
				case 0x10:
				ti=0x05;
       save_dis_watchtimer(ti);

					
				break;

				
		   case 0x15:
				 ti=0x10;	
       save_dis_watchtimer(ti);
 
				
			 KEY=0;
				break;
			 
		   case 0x20:
				 ti=0x15;
       save_dis_watchtimer(ti);
	
				
			 KEY=0;
				break;
				KEY=0;			 
		   case 0x30:
				  ti=0x20;
	     save_dis_watchtimer(ti);
					
			 
			  
			 KEY=0;
				break;				 
			
			}
				KEY=0;
				break;
			
			
			case down_Pin:
				switch(ti){
				
				case 0x05:
					//switch()
			 ti=0x10;
       save_dis_watchtimer(ti);


				break;
				
				case 0x10:
	  		ti=0x15;
       save_dis_watchtimer(ti);

       KEY=0;				
				break;

				
		   case 0x15:
				 ti=0x20;
       save_dis_watchtimer(ti);
 
					
			 KEY=0;
				break;
			 
		   case 0x20:
				ti=0x30;
       save_dis_watchtimer(ti);
	
				
			 KEY=0;
			 
				break;			 
		   case 0x30:
				 ti=0x05;
	     save_dis_watchtimer(ti);
					
			  
			 KEY=0;
				break;				 
			
			}
				KEY=0;
				break;
			 
	}
		}
   if(save()){		
	   HAL_FLASH_Unlock();
	 	  FLASH_PageErase(0x0801ff00);
 	    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	
	    FLASH_Program_HalfWord( 0x0801ff00,mj);
		 FLASH_Program_HalfWord( 0x0801ff22,mj);
			 CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
		 

 	    HAL_FLASH_Lock(); 
				 lcd_clear();
			  lcd_set_cursor(4, 0); 
			  lcd_write_string("SAVING setting is OK");
			 if(mj==0x30){
				  minu=30;
			 }
      else if(mj==0x20){			 
			 minu=20;}
      else if(mj==0x15){			 
			 minu=15;}			
      else if(mj==0x10){			 
			 minu=10;}
      else if(mj==0x05){			 
			 minu=5;}				
	    mj2=minu;
			 sec=0;

 
	  
}
			
else{		
	
				 lcd_clear();
			  lcd_set_cursor(4, 0); 
			  lcd_write_string("SAVING is cancel");	
	
}
       HAL_Delay(1000);
 			
		}



  void page1_list(void){
		
				lcd_clear();
			  lcd_set_cursor(0, 0); 
			  lcd_write_string("1.SET TIME & DATE");	
			  lcd_set_cursor(1, 0); 
			  lcd_write_string("2.SET TIME WATCH");
	     	lcd_set_cursor(2, 0); 
				lcd_write_string("3.RECORD EVENT");
	     	lcd_set_cursor(3, 0); 
				lcd_write_string("4.ABOUT");
	     	lcd_set_cursor(3, 18); 
				lcd_write_string("->");

		
	}

			  void increase(void){
            switch(POSITION_VAL[axis]){
						 case(6):
							 if(sTime.Hours==23){
								 current_time.Hours=0;
								  sTime.Hours = 0;
								 	sprintf(time,"%02d",current_time.Hours);

							 }
							 else{
            sTime.Hours += 1;
						 current_time.Hours+= 1;
		        	sprintf(time,"%02d",sTime.Hours);}
							
							lcd_set_cursor(1, 5);
 		          lcd_write_string(time);
						   lcd_set_cursor(1, 6);
                break;
						 
						 case(9):
							 if( sTime.Minutes==59){
								    sTime.Minutes =0;
						        current_time.Minutes = 0;
										 lcd_set_cursor(1, 8);
										 sprintf(time,"%02d",sTime.Minutes);

							 }
							else{	 
              sTime.Minutes += 1;
						 current_time.Minutes+= 1;
						 sprintf(time,"%02d",sTime.Minutes);
						 	lcd_set_cursor(1, 8);}
 		          lcd_write_string(time);
						   lcd_set_cursor(1, 9);
                break;
						 
 						 case(8):
							 if(DateToUpdate1.Year>= 99){
								 DateToUpdate1.Year=23;
								  current_date.Year=23;
								  
							 }
 
								 
							else{
							  
              DateToUpdate1.Year += 1;
						  current_date.Year+= 1;
							}
						 	lcd_set_cursor(2, 7);
		        	sprintf(time,"%02d",DateToUpdate1.Year);
 		          lcd_write_string(time);
						  lcd_set_cursor(2, 8);
						               

              break; 

 						 case(11):
							 if(DateToUpdate1.Month==12 || DateToUpdate1.Month==00 ){
								 
							 DateToUpdate1.Month = 1;
						  current_date.Month= 1;
							lcd_set_cursor(2, 10);
							 sprintf(time,"%02d",DateToUpdate1.Month);
							 }
							 else{
              DateToUpdate1.Month += 1;
						  current_date.Month+= 1;
						 	lcd_set_cursor(2, 10);
		        	sprintf(time,"%02d",DateToUpdate1.Month);
							 }
 		          lcd_write_string(time);
						  lcd_set_cursor(2, 11);
               break; 

 						 case(14):
							 if(DateToUpdate1.Date==31 || DateToUpdate1.Date==00 ){
								 
					   	 DateToUpdate1.Date = 1;
						   current_date.Date= 1;
							 lcd_set_cursor(2, 13);
		        	  sprintf(time,"%02d",DateToUpdate1.Date);
							 }
							 else{
            DateToUpdate1.Date += 1;
						 current_date.Date+= 1;
						 	lcd_set_cursor(2, 13);
		        	sprintf(time,"%02d",DateToUpdate1.Date);}
 		          lcd_write_string(time);
						   lcd_set_cursor(2, 14);
                break; 							 
					 }
					 
				 }
	 
  void decrease(void){
		
           switch(POSITION_VAL[axis]){
						 case(6):
							 if( sTime.Hours==0){
								  sTime.Hours = 23;
					  	    current_time.Hours= 23;
								 	lcd_set_cursor(1, 5);								 
								  sprintf(time,"%02d" ,sTime.Hours );
							 }
							 else{
                sTime.Hours -= 1;
					  	  current_time.Hours-= 1;
						  	lcd_set_cursor(1, 5);								 
		        	  sprintf(time,"%02d",sTime.Hours);
                    }
							  lcd_write_string(time);
						   lcd_set_cursor(1, 6);
                break;
						 
						 case(9):
							 
						 if( sTime.Minutes==0){
 
							  sTime.Minutes= 59;
							 current_time.Minutes= 59;
						   	lcd_set_cursor(1, 8);
							  sprintf(time,"%02d",sTime.Minutes);
							 
						 }
						 else{
              sTime.Minutes -= 1;
						  current_time.Minutes-= 1;
						 	lcd_set_cursor(1, 8);
		        	sprintf(time,"%02d",sTime.Minutes );}
 		          lcd_write_string(time);
						   lcd_set_cursor(1, 9);
                break;

		
						 
 						 case(8):
							 if(DateToUpdate1.Year<23){
								 DateToUpdate1.Year=23;
								 current_date.Year=23;
								   
							 }
		 
              
								 
							else{
            DateToUpdate1.Year -= 1;
						 current_date.Year-= 1;
							}
						 	lcd_set_cursor(2, 7);
		        	sprintf(time,"%02d",DateToUpdate1.Year);
 		          lcd_write_string(time);
						   lcd_set_cursor(2, 8);
                break; 

 						 case(11):
							 if(DateToUpdate1.Month==1 || DateToUpdate1.Month==0){
                 DateToUpdate1.Month = 12;
						      current_date.Month= 12;
							  	lcd_set_cursor(2, 10);
		            	sprintf(time,"%02d",DateToUpdate1.Month);
							 }
							 else{
            DateToUpdate1.Month -= 1;
						 current_date.Month-= 1;
						 	lcd_set_cursor(2, 10);
		        	sprintf(time,"%02d",DateToUpdate1.Month);}
 		          lcd_write_string(time);
						   lcd_set_cursor(2, 11);
                break; 
                    
 						 case(14):
							 if(DateToUpdate1.Date==1 || DateToUpdate1.Date==0){
								  DateToUpdate1.Date = 31;
					    	 current_date.Date= 31;
						    	lcd_set_cursor(2, 14);
		        	    sprintf(time,"%02d",DateToUpdate1.Date);
								 
								 
							 }
							 else{
            DateToUpdate1.Date -= 1;
						 current_date.Date-= 1;
						 	lcd_set_cursor(2, 13);
		        	sprintf(time,"%02d",DateToUpdate1.Date);
 		          lcd_write_string(time);
						   lcd_set_cursor(2, 14);
                break; 
							 }								 
					 }
				 }
 	
		
	
	 void time_dis(void){


 
	
	  HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&DateToUpdate1,RTC_FORMAT_BIN);
 
		lcd_set_cursor(1, 5);
		sprintf(time,"%02d:%02d:%02d",sTime.Hours,sTime.Minutes,sTime.Seconds);
 		lcd_write_string(time);	 
    lcd_set_cursor(2, 5);
	  sprintf(time,"20%02d/%02d/%02d",DateToUpdate1.Year,DateToUpdate1.Month,DateToUpdate1.Date);
 		lcd_write_string(time);
	 

	 }
	
 void set_time_date(void){

	lcd_clear();
  time_dis();
	lcd_set_cursor(1, 6);
	LCD_BlinkOn();
	 axis=0;
	  while(KEY!=esc_Pin){
			res;
 			switch(KEY) {
 
	    
			 case right_Pin:
				 switch(axis){
					 case(0):
				    axis+=1;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
				  	 KEY=0;
					 	break;
					 
           case(1): 					 
				    axis+=1;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
					  KEY=0;
					 	break;
           case(2): 					 
				    axis+=1;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					  KEY=0;
					 	break;					 
           case(3): 					 
				    axis+=1;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					  KEY=0;
					 	break;						 
           case(4): 					 
				    axis+=1;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					  KEY=0;
					 	break;				   
           case(5): 					 
				    axis=0;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
					  KEY=0;
					 
					 	break;					  
				 }
          break;
				 
		
			 	case up_Pin:
		     increase();
		      KEY=0;
          break;
				
				
		  	case down_Pin:
		     decrease();
		      KEY=0;
          break;
					
					
					
			 case left_Pin:
				 switch(axis){
					 case(0):
				    axis=5;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					 KEY=0;
					 	break;
					 
           case(1): 					 
				    axis-=1;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
					  KEY=0;
					 	break;
           case(2): 					 
				    axis-=1;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
					  KEY=0;
					 	break;					 
           case(3): 					 
				    axis-=1;	
			      lcd_set_cursor(1, POSITION_VAL[axis]);
					  KEY=0;
					 	break;						 
           case(4): 					 
				    axis-=1;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					  KEY=0;
					 	break;				   
           case(5): 					 
				    axis-=1;	
			      lcd_set_cursor(2, POSITION_VAL[axis]);
					  KEY=0;
					 
					 	break;					 
					
				 }
			    break;
			 
	
		 }
				}
		   if( save()){
	    
	  
		  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
			 lcd_clear();
			  lcd_set_cursor(4, 0); 
			  lcd_write_string("Setting save is fail");
  }
	 

			   if (HAL_RTC_SetDate(&hrtc, &DateToUpdate1, RTC_FORMAT_BIN) != HAL_OK)
  {
						 lcd_clear();
			  lcd_set_cursor(4, 0); 
			  lcd_write_string("Setting save is fail");
		
    Error_Handler();
  }
			  lcd_clear();
			  lcd_set_cursor(4, 0); 
			  lcd_write_string("Setting save is OK");
	      HAL_Delay(1000);
}
	   	page1_list();
     

		}




void ABOUT(void){
	 
		lcd_clear();
 	lcd_set_cursor(0, 0);
	LCD_Blinkoff();
	lcd_write_string("Device:BN143 ");
	 	lcd_set_cursor(1, 0);
 	lcd_write_string("Version:1.0");
		 	lcd_set_cursor(3, 0);
  	lcd_write_string("Production:NMNJ.CO");
			  while(KEY!=esc_Pin){
 					LCD_Blinkoff();
					res;
					 
					
				
		 
	}
   
	}

		
void page1_menu(void)
				{
					
					page1_list();
					lcd_set_cursor(0, 0); 
					courser=0; 
					KEY=0;
				  LCD_BlinkOn();
					STAR=1;
					while(KEY!=esc_Pin )	{
						res;
 					 if(STAR==0){
		     	   KEY=esc_Pin;
			
		       }
					 switch(KEY) {
						 
						 case right_Pin:
							  page2_menu();
						
						 break;
						
						case up_Pin:

							if(courser==0){
								courser=3;
										lcd_set_cursor(courser, 0); 
							LCD_BlinkOn();
							
							}
							else{
							 courser-=1;
							 lcd_set_cursor(courser, 0); 
							LCD_BlinkOn();}
								KEY=0;
							break;	
						
						case down_Pin:		
							if(courser==3){
								courser=0;
							lcd_set_cursor(courser, 0); 
							LCD_BlinkOn();
								KEY=0;
							}
							else{
							courser+=1;
							lcd_set_cursor(courser, 0); 
							LCD_BlinkOn();
							}
							KEY=0;
							break;
								
						
							case ok_Pin:
									
							switch(courser) {
						case 0:
						 
								 set_time_date();
							// code block
							KEY=0;
							break;
							 case 1:
							if(	status_watch_timer==1 && sec_key==0){
										 set_time_watch();
													 }
						 else{
								 lcd_clear();
								 lcd_set_cursor(1, 0);	
								 lcd_write_string("   Access denied") ; 
								LCD_Blinkoff();
								 HAL_Delay(2000);
						 }
									 page1_list();
							 
									 lcd_set_cursor(courser, 0); 
									 LCD_BlinkOn();

						 
							// code block
							KEY=0;
							break;

							 case 2:
								if( sec_key==0){
									 event_list();
							 }
							 else{
								 lcd_clear();
								 lcd_set_cursor(2, 0);	
								 lcd_write_string("   Access denied") ; 
								 
								LCD_Blinkoff();
								  HAL_Delay(2000);
	 							 
							 }
								// conection();
								   KEY=0;
							    	courser=2;
							 		 page1_list();							 
									 lcd_set_cursor(courser, 0); 
									 LCD_BlinkOn();
							 break;
								
							// code block
							KEY=0;
							 
							 case 3:
							
								ABOUT();
							courser=3;
							 page1_list();
							// code block
							 lcd_set_cursor(courser, 0); 
							LCD_BlinkOn();
							KEY=0;
							break;
							 
							 
							 
					}	
							break;
						}
					}	
lcd_clear();
lcd_send_cmd( 0x0c);//BLINKOFF
//BACK TO MAIN PAGE		
//	lk();
    minu=		mj2-1;	
    sec=59;					
}





