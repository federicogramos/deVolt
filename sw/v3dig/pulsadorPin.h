////////////////////////////////////////////////////////////////////////////////
// pulsador.h                                                                      //
////////////////////////////////////////////////////////////////////////////////

// CONSTANTES PARA QUE USUARIO SETEE
#define PULS_PIN_CANT 3

// CONSTANTES
//#define PULS_PIN_BUFSIZ 1
#define PULS_PIN_N_ANTIREBOTE 5

// ESTRUCTURAS
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.

typedef struct
  {
  char *p2port;
  unsigned char bitNum:3;
  unsigned char state:1;
  unsigned char prevState:1;
  unsigned char timer:3;
  }t_pulsPin;

// DECLARACIÓN DE FUNCIONES
void pulsPinDriver(void);

extern char pulsPinBuffer;

#define GET_PULS_PIN_STATE(byte) (PUL_ST_MSK & byte)
#define GET_PULS_PIN_ID(byte) (~PUL_ST_MSK & byte)
