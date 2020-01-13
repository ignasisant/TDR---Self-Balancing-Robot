#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)

#define DELAY_COUNTER_VALUE    100

void main(void)
{
unsigned long m_delay_counter=DELAY_COUNTER_VALUE;
int1 x=0,int8 a;
set_tris_d(0xff);
set_tris_b(0x00);
output_b(0);

while(1)
{
  for (a = 0; a < 8; a++)
  {
   output_bit(PIN_B5,a);
   
   
  }
  
}
}
