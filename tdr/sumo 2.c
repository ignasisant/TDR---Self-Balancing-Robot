#include <16f877.h>                    // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,PUT,BROWNOUT // Opciones de configuraci?n
#use delay(clock=20000000)              // Velocidad del Cristal : 20 Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definici?n del RS232

int aux=0;                           // variable auxiliar usada al timer 1
int movimiento=5;                    // variable que regulara el switch case del timer 1, comen?ara en parada
int umbral_linia=80;                 // calibracio dels sensors de linea
int umbral_distancia_esquerra=40;    // calibracio sensors distancia
int umbral_distancia_dreta=40;       // calibracio sensor distancia
int endavant=0;                      // definim nom a les funcions del switch case del timer 1 
int endarrere=2;
int rastreig=6;
int volta_rellotge=7;
int volta_antirellotge=8;
int dreta_linia, dreta_ulls, esquerra_linia, esquerra_ulls, central_linia; // definim les variables dels valors dels sensors

#INT_TIMER1                             // Interrupci? per desbordament
void isr_timer1() {                                 
      switch(movimiento){
         case 0:                        // endavant
            switch(aux){
               case 0:                    // si aux es 0 va endavant
               
               output_high(PIN_B2);       // fem un high als dos durant 0,5 ms
               output_high(PIN_B1);
               set_timer1(65223);         
               aux++;                     // cambien l'estat de l'auxiliar
               break;
              
              case 1:
               output_low(PIN_B2);        // un low al connectat al B2 durant 2 ms
               set_timer1(64286);
               aux++;
               break;
               
               case 2:                    // quan cambia l'estat de l'auxiliar
               output_low(PIN_B1);        // es baixa l'estat de l'altre durant 17,5 ms
               set_timer1(54598);        
               aux=0;
               break;
            }
             break;  
          
          case 1:                         // aquesta funcio realitzaria un fre actiu (no usat al programa)
               switch(aux){
               case 0:
               output_high(PIN_B2);
               output_high(PIN_B1);
               set_timer1(64598);
               aux++;
               break;
               
               case 1:
               output_low(PIN_B2);
               output_low(PIN_B1);
               set_timer1(53973);
               aux=0;
               break;
               
               case 2:                    // en cas de que l'auxiliar sigui 2 fara el mateix que si fos 1
               output_low(PIN_B2);
               output_low(PIN_B1);
               set_timer1(53973);
               aux=0;
               break;
               }
               
             break;  
           case 2:                        // enrere
               switch(aux){
               case 0:                    // si aux es 0 va endavant
               output_high(PIN_B2);       // fem un high als dos durant 0,5 ms
               output_high(PIN_B1);
               set_timer1(65223);         
               aux++;                     // cambien l'estat de l'auxiliar
               break;
              
              case 1:
               output_low(PIN_B1);        // un low al connectat al B1 durant 2 ms
               set_timer1(64286);
               aux++;
               break;
               
               case 2:                    // quan cambia l'estat de l'auxiliar
               output_low(PIN_B2);        // es baixa l'estat de l'altre durant 17,5 ms
               set_timer1(54598);         // durant 17,5 ms
               aux=0;
               break;
            }
            break;
            
             case 5:                      // per fer la parada simplement no donarem senyal als motors
               output_low(PIN_B2);
               output_low(PIN_B1);
               break;
               
             case 6:                      // es realitza un gir per a buscar el robot contrari
               
                  switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(65223);            // enviem una senyal de 0,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // mantenim la senyal al pin_b1 durant aproximadament 1 ms
                     set_timer1(64900);            // d'aquesta manera una roda gira i l'altre es mant? fixa permeten abarcar mes rang de deteccion
                     aux=0;
                     break;
                     case 2:                       
                     output_low(PIN_B1);
                     set_timer1(53973);            // la resta de temps (18,5 ms) mantenim la senyal en low
                     aux=0;
                     break;
                     }
                  break;
                 case 7:                           // un gir en el sentit contrari
                     switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(65223);            // enviem una senyal de 0,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // la resta (19,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(53348);
                     aux=0;
                     break;
                     case 2:                       // cap la possibilitat que aux=2 quan entri en aquest cas, per aixo es repeteix la comanda
                     output_low(PIN_B2);           // la resta (19,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(53348);
                     aux=0;
                     break;
                     }
                     break;
                     
                  case 8:                         // gir en l'altre sentit
                     switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(63973);            // enviem una senyal de 2,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // la resta (17,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(54598);
                     aux=0;
                     break;
                     case 2:                       // el mateix que en el cas anterior
                     output_low(PIN_B2);           // la resta (17,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(54598);
                     aux=0;
                     break;
                  }
                  break;
               }          
      }



void linia(){           // una funcio que llegeix els sensors inferiors que llegeixen la linea
   set_adc_channel(5);
   delay_ms(1);
   dreta_linia = read_adc();
   
   set_adc_channel(6);
   delay_ms(1);
   central_linia= read_adc();
   
   set_adc_channel(7);
   delay_ms(1);
   esquerra_linia = read_adc();
}
void ulls(){            // una funcio que ens dona els valors dels sensors de distancia
   set_adc_channel(2);
   delay_ms(1);
   dreta_ulls = read_adc();
   
   set_adc_channel(3);
   delay_ms(1);
   esquerra_ulls = read_adc();
}
   
   
void main(void){
  int auxiliar=0;       // definim una variable auxiliar
  set_tris_b(0x00);     // definim els ports b (on son els servos) com a output

  setup_adc(ADC_CLOCK_INTERNAL);
  setup_adc_ports(ALL_ANALOG);
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);                //definim timer 1
  enable_interrupts(int_rda);               //habilitem les interrupcions

  enable_interrupts(INT_TIMER1);
  enable_interrupts(global);  
  
  delay_ms(5000);       // 5 segons abans de iniciar el programa
  while(1){
  ulls();               // llegim els valors tant de els sensors de distancia com els de linea
  linia();
  if (dreta_linia < umbral_linia){      // si es dispara el sensor de linea dret
      if (auxiliar != 1){
      movimiento = endarrere;           // anira enrere 1 cop durant 700 ms i girara sobre si mateix durant 500 ms
      delay_ms(700);
      }
      movimiento=volta_antirellotge;
      delay_ms(500);
      auxiliar=1;
  }
  
  if (esquerra_linia < umbral_linia){    // semblant per als altres sensors
      if (auxiliar != 2){
         movimiento = endarrere;
         delay_ms(700);
         }
         movimiento=volta_rellotge;
         delay_ms(500);
         auxiliar=2;
  }
  if (central_linia < umbral_linia){    
      if (auxiliar != 2){
         movimiento = endarrere;
         delay_ms(700);
         }
         movimiento=volta_rellotge;
         delay_ms(500);
         auxiliar=2;
  }
  if (dreta_ulls > umbral_distancia_dreta){        // si detectem al sensor de la dreta
     if (esquerra_ulls > umbral_distancia_esquerra){  // i detectem al de l'esquerra
     movimiento=endavant;                             // el robot anira endavant
           }
     else{
     movimiento=volta_rellotge;                    // si nomes llegeix dreta, llavors fara un gir en sentit de les agulles del rellotge
     }
  }
  else{
   if (esquerra_ulls > umbral_distancia_esquerra){ // si no detecta dreta pero si esquerra, fara un gir en l'altre sentit
     movimiento=volta_antirellotge;
     }
     else{                    // si no detecta res
     if (auxiliar != 3){      
     movimiento=endavant;     // anira endavant durant 500 ms
     delay_ms(500);           // possible contramesura per si es empes per un lateral o per darrere
     }
     auxiliar=3;              
     movimiento=rastreig;     // inicia el moviment de rastreig
     
     }
  }
  
  }
}
