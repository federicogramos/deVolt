// adc.c

#include <projectHeader.h>
#include <adc.h>

t_adc adcStruct;

void adcDriver(void)
   {
   char ch2Cnv;

   if(adcStruct.flgs2convert && !adcStruct.inProcessFlg)
      {
      do
         {
         ch2Cnv=adcStruct.nx2convert;
         if(adcStruct.nx2convert<=12) adcStruct.nx2convert++;
         else adcStruct.nx2convert=0;
         }
      while(!BIT_GETVAL_QUICK(adcStruct.flgs2convert,ch2Cnv));

      ADCON0bits.CHS=ch2Cnv;
//ADCON0bits.CHS=12;

      BIT_CLR(adcStruct.flgs2convert,ch2Cnv);
      adcStruct.inProcessFlg=1;
      adcStruct.completeFlg=0;
      ADCON0bits.GODONE=1;
      }
   }

int getConv(void)
   {
   adcStruct.inProcessFlg=0;
   adcStruct.completeFlg=0;
   return ADRES;
   }

void isr_adc(void)
   {
   adcStruct.chComp=ADCON0bits.CHS;
   adcStruct.completeFlg=1;

   PIR1bits.ADIF=0;
   }

void adcSetup(void)
   {
   ADCON1bits.PCFG=0x0F;//AN12 usado, pero seteo todo como digital y uso entrada digital seteada en entrada para leer voltaje analogico
   ADCON2bits.ADCS=0x06;//Conversion Clock = FOSC/64
   ADCON2bits.ACQT=0x00;//Acquisition Time = no time
   ADFM=1;
   ADCON0bits.ADON=1;
   PIR1bits.ADIF=0;
   PIE1bits.ADIE=1;
   }
