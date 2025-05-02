////////////////////////////////////////////////////////////////////////////////
// fsm.h                                                                      //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// DECLARACIÓN DE FUNCIONES                                                   //
////////////////////////////////////////////////////////////////////////////////

void fsmInit(void);

void fsmParser(void);

/////////////////////////////////////////////////////////////////////////
// DEFINICIONES ENUM PARA FSM                                          //
/////////////////////////////////////////////////////////////////////////

enum e_event{SET_PRESSED,INC_PRESSED,
             DEC_PRESSED,TABLE_END};
// No event se usa por defecto para enviar a la fsm, en el caso de que no ocurra
// nada. Dado que NO_EVENT es distinto a cualquier otro evento que pueda
// ocurrir en cualquier circunstancia, indefectiblemente la fsm llegará a
// TABLE_END y ejecutará esa acción, es decir, justo lo que se quería hacer.

enum e_action{A000,A001,A002,A003,DO_NOTHING};

#define INC_MIN A000
#define DEC_MIN A001
#define INC_HORA A002
#define DEC_HORA A003

/////////////////////////////////////////////////////////////////////////
// DEFINICION ESTRUCTURAS                                              //
/////////////////////////////////////////////////////////////////////////

struct t_transition
   {
   int event;
   struct t_transition *nextState;
   int action;
   };

typedef struct t_transition t_state;

/////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATION OF STATES (modificar para cada caso)            //
//                                                                     //
// Hay estados en la tabla de estados, que son referenciados antes de  //
// que los mismos sean definidos. Es por eso que antes de la creacion  //
// de la tabla de estados, se deben declarar todos los estados         //
// existentes.                                                         //
/////////////////////////////////////////////////////////////////////////

extern t_state s000[];
extern t_state s001[];
extern t_state s002[];

extern t_state *p2tablaDeEstado;
