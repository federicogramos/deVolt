/******************************************************************************/
/* ARCHIVO:     stdio.h                                                       */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


//#ifndef __STDIO_H
//#define __STDIO_H


/******************************************************************************/
/* DEFINICIÓN DE CONSTANTES                                                   */
/******************************************************************************/
#define _FFULL    (1<<0)      /* Notifica error: trató de meter datos en un   */
                              /* archivo que alcanzó su capacidad máxima      */
#define _FEMPTY   (1<<1)      /* Notifica error: intentó extraer datos de un  */
                              /* archivo vacío                                */
#define _FERR     (1<<2)      /* Notifica error: error                        */

#define SEEK_END  0           /* Modo para la función fseek()                 */
#define SEEK_CUR  1           /* Modo para la función fseek()                 */
#define SEEK_SET  2           /* Modo para la función fseek()                 */

#define EOF       (-1)
#define NULL      0

#define _READ     (1<<0)      /* FILE flag: archivo abierto para lectura      */
#define _WRITE    (1<<1)      /* FILE flag: archivo abierto para escritura    */
#define _UNBUF    (1<<2)      /* FILE flag: archivo sin buffer                */
#define _EOF      (1<<3)      /* FILE flag: ocurrió fin de archivo (EOF)      */
#define _ERR      (1<<4)      /* FILE flag: ocurrió un error en este archivo  */

#define MAX_FPRINTF_INT 7 //16bit: 5char + signo + NULL

/******************************************************************************/
/* ESTRUCTURA:  FILE                                                          */
/* DESCRIPCIÓN: Contiene variables que se necesitan para implementar una      */
/*              cola, y otras variables accesorias.                           */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/
typedef struct
  {
  char flg;  /* Modo de acceso al archivo                                     */
  char *nxr; /* Address donde escribiré del buffer                            */
  char *nxw; /* Address que leeré del buffer                                  */
  char *bas; /* Apunta al primer byte de la memoria reservada para buffer     */
  char nr;    /* Cantidad de bytes que existen para leer en el buffer          */
  char nw;    /* Cantidad de bytes que restan para escribir en el buffer       */
  char bufsiz;
  }FILE;


/******************************************************************************/
/* DECLARACIÓN DE VARIABLES EXTERNAS                                          */
/******************************************************************************/


/******************************************************************************/
/* DECLARACIÓN DE FUNCIONES                                                   */
/******************************************************************************/
char fputc(char c, FILE *stream);
char fgetc(FILE *stream);
void fseek(FILE *fp,int offset,int mode);
void unget(FILE *stream);

//char ferror(FILE *stream);
//char feof(FILE *stream);

void fprintf(FILE *fp,char *fmt,...);
void fprinti(FILE *fp,char *str);

char *intToStr(int num,char *str,char strLen);
void ucharToStr(unsigned char num,char *str,char strLen);
void uintToStr(unsigned int num,char *str,char strLen);

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

#define rewind(fp) fseek(fp,0,SEEK_SET)

//#define getchar()  fgetc(stdin)
//#define putchar(c) fputc((c),stdout)




//#endif /* __STDIO_H                                                           */