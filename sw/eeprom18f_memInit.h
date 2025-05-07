//==============================================================================
// Archivo: eeprom18f_memInit.h
// Autor: Federico Ramos
// Modificado: 20250402 0554
//
// Este archivo de inicialización, se pone separadamente fuera de la librería, j
// unto con la invocacion de #include <eeprom18f.h>, porque cuando se pone adent
// ro de la .h, se produce duplicacion de la reserva de memoria por cada vez que
// se invoca la libreria .h en otros archivos, por ejemplo, cuando se la requier
// e en interrupts.c u otro.
//==============================================================================


#ifndef __EEPROM18F_MEM_INIT_H
#define __EEPROM18F_MEM_INIT_H


// Init eeprom =================================================================
// Nota: usa doble espacio en identificadores.
// EEADDR__XX_YY
// XX: orden de arriba a abajo de cada byte EEPROM (address fisico real)
// YY: nro de byte de una variable cuyo sizeof es mayor a 1, ejemplo: int va a t
// ener 00 Y 01.
//==============================================================================

__EEPROM_DATA(
    0x00,// EEADDR_BRILLO_MEM
    0x00,// EEADDR_ADV_MODE_MEM
    0x00,0x00,// EEADDR_XLO_MEM
    0x00,0x00,// EEADDR_XUP_MEM
    0x00,0x00// EEADDR_ELO_MEM
    );

__EEPROM_DATA(
    0x00,0x00,// EEADDR_EUP_MEM
    0x00,0x00,// EEADDR_VLO_MEM
    0x00,0x00,// EEADDR_VUP_MEM
    0x00,0x01// EEADDR_ESC_ENT_MEM
    );

__EEPROM_DATA(
    0x00,0x00,// EEADDR_ESC_DEC_MEM
    0x00,0x00,//
    0x00,0x00,//
    0x00,0x00
    );




#endif // __EEPROM18F_MEM_INIT_H