#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)

void main(void)
{
byte x=0;
set_tris_d(0xff);
set_tris_b(0x00);

while(1)
{
   x=input_d();
   output_b(x);
}
}
