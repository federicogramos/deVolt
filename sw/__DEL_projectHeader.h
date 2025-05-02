////////////////////////////////////////////////////////////////////////////////
// projectHeader.h                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef __PROJECT_HEADER_H
#define __PROJECT_HEADER_H

#include <htc.h>
// Este include va adentro del .h, solo porque es un include que deben tener
// todos los archivos fuente.

////////////////////////////////////////////////////////////////////////////////
// MACROS DE MANEJO DE BITS                                                   //
////////////////////////////////////////////////////////////////////////////////

//#define HIGH_BYTE(x) ((unsigned char)(x>>8))
//#define LOW_BYTE(x) ((unsigned char)(x & 0xFF))

#define GET_NUM_BYTE(n,x) ((unsigned char)(x>>(8*n)))

#define BIT_SET(var,bitno) ((var) |= 1UL << (bitno))
#define BIT_CLR(var,bitno) ((var) &= ~(1UL << (bitno)))

#define BIT_GETVAL(byte,bitno) !(((1UL<<(bitno)) & (byte))==0)
// Retorna 0 o 1.

#define BIT_GETVAL_QUICK(byte,bitno) ((1UL<<(bitno)) & (byte))
// Retorna 0 si el bit es 0, !0 en otro caso.

#define BIT_BY_BIT_BYTE(b7,b6,b5,b4,b3,b2,b1,b0) (         \
                                                 b0*1UL<<0|\
                                                 b1*1UL<<1|\
                                                 b2*1UL<<2|\
                                                 b3*1UL<<3|\
                                                 b4*1UL<<4|\
                                                 b5*1UL<<5|\
                                                 b6*1UL<<6|\
                                                 b7*1UL<<7 \
                                                 )
// Para escribir una constante del tipo byte, pero estableciendo bit por bit.

#define HIGH_NIBBLE(x) ((unsigned char)(x>>4))
#define LOW_NIBBLE(x) ((unsigned char)(x & 0xFF))

////////////////////////////////////////////////////////////////////////////////
// MACROS PARA MANEJO DE EEPROM                                               //
////////////////////////////////////////////////////////////////////////////////

#define EEPROM_WRITE_CHAR(addr,n) {                     \
                                  ee_write_byte(addr,n); \
                                  }
// EEPROM:  +------------+
// Address: |    0x00    |
//          +------------+
// Data:    |    BYTE    |
//          +------------+

#define EEPROM_READ_CHAR(addr,var) {                     \
                                   var=ee_read_byte(addr);\
                                   }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

#define EEPROM_WRITE_INT(addr,n) {                                \
                                 ee_write_byte(addr,HIGH_BYTE(n)); \
                                 ee_write_byte(addr+1,LOW_BYTE(n));\
                                 }
// EEPROM:  +------------+----------+
// Address: |    0x00    |   0x01   |
//          +------------+----------+
// Data:    |  HIGH BYTE | LOW BYTE |
//          +------------+----------+

#define EEPROM_READ_INT(addr,var) {                           \
                                  var=0x00;                   \
                                  var|=ee_read_byte(addr)<<8;  \
                                  var|=ee_read_byte(addr+1)<<0;\
                                  }

// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

#define EEPROM_WRITE_LONG_INT(addr,n) {                                 \
                                 eeprom_write(addr+0,GET_NUM_BYTE(3,n));\
                                 eeprom_write(addr+1,GET_NUM_BYTE(2,n));\
                                 eeprom_write(addr+2,GET_NUM_BYTE(1,n));\
                                 eeprom_write(addr+3,GET_NUM_BYTE(0,n));\
                                 }
// EEPROM:  +------------+----------+------------+----------+
// Address: |    0x00    |   0x01   |    0x02    |   0x03   |
//          +------------+----------+------------+----------+
// Data:    |   BYTE 3   |  BYTE 2  |   BYTE 1   |  BYTE 0  |
//          +------------+----------+------------+----------+

#define EEPROM_READ_LONG_INT(addr,var) {                                \
                                  var=0x0000L;                          \
                                  var|=(long)eeprom_read(addr+0)<<(8*3);\
                                  var|=(long)eeprom_read(addr+1)<<(8*2);\
                                  var|=(long)eeprom_read(addr+2)<<(8*1);\
                                  var|=(long)eeprom_read(addr+3)<<(8*0);\
                                  }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

////////////////////////////////////////////////////////////////////////////////
// MAPA DE MEMORIA DE EEPROM                                                  //
////////////////////////////////////////////////////////////////////////////////

#define EEADDR_BRILLO_MEM 0
#define EEADDR_ADV_MODE_MEM 1
#define EEADDR_XLO_MEM 2
#define EEADDR_XUP_MEM 4
#define EEADDR_ELO_MEM 6
#define EEADDR_EUP_MEM 8
#define EEADDR_VLO_MEM 10
#define EEADDR_VUP_MEM 12
#define EEADDR_ESC_ENT_MEM 14
#define EEADDR_ESC_DEC_MEM 16



#endif
   // __PROJECT_HEADER_H