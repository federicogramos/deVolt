// segments.c

#include <projectHeader.h>
#include <segments.h>
#include <system.h>
#include <stdio.h>

char muxBuffer[MUX_BUFSIZ]={' ',' ',' ',' ',0};//Null terminated

FILE muxFile={
              _READ|_WRITE,
              &muxBuffer,
              &muxBuffer,
              &muxBuffer,
              MUX_BUFSIZ,
              MUX_BUFSIZ,
              MUX_BUFSIZ
              };

t_7seg segments;

void char2pins(char c)
   {
   switch(c)
      {
      case '0':
               SEGA=1;
               SEGB=1;
               SEGC=1;
               SEGD=1;
               SEGE=1;
               SEGF=1;
               SEGG=0;
               break;
      case '1':
               SEGA=0;
               SEGB=1;
               SEGC=1;
               SEGD=0;
               SEGE=0;
               SEGF=0;
               SEGG=0;
               break;
      case '2':
               SEGA=1;
               SEGB=1;
               SEGC=0;
               SEGD=1;
               SEGE=1;
               SEGF=0;
               SEGG=1;
               break;
      case '3':
               SEGA=1;
               SEGB=1;
               SEGC=1;
               SEGD=1;
               SEGE=0;
               SEGF=0;
               SEGG=1;
               break;
      case '4':
               SEGA=0;
               SEGB=1;
               SEGC=1;
               SEGD=0;
               SEGE=0;
               SEGF=1;
               SEGG=1;
               break;
      case '5':
               SEGA=1;
               SEGB=0;
               SEGC=1;
               SEGD=1;
               SEGE=0;
               SEGF=1;
               SEGG=1;
               break;
      case '6':
               SEGA=1;
               SEGB=0;
               SEGC=1;
               SEGD=1;
               SEGE=1;
               SEGF=1;
               SEGG=1;
               break;
      case '7':
               SEGA=1;
               SEGB=1;
               SEGC=1;
               SEGD=0;
               SEGE=0;
               SEGF=1;
               SEGG=0;
               break;
      case '8':
               SEGA=1;
               SEGB=1;
               SEGC=1;
               SEGD=1;
               SEGE=1;
               SEGF=1;
               SEGG=1;
               break;
      case '9':
               SEGA=1;
               SEGB=1;
               SEGC=1;
               SEGD=1;
               SEGE=0;
               SEGF=1;
               SEGG=1;
               break;
      case 'x':
               SEGA=0;
               SEGB=0;
               SEGC=0;
               SEGD=1;
               SEGE=0;
               SEGF=0;
               SEGG=0;
               break;
      case 'v':
               SEGA=0;
               SEGB=0;
               SEGC=0;
               SEGD=0;
               SEGE=0;
               SEGF=0;
               SEGG=0;
               DP=1;
               break;
      case '!':
               SEGA=0;
               SEGB=0;
               SEGC=1;
               SEGD=0;
               SEGE=0;
               SEGF=0;
               SEGG=0;
               break;


      case 'A':SEGA=1;SEGB=1;SEGC=1;SEGD=0;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'b':SEGA=0;SEGB=0;SEGC=1;SEGD=1;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'C':SEGA=1;SEGB=0;SEGC=0;SEGD=1;
               SEGE=1;SEGF=1;SEGG=0;
               break;
      case 'c':SEGA=0;SEGB=0;SEGC=0;SEGD=1;
               SEGE=1;SEGF=0;SEGG=1;
               break;
      case 'd':SEGA=0;SEGB=1;SEGC=1;SEGD=1;
				SEGE=1;SEGF=0;SEGG=1;break;
      case 'E':SEGA=1;SEGB=0;SEGC=0;SEGD=1;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'e':SEGA=1;SEGB=1;SEGC=0;SEGD=1;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'F':SEGA=1;SEGB=0;SEGC=0;SEGD=0;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'H':SEGA=0;SEGB=1;SEGC=1;SEGD=0;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'i':SEGA=0;SEGB=0;SEGC=1;SEGD=0;
               SEGE=0;SEGF=0;SEGG=0;
               break;
      case 'L':SEGA=0;SEGB=0;SEGC=0;SEGD=1;
               SEGE=1;SEGF=1;SEGG=0;
               break;
      case 'n':SEGA=0;SEGB=0;SEGC=1;SEGD=0;
               SEGE=1;SEGF=0;SEGG=1;
               break;
      case 'o':SEGA=0;SEGB=0;SEGC=1;SEGD=1;
               SEGE=1;SEGF=0;SEGG=1;
               break;
      case 'P':SEGA=1;SEGB=1;SEGC=0;SEGD=0;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'r':SEGA=0;SEGB=0;SEGC=0;SEGD=0;
               SEGE=1;SEGF=0;SEGG=1;
               break;
      case 'S':SEGA=1;SEGB=0;SEGC=1;SEGD=1;
               SEGE=0;SEGF=1;SEGG=1;
               break;
      case 't':SEGA=0;SEGB=0;SEGC=0;SEGD=1;
               SEGE=1;SEGF=1;SEGG=1;
               break;
      case 'u':SEGA=0;SEGB=0;SEGC=1;SEGD=1;
               SEGE=1;SEGF=0;SEGG=0;
               break;
      case 'y':SEGA=0;SEGB=1;SEGC=1;SEGD=1;
               SEGE=0;SEGF=1;SEGG=1;
               break;
      case '-':SEGA=0;SEGB=0;SEGC=0;SEGD=0;
               SEGE=0;SEGF=0;SEGG=1;
               break;


      case ' ':
      default:
               SEGA=0;
               SEGB=0;
               SEGC=0;
               SEGD=0;
               SEGE=0;
               SEGF=0;
               SEGG=0;
               DP=0;
      }
   }
