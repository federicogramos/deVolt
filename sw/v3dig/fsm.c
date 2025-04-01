////////////////////////////////////////////////////////////////////////////////
// fsm.c                                                                      //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <fsm.h>
#include <timer.h>
#include <pulsadorPin.h>
#include <mainDefinitions.h>
#include <system.h>// Para la inicialización del sistema.

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

t_state s000[]=
{
  {SET_PRESSED,&s001[0],DO_NOTHING},
  {TABLE_END,&s000[0],DO_NOTHING}
};

t_state s001[]=
{
  {SET_PRESSED,s002,DO_NOTHING},
  {INC_PRESSED,s001,INC_MIN},
  {DEC_PRESSED,s001,DEC_MIN},
  {TABLE_END,s001,DO_NOTHING}
};

t_state s002[]=
{
  {SET_PRESSED,s000,DO_NOTHING},
  {INC_PRESSED,s002,INC_HORA},
  {DEC_PRESSED,s002,DEC_HORA},
  {TABLE_END,s002,DO_NOTHING}
};

////////////////////////////////////////////////////////////////////////////////
// ACCIONES PARA LA FSM                                                       //
////////////////////////////////////////////////////////////////////////////////

void fAction000(void)
   {
   //min==59? min=0:min++;
   }

void fAction001(void)
   {
   //min==0? min=59:min--;
   }

void fAction002(void)
   {
   //hora==23? hora=0:hora++;
   }

void fAction003(void)
   {
   //hora==0? hora=23:hora--;
   }

////////////////////////////////////////////////////////////////////////////////
// EJECUCION DE ACCION PARA LA FSM                                            //
////////////////////////////////////////////////////////////////////////////////

void runAction(char action)
  {
  switch(action)
    {
    case A000:fAction000();break;
    case A001:fAction001();break;
    case A002:fAction002();break;
    case A003:fAction003();break;
    default:break;
   }
}

char getEvent(void)
// Para determinar el estado en el que me encuentro, en lugar de hacer un
// "switch", lo que hago es un "if" porque el compilador no permite realizar
// esa instrucción con un puntero, y si quiero hacer un "casteo" de la variable
// también tira error.

   {
   char event=TABLE_END;
// Por defecto va a devolver "ningun evento" (= TABLE_END).

  

   return event;
   }

////////////////////////////////////////////////////////////////////////////////
// PARSER                                                                     //
////////////////////////////////////////////////////////////////////////////////

int aux;

t_state *p2tablaDeEstado;
// El establecimiento del estado inicial de "p2tablaDeEstado" es realizado en la
// función "fsmInit".

void fsmParser(void)

   {

   char event;

   event=getEvent();

   while(p2tablaDeEstado->event != TABLE_END &&
         p2tablaDeEstado->event != event)

      {

      p2tablaDeEstado++;

      }

   runAction(p2tablaDeEstado->action);

   p2tablaDeEstado=p2tablaDeEstado->nextState;

   }


void fsmInit(void)
  {
  p2tablaDeEstado=s000;
  }
