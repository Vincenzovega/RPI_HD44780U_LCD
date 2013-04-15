#include <inttypes.h>
#include <bcm2835.h>

// Commands:

#define ClearDisplay                0b00000001
#define ReturnHome                  0b00000010
#define EntryModeSet                0b00000100
#define DisplayControl              0b00001000
#define CursorDisplayShift          0b00010000
#define FunctionSet                 0b00100000
#define SetCGRAMAddr                0b01000000
#define SetDDRAMAddr                0b10000000

//EntryModeSet:
#define Shift                       0b00000001

#define Decrement                   0b00000000
#define Increment                   0b00000010

//DisplayControl

#define DisplayOn                   0b00000100
#define CursorOn                    0b00000010
#define BlinkOn                     0b00000001

// CursorDisplayShift

#define DisplayShift                0b00001000
#define CursorMove                  0b00000000

#define Right                       0b00000100
#define Left                        0b00000000

//FunctionSet

#define EightBits                       0b00010000
#define FourBits                       0b00000000

#define TwoLines                      0b00001000
#define OneLine                       0b00000000

#define Font5x8                         0b00000000
#define Font5x10                        0b00000100


class LCD_display {
    public:
    
LCD_display(uint8_t PIN_RS, uint8_t PIN_EN, uint8_t PIN_RW, uint8_t PIN_0, uint8_t PIN_1, uint8_t PIN_2, uint8_t PIN_3);

LCD_display(uint8_t PIN_RS, uint8_t PIN_EN, uint8_t PIN_RW, uint8_t PIN_0, uint8_t PIN_1, uint8_t PIN_2, uint8_t PIN_3,
uint8_t PIN_4, uint8_t PIN_5, uint8_t PIN_6, uint8_t PIN_7);

void init(uint8_t DataLength,uint8_t PIN_RS,uint8_t PIN_EN,uint8_t PIN_RW,uint8_t PIN_0,uint8_t PIN_1,uint8_t PIN_2,uint8_t PIN_3,
uint8_t PIN_4,uint8_t PIN_5,uint8_t PIN_6,uint8_t PIN_7); 

void pulse_en();

void send(uint8_t RS,uint8_t DATA);

void FourBitWrite(uint8_t DATA);
void EightBitWrite(uint8_t DATA);
    
    private:
    uint8_t _rs;
    uint8_t _en;
    uint8_t _rw;
    
    uint8_t data_pin[8];
    
    uint8_t _FourBitMode; 
    
    
};
    
