////////////////////////////////////////////////////////////////////////////////
// pulsador.h                                                                      //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

// CONSTANTES PARA QUE USUARIO SETEE
#define PULS_CANT 4

// CONSTANTES
#define PULS_BUFSIZ 8
#define TIMERS_BIT_LENGTH 4
#define N_ANTIREBOTE 10

#define PUL_DWN 0x0F
#define PUL_UP 0x1F

// ESTRUCTURAS
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.
typedef struct
  {
  char *p2port;
  unsigned char bitNum:1;
  unsigned char state:1;
  unsigned char prevState:1;
  unsigned char inhibit:1;
  unsigned char timer:TIMERS_BIT_LENGTH;
  }t_puls;

// DECLARACIÓN DE FUNCIONES
void pulsDriver(void);
void pulsInterruptDriver(void);

extern FILE pulsFile;