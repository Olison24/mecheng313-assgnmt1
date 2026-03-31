#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#define THRESHOLD 410

volatile uint16_t result_conversion;

int main() {
  
  cli();

  DDRB |= (1<<DDB5);
  PORTB &= ~(1<<PORTB5);
  
  ADMUX |= (1<<MUX0);
  ADMUX |= (1<<REFS0);
  ADCSRA |= (1<<ADEN)|(1<<ADIE);
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  
  sei();
  
  while(1) {

    result_conversion = 0;
    ADCSRA |= (1<<ADSC);

    _delay_ms(250);

    if (result_conversion >= THRESHOLD) { 
      PORTB |= (1<<PORTB5);
     _delay_ms(250);
     PORTB &= ~(1<<PORTB5);
     _delay_ms(250); 
       PORTB |= (1<<PORTB5);
     _delay_ms(250);
     PORTB &= ~(1<<PORTB5);
    }
    else { 
      PORTB |= (1<<PORTB5);
     _delay_ms(500);
     PORTB &= ~(1<<PORTB5);
     _delay_ms(250);
    }
    
  }

}

ISR(ADC_vect) { 
  result_conversion = ADC; 
}
