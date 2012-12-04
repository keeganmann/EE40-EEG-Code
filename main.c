#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>
#include <avr/pgmspace.h>

#define BUZZER 6 //PORTD

#define TS_A 3   //PORTD
#define TS_B 4   //PORTD
#define TS_C 2   //PORTD
#define TS_D 5   //PORTC
#define TS_E 4   //PORTC

#define LED_1 0  //PORTB
#define LED_2 1  //PORTB
#define LED_3 2  //PORTB
#define LED_4 3  //PORTC

#define TOUCH_SENSE_THRESHOLD 4
#define TOUCH_SENSE_CHARGE_TIME 1.0

/***** SOUND *****/

void setup_buzzer(){
    DDRD |= _BV(BUZZER);
}

void beep_A4(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(2.27272727);
    }
    _delay_ms(100);
}
void beep_A5(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(1.13636363);
    }
    _delay_ms(100);
}
void beep_C5(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(0.95556617);
    }
    _delay_ms(100);
}
void beep_E5(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(0.75843761);
    }
    _delay_ms(100);
}
void beep_G5(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(0.6377551);
    }
    _delay_ms(100);
}

/***** TOUCH *****/

void setup_touch(){
    DDRD |= _BV(TS_A) | _BV(TS_B) | _BV(TS_C);
    DDRC |= _BV(TS_D) | _BV(TS_E);
    MCUCR |= _BV(PUD);
}

uint8_t touch_sense_a_raw(){
    //return touch_sense_raw(&DDRD, &PORTD, &PIND, TS_A);
     uint8_t i = 0;
     //charge pin
     DDRD |= _BV(TS_A);  //output
     PORTD |= _BV(TS_A); //high
     _delay_ms( TOUCH_SENSE_CHARGE_TIME );  //charge time
     //read pin
     DDRD &= ~_BV(TS_A);
     while(PIND & _BV(TS_A)){
         i++;
     }
     return i;
}
uint8_t touch_sense_b_raw(){
    //return touch_sense_raw(&DDRD, &PORTD, &PIND, TS_A);
     uint8_t i = 0;
     //charge pin
     DDRD |= _BV(TS_B);  //output
     PORTD |= _BV(TS_B); //high
     _delay_ms( TOUCH_SENSE_CHARGE_TIME );  //charge time
     //read pin
     DDRD &= ~_BV(TS_B);
     while(PIND & _BV(TS_B)){
         i++;
     }
     return i;
}
uint8_t touch_sense_c_raw(){
    //return touch_sense_raw(&DDRD, &PORTD, &PIND, TS_A);
     uint8_t i = 0;
     //charge pin
     DDRD |= _BV(TS_C);  //output
     PORTD |= _BV(TS_C); //high
     _delay_ms( TOUCH_SENSE_CHARGE_TIME );  //charge time
     //read pin
     DDRD &= ~_BV(TS_C);
     while(PIND & _BV(TS_C)){
         i++;
     }
     return i;
}
uint8_t touch_sense_d_raw(){
    //return touch_sense_raw(&DDRD, &PORTD, &PIND, TS_A);
     uint8_t i = 0;
     //charge pin
     DDRC |= _BV(TS_D);  //output
     PORTC |= _BV(TS_D); //high
     _delay_ms( TOUCH_SENSE_CHARGE_TIME );  //charge time
     //read pin
     DDRC &= ~_BV(TS_D);
     while(PINC & _BV(TS_D)){
         i++;
     }
     return i;
}
uint8_t touch_sense_e_raw(){
    //return touch_sense_raw(&DDRD, &PORTD, &PIND, TS_A);
     uint8_t i = 0;
     //charge pin
     DDRC |= _BV(TS_E);  //output
     PORTC |= _BV(TS_E); //high
     _delay_ms( TOUCH_SENSE_CHARGE_TIME );  //charge time
     //read pin
     DDRC &= ~_BV(TS_E);
     while(PINC & _BV(TS_E)){
         i++;
     }
     return i;
}

uint8_t touch_sense_a(){
    return touch_sense_a_raw() > TOUCH_SENSE_THRESHOLD;
}
uint8_t touch_sense_b(){
    return touch_sense_b_raw() > TOUCH_SENSE_THRESHOLD;
}
uint8_t touch_sense_c(){
    return touch_sense_c_raw() > TOUCH_SENSE_THRESHOLD;
}
uint8_t touch_sense_d(){
    return touch_sense_d_raw() > TOUCH_SENSE_THRESHOLD;
}
uint8_t touch_sense_e(){
    return touch_sense_e_raw() > TOUCH_SENSE_THRESHOLD;
}

/***** LIGHT *****/

void setup_leds(){
    DDRB |= _BV(LED_1) | _BV(LED_2) | _BV(LED_3);
    DDRC |= _BV(LED_4);
}

void toggle_led_1(){
    PORTB ^= _BV(LED_1);
}
void toggle_led_2(){
    PORTB ^= _BV(LED_2);
}
void toggle_led_3(){
    PORTB ^= _BV(LED_3);
}
void toggle_led_4(){
    PORTC ^= _BV(LED_4);
}

/***** NYAN CAT *****/

extern void setup();
extern void loop();

void nyan(){
    TCCR0A |= _BV(COM0A0) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(WGM02) | _BV(CS01);
    OCR0A = 255;
    setup();
    loop();
}
void nyan_reset(){
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A = 0;
}

/***** LCD *****/

static const uint8_t ASCII[][5] PROGMEM =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

#define SCE  1  //PORTC     chip enable (inverted)
#define RST  0  //PORTC     reset
#define DC   1  //PORTB     data (1) or command (0)
#define MOSI 3  //PORTB     
#define SCK  5  //PORTB     serial clock

void send_byte(uint8_t byte){
    PORTC &= ~_BV(SCE);

    uint8_t i;
    for (i = 0; i < 8; i++){
        PORTB &= ~_BV(SCK);
        if(byte & (0x80 >> i)){
            PORTB |= _BV(MOSI);
        }
        else{
            PORTB &= ~_BV(MOSI);
        }
        PORTB |= _BV(SCK);
        PORTB &= ~_BV(SCK);
    }

}

void send_string(char *string){
    uint8_t i = 0;
    uint8_t ii;
    uint8_t c;
    while ( (c = string[i]) != '\0' ){
        i++;
        for (ii = 0; ii < 5; ii++){
            send_byte( pgm_read_byte(&( ASCII[c-' '][ii] )));
        }
        send_byte(0);
    }
}

void lcd_setup(){
    DDRC |= _BV(SCE) | _BV(RST);
    DDRB |= _BV(DC) | _BV(MOSI) | _BV(SCK);

    //reset
    PORTC |= _BV(RST);
    //_delay_ms(10);
    PORTC ^= _BV(RST);

    PORTC |= _BV(SCE);
    PORTC &= ~_BV(SCE);

    PORTC ^= _BV(RST);
    
    PORTB &= ~_BV(DC);
    send_byte(0x21);
    send_byte(0xBF);
    send_byte(0x04);
    send_byte(0x14);
    send_byte(0x20);
    send_byte(0x0C);

    PORTB |= _BV(DC);
}


/***** MAIN *****/

int main() {
    lcd_setup();
    setup_leds();
    setup_buzzer();
    setup_touch();

    while(1) {
        uint8_t a = touch_sense_a();
        uint8_t b = touch_sense_b();
        uint8_t c = touch_sense_c();
        uint8_t d = touch_sense_d();
        uint8_t e = touch_sense_e();
        if (a){
            toggle_led_1();
            beep_A5();
            //nyan();
            //nyan_reset();
            send_string("Hello world! How are you? I am swell--Sure am. Isn't it great, dude... Yep, sure is!");
        }
        if (b){
            toggle_led_2();
            beep_C5();
        }
        if (c){
            toggle_led_3();
            beep_E5();
        }
        if (d){
            toggle_led_4();
            beep_G5();
        }
        if (e){
            toggle_led_1();
            toggle_led_2();
            toggle_led_3();
            toggle_led_4();
            beep_A4();
        }
    }
    return 0;
}
