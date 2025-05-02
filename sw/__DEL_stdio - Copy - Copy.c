/******************************************************************************/
/* ARCHIVO:     stdio.c                                                       */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/
#include <stdio.h>

#include <string.h>
#include <stdarg.h>


/******************************************************************************/
/* DEFINICI�N DE VARIABLES GLOBALES                                           */
/******************************************************************************/


/******************************************************************************/
/* FUNCI�N:     fputc(char,FILE*)                                             */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  La primera vez que se ejecuta con un archivo reci�n creado,   */
/*              llama a flushBuff() que lo que har� es asignarle al stream un */
/*              buffer en memoria y ponerle adentro el caracter c. Las        */
/*              siguientes invocaciones seguir�n poniendo los caracteres en   */
/*              el buffer, hasta llegar al l�mite del mismo. Llegado ese      */
/*              punto, se vuelve a invocar flushBuff(), que lo que har� es    */
/*              invocar a la funci�n fflush(), para que el contenido del      */
/*              buffer sea pasado a memoria y luego vaciado para continuar    */
/*              poniendo caracteres.                                          */
///corregic comentario teniendo en cuenta la modificaci�n ->
// uno de los defectos que creo que tiene, es que no se puede hacer rewind, y luego escribir,
// porque no tiene manera de saber que se hab�a rebobinando, y entonces cuando se vuelve
// a escribir, si bien escribe en el lugar deseado, el segmento INCREMENTA su cantidad
// de elementos, cosa que es un error, ya que en realidad no se est�n agregando m�s
// caractere, sino que se est�n sobreescribiendo algunos, por lo que la cantidad
// de bytes del segmento NO DEBERIA CAMBIAR

/******************************************************************************/
// con la nueva modificaci�n, al escribir usando fputc, esto no afecta lo que
// se estaba leyendo (es decir que el puntero que se usaba para leer no se mueve
// de lugar).
char fputc(char c,FILE *stream)
  {
  if(stream->nw==0)
    {
    stream->flg|=_EOF;
    return EOF;
    }
  else
    {
    --stream->nw;
    return *((stream->nxw)++)=c;
    }
  }


/******************************************************************************/
/* FUNCI�N:     fgetc(FILE*)                                                  */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:                                                                */
/******************************************************************************/
char fgetc(FILE *stream)
  {
  if(stream->nr==0)
    {
    stream->flg|=_EOF;
    return EOF;
    }
  else
    {
    --(stream->nr);
     return *((stream->nxr)++);
    }
  }
  

void unget(FILE *stream)
  {
  if((stream->nr++)==0) stream->flg&=~_EOF;
  --(stream->nxr);
  }

/******************************************************************************/
/* FUNCI�N:     fseek(FILE *f,int offset,int mode)                            */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  Resetea el flag de _EOF, y posiciona los cursores (de lectura y de escritura) en un lugar    */
/*              arbitrario dentro del archivo.                                */
/*              No hace chequeo de que el flag de _ERR est� apagado.          */
/******************************************************************************/
//creo que para que esto funcione bien, debe resetear la cantidad de elementos contenida en el buffer,
// de manera que en la siguiente lectura/escritura, se vuelva a cargar
//Un problema que a�n no solucion� es el que si se rebobina y se hace fputc(), a�n
// se sigue incrementando el contador del tama�o del archivo, pero en realidad no se est�
// incrementando ya que est� sobreescribiendo.

// Hice una modificaci�n para que mueva �nicamente los punteros en funci�n de
// si el archivo es de lectura, escritura o ambos, cuesti�n de que solo mueva
// aquellos indispensables. Esta modificaci�n fue necesaria porque necesito
// poder rebobinar sin que se me mueva el otro puntero, cosa que anteriormente
// no ten�a manera de hacer.

void fseek(FILE *fp,int offset,int mode)
  {
  fp->flg&=~_EOF; /* Borra el flag de _EOF para que pueda hacer fflush()      */
  if(mode==SEEK_SET)
    {
    if(fp->flg&_READ)
      {
      (fp->nxr)=fp->bas;
      (fp->nr)=fp->bufsiz;
      }
    if(fp->flg&_WRITE)
      {
      (fp->nxw)=fp->bas;
      (fp->nw)=fp->bufsiz;
      }
    }
  else if(mode==SEEK_END)
    {
    if(fp->flg&_READ)
      {
      (fp->nxr)=fp->bas+fp->bufsiz;
      (fp->nw)=0;
      }
    if(fp->flg&_WRITE)
      {
      (fp->nxw)=fp->bas+fp->bufsiz;
      (fp->nw)=0;
      }
    }
  else
    {
    if(fp->flg&_READ)
      {
      (fp->nxr)+=offset; /* Setea el bos en otro lugar respecto del actual   */
      (fp->nw)-=offset;
      }
    if(fp->flg&_WRITE)
      {
      (fp->nxw)+=offset;
      (fp->nw)-=offset;
      }
    }
  }

/******************************************************************************/
/* FUNCI�N:     fprintf()                                                     */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/
//La funcion va arg anda mal porque si uso en un printf 2 argumentos int,
// me devuelve el segundo mal--> Lo hacia porque le mandaba 2 parametros short long int
// en lugar de solamente int.

void fprintf(FILE *fp,char *fmt,...)
  {
  va_list ap;        /* Puntero de argumentos                                 */
  char str[MAX_FPRINTF_INT];      /* m�ximo int de 16 bits, entonces usa 5 char + signo + NULL  */
  char *p,*sval;
  int ival;
  double dval;
  unsigned uval;

  char *v;

  va_start(ap, fmt); /* Se hace que ap apunte al primer argumento sin nombre  */
  for(p=fmt;*p;p++)
    {
    if(*p!='%')
      {
      (void)fputc(*p,fp);
      continue;
      }
    switch(*++p)
      {
      case 'd':
      case 'i':
        ival=va_arg(ap,int);
        v=intToStr(ival,str,MAX_FPRINTF_INT);
        while(*v) fputc(*(v++),fp); /* Copia el string hasta el final     */
        break;
      case 'c':
        ival=va_arg(ap,int);
        (void)fputc((char)ival,fp);
        break;
      case 'u':
        //uval=va_arg(ap,unsigned int);
        //fprintu(uval,fp);
        break;
      case 'e':
        dval=va_arg(ap,double);
        //fprinte(dval,fp);
        break;
      case 'f':
        dval = va_arg(ap, double);
        //fprintflt("%f", dval);
        break;
      case 'g':
        dval = va_arg(ap, double);
        //printf("%g", dval);
        break;
      case 's':
        for(sval=va_arg(ap,char *);*sval;sval++) (void)fputc(*sval,fp);
        break;
      default:
        (void)fputc(*p,fp);
        break;
      }
    }
  va_end(ap);
  }




/******************************************************************************/
/* FUNCI�N:     intToStr()                                                    */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/
char *intToStr(int num,char *str,char strLen)
  {
//  char *strBack=str;
  str+=strLen-1;
  //*str=0;              /* NULL terminated     SAQUE SOLO PARA CRONOMETRO                                */
  if(num<0)
    {
    do *(--str)='0'-(num%10);
    while((num/=10)!=0);
    *(--str)='-';
    }
  else
    {
    do *(--str)='0'+(num%10);
    while((num/=10)!=0);
    }
return str;
  //return strcpy(strBack,str); /* Pasa en limpio el n�mero convertido          */
  }
/******************************************************************************/
/* FIN FUNCI�N:                                                               */
/******************************************************************************/



//num: numero a convertir en string
//str: puntero a array donde voy a escribir la conversion de nro a string
//strLen: cantidad de caracteres que va a escribir (alinea nro a la derecha y
//completa con ceros)
//El string que escribe, no es NULL terminated.
void ucharToStr(unsigned char num,char *str,char strLen)
   {
   char i;

   str+=strLen-1;
   for(i=0;i<strLen;i++)
      {
      *(--str)='0'+(num%10);
      num/=10;
      }
   }


void uintToStr(unsigned int num,char *str,char strLen)
   {
   char i;

   str+=strLen-1;
   for(i=0;i<strLen;i++)
      {
      *(--str)='0'+(num%10);
      num/=10;
      }
   }

