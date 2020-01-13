
#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT 
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  // Definicion del RS232

int esquerra, dreta, central; 
int esquerra_u, dreta_u;
char movimiento=' ';
int aux=0;


#INT_TIMER1
void isr_timer1(){





 switch (movimiento){
      
         case 'w': //adelante Servo 1
         
          switch(aux){
          
            case 0:
             output_high(PIN_B1);
             output_low(PIN_B2);
             set_timer1(63973);//2.5
            //  printf("adelante0\n\r");
              aux=1;
            break;
            
            case 1:
              output_low(PIN_B1);
              output_high(PIN_B2);
             set_timer1(54598);//17.5
              //printf("adelante1\n\r");
             aux=0;
            break;
          }
         
         break;
         
         
         case 'p'://para Servo 1
         switch(aux){
          
            case 0:
             output_high(PIN_B1);
             output_low(PIN_B2);
             set_timer1(64598);
             
              aux=1;
            break;
            
            case 1:
              output_low(PIN_B1);
              output_high(PIN_B2);
             set_timer1(53973);
            
             aux=0;
            break;
          }
         break;
          
          case 'a': //atras Servo 1
         switch(aux){
          
            case 0:
             output_high(PIN_B1);
             output_high(PIN_B2);
             set_timer1(65223);//0.5
              //printf("atras0\n\r");
             aux=1;
            break;
            
            case 1:
              output_low(PIN_B1);
              output_low(PIN_B2);
             set_timer1(53348);//19.5
              //printf("atras1\n\r");
             aux=0;
            break;
          }
           break;
          
          case 's': //atras Servo 1
         switch(aux){
          
            case 0:
             output_low(PIN_B1);
             output_low(PIN_B2);
             set_timer1(63661);//0.5
              //printf("atras0\n\r");
             aux=1;
            break;
            
            case 1:
             output_high(PIN_B1);
             output_high(PIN_B2);
             set_timer1(54910);//19.5
              //printf("atras1\n\r");
             aux=0;
            break;
          }
           break;
           
          case 'c': //atras Servo 1
         switch(aux){
          
            case 0:
             output_low(PIN_B1);
             output_low(PIN_B2);
             set_timer1(64442);//0.5
              //printf("atras0\n\r");
             aux=1;
            break;
            
            case 1:
             output_high(PIN_B1);
             output_high(PIN_B2);
             set_timer1(54129);//19.5
              //printf("atras1\n\r");
             aux=0;
            break;
          }
           break;
          case 'z': //atras Servo 1
         switch(aux){
          
            case 0:
             output_low(PIN_B1);
             output_low(PIN_B2);
             set_timer1(64755);//0.5
              //printf("atras0\n\r");
             aux=1;
            break;
            
            case 1:
             output_high(PIN_B1);
             output_high(PIN_B2);
             set_timer1(53816);//19.5
              //printf("atras1\n\r");
             aux=0;
            break;
          }
          
         break;
         
      }
       
       
       
       
       
}



void linia(){ //funcio per poder llegir els sensors de linia
   
   set_adc_channel(5);
   delay_ms(1);
   dreta = read_adc();
   if (dreta > 150) dreta = 1;  // troba negre
   else dreta = 0;
   set_adc_channel(6);
   delay_ms(1);
   central = read_adc();
    if (central > 150) esquerra = 1;  // troba negre
    else central = 0;
   set_adc_channel(7);
   delay_ms(1);
   esquerra = read_adc();
   if (esquerra > 150) esquerra = 1;  // troba negre
   else esquerra = 0;
   
   delay_ms(100);
    
}

void ulls(){ //funcio per poder llegir els sensor sharp
   
   set_adc_channel(2); //activem la sortida que volem llegir 
   delay_ms(1);
   dreta_u = read_adc(); //llegim el valor 
   if (dreta_u > 100) dreta_u = 1;  // troba negre
   else dreta_u = 0;
   
   set_adc_channel(3); //activem l'altre sortida  
   delay_ms(1);
   esquerra_u = read_adc(); //llegim el valor
   if (esquerra_u > 100) esquerra_u = 1;  // troba negre
   else esquerra_u = 0;

   delay_ms(100);
   
   
}
   

void main(){

 
   
   setup_adc(ADC_CLOCK_INTERNAL); //activem el clock intern
   setup_adc_ports(ALL_ANALOG); //activem tots els pins analogics 
   
   set_tris_b(0x00);
   

   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //activa el timer 1

  
   enable_interrupts(INT_TIMER1);
   enable_interrupts(global);

while(1){
   ulls();
   linia();
   if ((dreta == 1 && central == 1 && esquerra == 1) || (dreta_u == 1 && esquerra_u == 1))movimiento = 'w';        
   else if ((dreta == 0 && esquerra == 0) || (central == 0 && dreta == 0 && esquerra == 0))
   {
      movimiento = 's';
      delay_ms(500);
      movimiento = 'p';
   }
   else if (dreta == 0 && (esquerra == 1 && (central == 1 || central == 0)))
   {
      movimiento = 'a';
      delay_ms(500);
      movimiento = 'p';
   } 
   else if (esquerra == 0 && (dreta == 1 && (central == 1 || central == 0)))
   {
      movimiento = 'd';
      delay_ms(500);
      movimiento = 'p';
   }       
   else if (dreta_u == 1 && esquerra_u == 0)
   {
      movimiento = 'c';
      delay_ms(500);
      movimiento = 'p';
   } 
   else if (dreta_u == 0 && esquerra_u == 1)
   {
      movimiento = 'z';
      delay_ms(500);
      movimiento = 'p';
   } 
}

}
