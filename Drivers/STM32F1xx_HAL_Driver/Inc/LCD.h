
#ifndef LCD_H
#define LCD_H 
/*
+++   maziar soleimani
+++   Version: 1.1.0
*/


 #include "main.h"

void lcd_write_nibble(uint8_t nibble, uint8_t rs) ;

void lcd_send_cmd(uint8_t cmd) ;
void lcd_send_data(uint8_t data);
void lcd_init();
void lcd_write_string(char *str) ;
void lcd_set_cursor(uint8_t row, uint8_t column) ;
void lcd_clear(void) ;
void lcd_backlight(uint8_t state) ;
void LCD_Blinkoff(void);
void LCD_Blinkon(void);
#endif

