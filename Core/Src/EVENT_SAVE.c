/*author:maziar soleimani
linkedin:https://www.linkedin.com/in/maziar-soleimani-a260689a/
company:nmnj
file:event_save.c
****/
#include "main.h"
#include "LCD.h"
#include "menu.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "EVENT_SAVE.h"

 #define res        IWDG->KR  = 0xAAAA;

#define  sec_key  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_15  )
extern RTC_DateTypeDef DateToUpdate1;
uint8_t ty ;
 char sa[330];

 uint32_t  test = (uint32_t ) 0x0801fa00;
 uint8_t courser1=1;;
extern RTC_DateTypeDef current_date1;
 
extern RTC_TimeTypeDef  current_time;
 extern RTC_DateTypeDef current_date;
extern RTC_HandleTypeDef hrtc;
extern uint16_t KEY ;
char ti[12];
		uint8_t arr[3]={1,2,3};
    uint8_t u=0;
char im[12];
		uint32_t val= ( uint32_t ) 0x0801fa00;
 void event_list(void){
    uint8_t axis=0;	
	 courser1=1;
	  uint8_t co=0;
	  uint8_t  num = *( uint8_t *) 0x0801f9f0;
	   arr[0]=1;
		 arr[1]= 2;
	   arr[2]=3;
      u=0;
	  lcd_set_cursor(1, 6);
	  LCD_BlinkOn();
	  LCD_Blinkoff();
	  lcd_clear();
	  lcd_set_cursor(0, 0);

	  lcd_write_string(" HOUR:MIN  MONTH/DAY") ;
 	 if(num==0xff){
		 	 lcd_set_cursor(1, 1);
	lcd_write_string("NOT EVENT SAVED YET") ;
			   HAL_Delay(2000);
		 
	 }
	 else{
		 if(num<3){
			 co=num;
			 
			 
		 }
		 else{co=3;}
		 for(  u=0;u<co;u++){
			 for(int dd=0;dd<12;dd+=1){
			      im[dd]= *(uint8_t *)val;
				    val++;
				    val++;
			 }
			 sprintf(ti ," %d.%c%c:%c%c %c%c   %c%c/%c%c",u+1,im[0],im[1],im[3],im[4],im[5],im[6],im[7],im[8],im[10],im[11] );

			 lcd_set_cursor(arr[u] , 0);
	     lcd_write_string(ti) ;
			 			 
		 }
		  lcd_set_cursor(1, 1);
		 	LCD_BlinkOn();
		  val=0x0801fa00;
	  while(KEY!=esc_Pin){
       res;
			switch(KEY) {
        case up_Pin :
			if(num==1){
             courser1=1;
					}						
				else if(num==2 && courser1==1){
					  courser1=1;
				}
				else if(num==2 && courser1==2){
					  courser1=1;
				}
				else if(num==3 && courser1==3){
					  courser1=2;
				}	
				else if(num==3 && courser1==3){ 
					  courser1=2;
				}				
       else{
        courser1-=1;
			 }
						if(courser1<1){
						 courser1=1;
					   //val=val-20;
					   arr[0]-=1;
						 arr[1]-=1;
						 arr[2]-=1;
						if(arr[0]<1){
							arr[0]=num;
						}
						if(arr[1]<1){
							arr[1]=num;
						}	
						if(arr[2]<1){
							arr[2]=num;
						}						
						scroll();
					}
		
						lcd_set_cursor(courser1, 1);
				    KEY=0;
				 break;
        case down_Pin :
 
						  //courser1+=1;
					if(num==1){
             courser1=1;
					}						
				else if(num==2 && courser1==1){
					  courser1=2;
				}
				else if(num==2 && courser1==2){
					  courser1=2;
				}
				else if(num==3 && courser1==3){
					  courser1=3;
				}	
				else if(num==3 && courser1==2){
					  courser1=3;
				}					
       else{
        courser1+=1;
			 }				 
					if(courser1>3){
						 courser1=3;
					   //val=val-20;
					   arr[0]+=1;
						 arr[1]+=1;
						 arr[2]+=1;
						if(arr[0]>num){
							arr[0]=1;
						}
						if(arr[1]>num){
							arr[1]=1;
						}	
						if(arr[2]>num){
							arr[2]=1;
						}							
          scroll();
 
			 }			 
					lcd_set_cursor(courser1, 1);
				  KEY=0;
					break;	
					}
					 
      }
				 
				
	
			}
	
}

void scroll(void){
	
	         for(  u=0;u<3;u++){
					  val=0x0801fa00;
						  val=val+(arr[u]*24)-24;
			     for(int dd=0;dd<12;dd+=1){
			      im[dd]= *(uint8_t *)val;
				    val++;
				    val++;
				   
			 }
       if(arr[u]>9){
				 			 sprintf(ti ,"%d.%c%c:%c%c %c%c   %c%c/%c%c",arr[u],im[0],im[1],im[3],im[4],im[5],im[6],im[7],im[8],im[10],im[11] );

 					 }
			 else{
				 			 sprintf(ti ," %d.%c%c:%c%c %c%c   %c%c/%c%c",arr[u],im[0],im[1],im[3],im[4],im[5],im[6],im[7],im[8],im[10],im[11] );
				 
			 }
			 lcd_set_cursor(u+1 ,0);
 	     lcd_write_string(ti) ;
			 lcd_set_cursor(1, 1);
		 	LCD_BlinkOn();
		 }
		 		 val=0x0801fa00;	
}


void event_save(uint8_t coun){
	
		 HAL_RTC_GetTime(&hrtc,&current_time,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,&DateToUpdate1,RTC_FORMAT_BIN);

	   	sprintf(ti ,"%02d:%02d ",current_time.Hours,current_time.Minutes );
		 sprintf(ti+7 ,"%02d/%02d ",DateToUpdate1.Month,DateToUpdate1.Date );
	   switch(coun) {
        case 0 :
          ti[5]=' ';
				  ti[6]=' ';         
        break;
				
				case 1 :
          ti[5]='c';
				  ti[6]='1';
        break;
				
        case 2 :
          ti[5]='c';
				  ti[6]='2'; 
        break;
				
        case 3 :
          ti[5]='c';
				  ti[6]='3';
        break;				
				}					
	      uint8_t  num = *( uint8_t *) 0x0801f9f0;
	      test = (uint32_t ) 0x0801fa00;
	       if(num==0xff){
					 
					 num=0x00;
					 
				 }
	       for(uint32_t y=24;y<=360;y+=2){
					 sa[ y ]=  *( uint8_t *)test ;
					 test++;
					 test++;
 				    
			 }
				HAL_FLASH_Unlock();
			  FLASH_PageErase(0x0801f9f0);
			 CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
			  test = (uint32_t ) 0x0801fa00;
       for(uint32_t y=0;y<12;y+=1){
 				  sa[2*y]=ti[y];
				  FLASH_Program_HalfWord( test,ti[y]);
					 test++;
					 test++;
				 
			 }

         test = (uint32_t ) 0x0801fa18;
 	   
		      for(uint32_t y=24;y<=360;y+=2){
						 
					 
				   FLASH_Program_HalfWord( test,sa[y]);
					 test++;
					 test++;
 				    
			 }
					
         if	(num==15){
             num=15;

				 }
        else{
            num+=1;
				}
				
				 FLASH_Program_HalfWord( 0x0801f9f0,num);	 	    
			 CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
		    HAL_FLASH_Lock(); 
}

