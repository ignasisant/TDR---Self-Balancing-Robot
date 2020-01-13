#include <16f877.h> // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT // Opciones de configuración
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definición del RS232

char Keypress=' ';

#int_rda
void serial_isr() {

  Keypress=0x00;
  if(kbhit()){
    Keypress=getc();
    if(Keypress!=0x00){
      putchar(keypress+1);
      keypress=0x00;
    }
  }
}


void main() {

  enable_interrupts(global);
  enable_interrupts(int_rda);

  printf("\r\n\Listen on RS232 (Int)\r\n");

  do {


  } while (TRUE);
}
