#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)


void main(void)
{
int1 x=0;
int8 a; // a serveix per saber si hem d'avan�ar enrere o endevant
int1 k = 0; // k serveix per avan�ar
output_d(0);
a = 1;

while(1)
{
if (input(PIN_B5) == 1)
{
 output_d(a);
 
  if (k == 0)a*=2;
  if (k == 1)a/=2;
  if (a == 1)k = 0;
  if (a == 128)k = 1;
  delay_ms(200);
  output_d(0);
}
}
}
