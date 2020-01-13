
#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  // Definicion del RS232


void linia(){ //funcio per poder llegir els sensors de linia
   int esquerra, dreta, central; 
   set_adc_channel(5);
   delay_ms(1);
   dreta = read_adc();
   
   set_adc_channel(6);
   delay_ms(1);
   central = read_adc();
   
   set_adc_channel(7);
   delay_ms(1);
   esquerra = read_adc();
   
   delay_ms(100);
     printf("Linia:%u - %u - %u\n\r",dreta, central, esquerra);
}
void ulls(){ //funcio per poder llegir els sensor sharp
   int esquerra, dreta;
   set_adc_channel(2); //activem la sortida que volem llegir 
   delay_ms(1);
   dreta = read_adc(); //llegim el valor 
   
   set_adc_channel(3); //activem l'altre sortida  
   delay_ms(1);
   esquerra = read_adc(); //llegim el valor

   delay_ms(100);
   printf("Ulls:%u - %u\n\r",dreta, esquerra);
   
}
   

void main(){

   
   setup_adc(ADC_CLOCK_INTERNAL); //activem el clock intern
   setup_adc_ports(ALL_ANALOG); //activem tots els pins analogics 
   
   

while(1){
   //ulls();
   linia();
}
}
