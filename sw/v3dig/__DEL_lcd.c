////////////////////////////////////////////////////////////////////////////////
// lcd.c                                                                      //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <timer.h>// La función getEvent utiliza timers.
#include <system.h>// Definición de nombres de puertos.
#include <stdio.h>
#include <lcd.h>

////////////////////////////////////////////////////////////////////////////////
// DEFINICION DE VARIABLES GLOBALES                                           //
////////////////////////////////////////////////////////////////////////////////

const char LCD_linAddr[2]={0x00,0x40};
// Para inicializar la estructura del LCD, es necesario crear un arreglo que
// tenga los address (interno al lcd) del primer caracter de cada renglón.

char lcdBuffer[LCD_BUFSIZ]={'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','z','\n',
                            'y','y','y','y','y','y','y','y','y','y','y','y','y','y','y','w'};


FILE lcdFile={
              _READ|_WRITE,
              &lcdBuffer,
              &lcdBuffer,
              &lcdBuffer,
              LCD_BUFSIZ,
              LCD_BUFSIZ,
              LCD_BUFSIZ
              };

t_lcdSettings lcdSettings={1,1,1,1,0,1,
                           1,1,1,1,1,1};

///////////////////////////////////////////////////////////////////////////////
// TABLAS DE ESTADO (modificar para cada caso)                               //
//                                                                           //
// La maquina de estados es un puntero a una de estas tablas, que son        //
// recorridas en busca de un evento, hasta el final de la tabla.             //
//                                                                           //
// Tal como tambien se indica en la seccion "forward declaration of          //
// states", la cantidad "y" de elementos de cada array "sxxx[y]", debe       //
// ser modificada para cada fsm distinta que se haga, debido a que el        //
// compilador da error si se deja la cantidad de elementos indefinida.       //
//                                                                           //
// Acerca de las prioridades en la maquina de estados: no tiene              //
// sentido hablar de prioridades de transicion, debido a que para la         //
// maquina de estados, no ocurren simultaneamente 2 eventos, sino que        //
// siempre se da 1 evento por vez, y esto queda asegurado debido a que       //
// el evento ocurrente es el valor retornado por la invocacion a la          //
// funcion "getEvent()". Por lo tanto, es la funcion "getEvent()" la         //
// la que debera manejar el comportamiento frente a eventos                  //
// simultaneos.                                                              //
///////////////////////////////////////////////////////////////////////////////

const t_lcdState lcdWaitToSetDataLength[]=
{
  {TIMEOUT_30MS,lcdWaitToClearDisplay,SET_DATA_LENGTH},
  {LCD_TABLE_END,lcdWaitToSetDataLength,LCD_DO_NOTHING}
};

const t_lcdState lcdWaitToClearDisplay[]=
{
  {ALWAYS,lcdWaitToSetEntryMode,CLEAR_DISPLAY},
  {LCD_TABLE_END,lcdWaitToClearDisplay,LCD_DO_NOTHING}
};

const t_lcdState lcdWaitToSetEntryMode[]=
{
  {TIMEOUT_30MS,lcdWaitToSetVisibility,SET_ENTRY_MODE},
  {LCD_TABLE_END,lcdWaitToSetEntryMode,LCD_DO_NOTHING}
};

const t_lcdState lcdWaitToSetVisibility[]=
{
  {ALWAYS,lcdWaitForRefresh,SET_VISIBILITY},
  {LCD_TABLE_END,lcdWaitToSetVisibility,LCD_DO_NOTHING}
};

const t_lcdState lcdWaitForRefresh[]=
{
  {TIMEOUT_30MS,lcdCommandFirstLine,REWIND},
  {LCD_TABLE_END,lcdWaitForRefresh,LCD_DO_NOTHING}
};

const t_lcdState lcdCommandFirstLine[]=
{
  {UNFINISHED,lcdCommandFirstLine,SEND_CHARACTER},
  {FIRST_LINE_FINISHED,lcdCommandSecondLine,START_LCD_SECOND_LINE},
  {LCD_TABLE_END,lcdCommandFirstLine,LCD_DO_NOTHING}
};

const t_lcdState lcdCommandSecondLine[]=
{
  {UNFINISHED,lcdCommandSecondLine,SEND_CHARACTER},
  {REFRESH_FINISHED,lcdWaitToSetEntryMode,LCD_INIT_TMR_30MS},
  {LCD_TABLE_END,lcdCommandSecondLine,LCD_DO_NOTHING}
};

////////////////////////////////////////////////////////////////////////////////
// ACCIONES PARA LA FSM                                                       //
////////////////////////////////////////////////////////////////////////////////

void lcdAction000(void)

   {
   lcdNibbleSend(NIBBLE_SEND_INSTR,(LCD_CMD_FUNCTION|LCD_4B_IF)>>4);//Interfase 4 bits
   }

void lcdAction001(void)
   {
   LCD_SEND_COMMAND(LCD_CMD_CLRDISP);
   TMR_START(TMR_30MS_LCD);
   }

void lcdAction002(void)

   {
   if(lcdSettings.incDec_rsh|lcdSettings.shift_rsh)
      {
      lcdSettings.incDec_rsh=0;
      lcdSettings.shift_rsh=0;
      LCD_SEND_COMMAND(LCD_CMD_ENTRYM|(lcdSettings.incDec<<1)|(lcdSettings.shift<<0));
      }
   }

void lcdAction003(void)
   {
   if(lcdSettings.dispVis_rsh|lcdSettings.curVis_rsh|lcdSettings.blink_rsh)
      {
      lcdSettings.dispVis_rsh=0;
      lcdSettings.curVis_rsh=0;
      lcdSettings.blink_rsh=0;
      LCD_SEND_COMMAND(LCD_CMD_VIS|(lcdSettings.dispVis<<2)|
                                   (lcdSettings.curVis<<1)|
                                   (lcdSettings.blink<<0));
      }
   }

void lcdAction004(void)
   {
   char c;

   lcdFile.flg&=~_WRITE;//ya no es de escritura
   lcdFile.flg|=_READ;//es de lectura
   rewind(&lcdFile);
   LCD_SET_DDRAM_ADDR(LCD_linAddr[0]);
   }

void lcdAction005(void)
   {
   char c;

   c=fgetc(&lcdFile);
   LCD_SEND_DATA(c);

   }

void lcdAction006(void)
   {
   TMR_START(TMR_30MS_LCD);
   }

void lcdAction007(void)
   {
   LCD_SET_DDRAM_ADDR(LCD_linAddr[1]);
   }

////////////////////////////////////////////////////////////////////////////////
// EJECUCION DE ACCION PARA LA FSM                                            //
////////////////////////////////////////////////////////////////////////////////

void lcdRunAction(char action)

{

   switch(action)

   {

      case LCD_A000:lcdAction000();break;
      case LCD_A001:lcdAction001();break;
      case LCD_A002:lcdAction002();break;
      case LCD_A003:lcdAction003();break;
      case LCD_A004:lcdAction004();break;
      case LCD_A005:lcdAction005();break;
      case LCD_A006:lcdAction006();break;
      case LCD_A007:lcdAction007();break;

      default:break;

   }

}

char lcdGetEvent(void)
// Para determinar el estado en el que me encuentro, en lugar de hacer un
// "switch", lo que hago es un "if" porque el compilador no permite realizar
// esa instrucción con un puntero, y si quiero hacer un "casteo" de la variable
// también tira error.

   {

   char event=LCD_NO_EVENT;
// Por defecto va a devolver NO_EVENT.

   if(p2tablaDeEstadoLcd==lcdWaitToSetDataLength)
      {
      if(TMR_TIMEOUT(TMR_30MS_LCD))
        event=TIMEOUT_30MS;
      }

   else if(p2tablaDeEstadoLcd==lcdWaitToClearDisplay)
      {
      event=ALWAYS;
      }

   else if(p2tablaDeEstadoLcd==lcdWaitToSetEntryMode)
      {
      if(TMR_TIMEOUT(TMR_30MS_LCD)) event=TIMEOUT_30MS;
      }

   else if(p2tablaDeEstadoLcd==lcdWaitToSetVisibility)
      {
      event=ALWAYS;
      }

   else if(p2tablaDeEstadoLcd==lcdWaitForRefresh)
      {
      if(TMR_TIMEOUT(TMR_30MS_LCD)) event=TIMEOUT_30MS;
      }

   else if(p2tablaDeEstadoLcd==lcdCommandFirstLine)
      {

      if(fgetc(&lcdFile)=='\n') event=FIRST_LINE_FINISHED;
      else
         {
         unget(&lcdFile);
         event=UNFINISHED;
         }
      }

   else if(p2tablaDeEstadoLcd==lcdCommandSecondLine)
      {
//auxChar=fgetc(&lcdFile);
      if(fgetc(&lcdFile)==(char)EOF) event=REFRESH_FINISHED;
//      if(auxChar==(char)EOF) event=REFRESH_FINISHED;
      else
         {
         unget(&lcdFile);
         event=UNFINISHED;
         }
      }

   return event;

   }

////////////////////////////////////////////////////////////////////////////////
// PARSER                                                                     //
////////////////////////////////////////////////////////////////////////////////

const t_lcdState *p2tablaDeEstadoLcd;
// El establecimiento del estado inicial de "p2tablaDeEstadoLcd" es realizado en la
// función "fsmInit".

void lcdFsmParser(void)

   {

   char event;

   event=lcdGetEvent();

   while(p2tablaDeEstadoLcd->event != LCD_TABLE_END &&
         p2tablaDeEstadoLcd->event != event)

      {

      p2tablaDeEstadoLcd++;

      }

   lcdRunAction(p2tablaDeEstadoLcd->action);

   p2tablaDeEstadoLcd=p2tablaDeEstadoLcd->nextState;

   }


void lcdFsmInit(void)
  {
  TMR_START(TMR_30MS_LCD);
  p2tablaDeEstadoLcd=lcdWaitToSetDataLength;
  }

void lcdNibbleSend(char mode,char lowerNibble)
  {
  LCD_RS=mode;
  LCD_DATA_LINES(lowerNibble);
  LCD_E=1;
  LCD_E=0;
  LCD_RS=1;
  }


