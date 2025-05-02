/******************************************************************************/
/* ARCHIVO:     matricial.h                                                   */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

#ifndef __MATRICIAL_H
#define __MATRICIAL_H

/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/


/******************************************************************************/
/* DEFINICIÓN DE CONSTANTES SETEABLES POR EL USUARIO                          */
/******************************************************************************/

// Cantidad de filas del teclado.
#define FILS      4

// Cantidad de columnas del teclado.
#define COLS      4

// 1: pull-up, 0:pull-down.
#define PULL_TYPE 1

// Cantidad de períodos de muestreo ignorados por el rebote. Un número que de
// 0.15s ó 0.2s está bien.
#define N_REBOTE  0

#define TEC_BUFSIZ 4



typedef struct
{
char f1c1:1;
char f1c2:1;
char f1c3:1;
char f1c4:1;
char f2c1:1;
char f2c2:1;
char f2c3:1;
char f2c4:1;
char f3c1:1;
char f3c2:1;
char f3c3:1;
char f3c4:1;
char f4c1:1;
char f4c2:1;
char f4c3:1;
char f4c4:1;
}t_bit_tec;

typedef struct
{
char f1c1:4;
char f1c2:4;
char f1c3:4;
char f1c4:4;
char f2c1:4;
char f2c2:4;
char f2c3:4;
char f2c4:4;
char f3c1:4;
char f3c2:4;
char f3c3:4;
char f3c4:4;
char f4c1:4;
char f4c2:4;
char f4c3:4;
char f4c4:4;
}t_4bit_tec;

/******************************************************************************/
/* DECLARACIÓN DE VARIABLES EXTERNAS SETEADAS POR EL USUARIO                  */
/******************************************************************************/


//extern PORT tecFil;
//extern PORT tecCol;
//extern PORT tecFilDDR;
//extern PORT tecColDDR;
//extern PORT tecColPullPol;
//extern PORT tecColPullEn;

/******************************************************************************/
/* DECLARACIÓN DE FUNCIONES                                                   */
/******************************************************************************/

void initMatricial(void);
void procesarBoton(char i,char j);
void analizarBoton(char i,char j);
void driverTeclado(void);
int kbhit(void);

char getTec(char i,char j);
void putTec(char i,char j,char val);

char getMed(char i,char j);
void putMed(char i,char j,char val);

char getMinc(char i,char j);
void putMinc(char i,char j,char val);

char tec2ascii(char i,char j);

// Change code section to DEFAULT.
//#pragma CODE_SEG DEFAULT

// __MATRICIAL_H
#endif
