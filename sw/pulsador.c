////////////////////////////////////////////////////////////////////////////////
// pulsador.c                                                                      //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <stdio.h>
#include <pulsador.h>

// DEFINICION DE VARIABLES GLOBALES                                           //

char pulsBuffer[PULS_BUFSIZ];
FILE pulsFile={
              _READ|_WRITE,
              &pulsBuffer,
              &pulsBuffer,
              &pulsBuffer,
              PULS_BUFSIZ,
              PULS_BUFSIZ,
              PULS_BUFSIZ
              };

t_puls puls[PULS_CANT]={
                       {(char*)&PORTA,0,0,0,0,0},{(char*)&PORTA,0,0,0,0,0},
                       {(char*)&PORTA,0,0,0,0,0},{(char*)&PORTA,0,0,0,0,0}
                       };

// Chequea por eventos en todos los pulsadores y los carga en el buffer.
// Para recoger los mensajes usar fgetc().
void pulsDriver(void)
  {
  char i;

  for(i=0;i<PULS_CANT;i++)
    {
    puls[i].state=BIT_GETVAL(*puls[i].p2port,puls[i].bitNum);
    if(!puls[i].inhibit && puls[i].state!=puls[i].prevState)
      {
      puls[i].prevState=puls[i].state;
      puls[i].inhibit=1;
      puls[i].timer=N_ANTIREBOTE;
      if(puls[i].state==0) fputc(PUL_DWN&i,&pulsFile);
      else fputc(PUL_UP&i,&pulsFile);
      }
    }
  }

// Decrementa los timers de botones durante debouncing.
// Al llegar a 0, rehabilita el boton.
void pulsInterruptDriver(void)
  {
  char i;

  for(i=0;i<PULS_CANT;i++)
    if(puls[i].inhibit && --puls[i].timer==0) puls[i].inhibit=0;
  }