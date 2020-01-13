#include <16f877.h>
#include <stdio.h>
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT 
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

char Keypress=' ';
int aux=0;
char movimiento =' ';



#INT_TIMER1
void isr_timer1(){
//printf("CRIDO");
      switch (movimiento){
      
         case 'w':  // Dos servomotors a 90?

            switch(aux){
               case 0:  //temps on els motors estan activats (0,5ms -> 90?)
                  output_high(PIN_B2);
                  //output_low(PIN_B2);
                  set_timer1(65223);
                  aux = 1;
               break;
               case 1:  //temps on els motors apagats (19,5ms)
                  output_low(PIN_B2);
                 // output_high(PIN_B2);
                  set_timer1(53348);
                  aux = 0;                   
               break;
            }
            break;
         
         case 'a': //Dos servomotors a 0?
            switch(aux){
               case 0:  //temps on els motors estan activats (1,5ms -> 0?)
                  output_high(PIN_B2);
                 // output_low(PIN_B2);
                  set_timer1(64598);
                  aux = 1;       
               break;
               case 1:  //temps on els motors apagats (18,5ms)
                  output_low(PIN_B2);
                 // output_high(PIN_B2);
                  set_timer1(53973);
                  aux = 0;                   
               break;
            }            
            break;
            
         case 's': //Dos servomotors a -90?
            switch(aux){
               case 0:  //temps on els motors estan activats (2,5ms -> -90?)
                  output_high(PIN_B2);
                //  output_low(PIN_B2);
                  set_timer1(63973);
                  aux = 1;       
               break;
               case 1:  //temps on els motors apagats (17,5ms)
                  output_low(PIN_B2);
                 // output_high(PIN_B2);
                  set_timer1(54598);
                  aux = 0;                   
               break;
            }            
            break;           
      }
         
   }

      
#int_rda
void serial_isr() {
   Keypress=0x00;
   if(kbhit()){
   Keypress=getc();
    putchar(Keypress);
      switch(keypress){
         case 'w':
            movimiento = 'w';
            
         break;
         
         case 'a':
            movimiento = 'a';
         break;
         
         case 's':
            movimiento = 's';
         break;
    }
  }
}

void main(){
   set_tris_b(0x00);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //activa el timer 1
   enable_interrupts(int_rda);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(global);
   
   do{
   
   }while(true);
}
