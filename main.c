#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>

void beep(){
    int i;
    for (i = 0; i < 100; i++){
        PORTD ^= _BV(6);
        _delay_ms(1);
    }
    _delay_ms(100);
}

int main() {
    //Buzzer
    DDRD |= _BV(6);
    //Touch
    DDRD |= _BV(4);
    MCUCR |= _BV(PUD);

    while(1) {
        uint8_t i = 0;
        //charge pin
        DDRD |= _BV(4);  //output
        PORTD |= _BV(4); //high
        _delay_ms( 1 );  //charge time
        //read pin
        DDRD &= ~_BV(4);
        while(PIND & _BV(4)){
            i++;
        }
        //buzz
        for (; i > 0; i--){
            beep();
        }

        _delay_ms(1000);
    }
    return 0;
}
