////////////////////////////////////////////////////////////////////////////////
// system.c                                                                   //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <system.h>
#include <interrupts.h>
#include <adc.h>

void systemInit(void)
   {
   OSCCONbits.SCS=0x00; //System Clock = Primary oscillator
   UCFGbits.UTRDIS=1;//necesario para poder usar RC4/5 como digital input
   RCONbits.IPEN=1;//low priority interrupts enable
   INTCON2bits.RBPU=0;// pull ups portb

   IPR2bits.TMR3IP=0;//interrupt timer 3 es low priority
   IPR1bits.ADIP=0;//int AD low priority

   //ADCON1bits.PCFG=0x0F;//para que todos los pines sean digitales y poder leer sus estados digitales.
   adcSetup();

   IRQ_TIMER0_SETUP();
   IRQ_TIMER3_SETUP();

   INIT_DDR();// Establece los puertos de entrada/salida.
   INIT_PORTS();// Al arranque, pone en un estado conocido a las salidas.

   INTCONbits.TMR0IE=1;
   PIE2bits.TMR3IE=1;
 
   INTCONbits.PEIE=1;
   INTCONbits.GIE=1;
   INTCONbits.GIEH=1;
   INTCONbits.GIEL=1;
   }

