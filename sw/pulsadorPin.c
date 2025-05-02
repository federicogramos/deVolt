////////////////////////////////////////////////////////////////////////////////
// pulsadorPin.c                                                                      //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <pulsadorPin.h>

// DEFINICION DE VARIABLES GLOBALES                                           //

//char pulsPinMem[PULS_PIN_BUFSIZ];

char pulsPinBuffer;// PulsPin: los pines tocados se identifican de 1..N porque el 0 se reserva para indicar "ninguno ha sido presionado"

t_pulsPin pulsPin[PULS_PIN_CANT]={{(char*)&PORTB,0,1,1,0},
                                  {(char*)&PORTB,1,1,1,0},
                                  {(char*)&PORTB,3,1,1,0}};

// Chequea por eventos en todos los pulsadores y los carga en el buffer.
// Para recoger los mensajes usar fgetc().
// Para ejecutar con periodo de 0.075s
void pulsPinDriver(void)
   {
   char i,j;

   for(i=0;i<PULS_PIN_CANT;i++)
      {
      pulsPin[i].state=BIT_GETVAL(*(pulsPin[i].p2port),pulsPin[i].bitNum);
      if(pulsPin[i].timer) pulsPin[i].timer--;
      else if(pulsPin[i].state!=pulsPin[i].prevState)
         {
         pulsPin[i].timer=PULS_PIN_N_ANTIREBOTE;
         if(pulsPin[i].state==1 && pulsPin[i].prevState==0) pulsPinBuffer=(i+1);
         pulsPin[i].prevState=pulsPin[i].state;
         }
      }
   }
