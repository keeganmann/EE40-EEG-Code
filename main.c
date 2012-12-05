#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "lcd_ascii.h"
#include "nyan.h"

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
