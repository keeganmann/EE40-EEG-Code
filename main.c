#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>

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

void beep(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(0.5);
    }
    _delay_ms(100);
}
void beep_low(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(BUZZER);
        _delay_ms(3);
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

/***** MAIN *****/

int main() {
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
            beep();
            //nyan();
            //nyan_reset();
        }
        if (b){
            toggle_led_2();
            beep();
        }
        if (c){
            toggle_led_3();
            beep();
        }
        if (d){
            toggle_led_4();
            beep();
        }
        if (e){
            toggle_led_1();
            toggle_led_2();
            toggle_led_3();
            toggle_led_4();
            beep_low();
        }
    }
    return 0;
}
