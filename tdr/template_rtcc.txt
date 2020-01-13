#include <16f877.h>                    // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,PUT,BROWNOUT // Opciones de configuración
#use delay(clock=20000000)              // Velocidad del Cristal : 4 Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definición del RS232

byte const NInts=30;                   // Numero de interrupciones para 1 Segundo (CALCULADLO)!!!!!!!!

// VARIABLES GLOBALES

int16 C_Ints=0;                         // Contador de Interrupciones ocurridas
char Flag=0;                           // Flag que cambia cada NInts interrupciones


#int_RTCC                              // Interrupción por desbordamiento
void RTCC_isr() {                           // del TIMER0 RTCC

  if(C_Ints > NInts){                  // Si las ints ocurridas > ints para 1 Seg.

    if(Flag==0){
      Flag=1;
    }
    else{
      Flag=0;
    }
    C_Ints=0;                          // Reinicializo Contador de Ints
  }
  ++C_Ints;                            // Incremento el número de interrupciones
}                                      // Ocurridas



void main(void) {
  char K;
  K=Flag;
  setup_counters(RTCC_INTERNAL,RTCC_DIV_128);// TIMER0: Clock Interno, Presescaler 128
  enable_interrupts(INT_RTCC);               // Habilito Interrupción RTCC
  enable_interrupts(global);                 // Habilito Interrupciones



  do{ // Bucle infinito

    if(Flag==K){}
    else
    {                                        // si ha cambiado Flag ...

      printf("Ha pasado un segundo\n\r");
      K=Flag;                                // Guardo estado anterior de Flag
    }

  }While(TRUE);
}
