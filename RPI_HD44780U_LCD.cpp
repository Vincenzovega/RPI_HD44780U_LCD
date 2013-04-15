#include "lcd.h"
#include <stdio.h>


LCD_display::LCD_display(uint8_t PIN_RS, uint8_t PIN_EN, uint8_t PIN_RW, uint8_t PIN_0, uint8_t PIN_1, uint8_t PIN_2, uint8_t PIN_3) {

init(0,PIN_RS,PIN_EN,PIN_RW,PIN_0,PIN_1,PIN_2,PIN_3,0,0,0,0);
}


LCD_display::LCD_display(uint8_t PIN_RS, uint8_t PIN_EN, uint8_t PIN_RW, 
uint8_t PIN_0, uint8_t PIN_1, uint8_t PIN_2, uint8_t PIN_3,
uint8_t PIN_4, uint8_t PIN_5, uint8_t PIN_6, uint8_t PIN_7){
    
init(1,PIN_RS,PIN_EN,PIN_RW,PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7);
}

    
void LCD_display::init(uint8_t DataLength,uint8_t PIN_RS,uint8_t PIN_EN,uint8_t PIN_RW,
uint8_t PIN_0,uint8_t PIN_1,uint8_t PIN_2,uint8_t PIN_3,
uint8_t PIN_4,uint8_t PIN_5,uint8_t PIN_6,uint8_t PIN_7)    
{
   _rs = PIN_RS;
   _en = PIN_EN;
   _rw = PIN_RW;
    
    data_pin[0] = PIN_0;
    data_pin[1] = PIN_1;
    data_pin[2] = PIN_2;
    data_pin[3] = PIN_3;
    data_pin[4] = PIN_4;
    data_pin[5] = PIN_5;
    data_pin[6] = PIN_6;
    data_pin[7] = PIN_7; 
    
    bcm2835_gpio_fsel(_rs, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_rs, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_rs, BCM2835_GPIO_FSEL_OUTP);
    
    bcm2835_gpio_write(_rw, LOW);
    bcm2835_gpio_write(_rs, LOW);
    bcm2835_gpio_write(_en, LOW);
    
    
    for(int x=0;x<8;x++){
         bcm2835_gpio_fsel(data_pin[x], BCM2835_GPIO_FSEL_OUTP);
    }
    
    _FourBitMode = !DataLength;
    
    bcm2835_delay(50);
    FourBitWrite(0x03);
    bcm2835_delayMicroseconds(4500);
    FourBitWrite(0x03);
    bcm2835_delayMicroseconds(4500);
    FourBitWrite(0x03);
    bcm2835_delayMicroseconds(150);
    FourBitWrite(0x02);
    
    bcm2835_delay(50);
    send(0,FunctionSet | FourBits | OneLine | Font5x8);
    bcm2835_delay(50);
    send(0,DisplayControl | DisplayOn);
    bcm2835_delay(50);
}


void LCD_display::pulse_en(){
    bcm2835_gpio_write(_en, HIGH);
    bcm2835_delayMicroseconds(5);
    bcm2835_gpio_write(_en, LOW);
    bcm2835_delayMicroseconds(100);
    
}

void LCD_display::send(uint8_t RS, uint8_t DATA) {
    
    bcm2835_gpio_write(_rs,RS);
    
    if (_FourBitMode) {
       FourBitWrite(DATA>>4);
       FourBitWrite(DATA);
    }else{
        EightBitWrite(DATA);
    }
}

void LCD_display::FourBitWrite(uint8_t DATA){
 
    for(uint8_t bit=0;bit<4;bit++){
            bcm2835_gpio_write(data_pin[bit], (DATA>>bit) & 1);
        }
    pulse_en();
    }

void LCD_display::EightBitWrite(uint8_t DATA) {
    
    for(uint8_t bit=0;bit<8;bit++){
        bcm2835_gpio_write(data_pin[bit], DATA>>bit & 1);
        }
    pulse_en();

}
