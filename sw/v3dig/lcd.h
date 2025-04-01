////////////////////////////////////////////////////////////////////////////////
// lcd.h                                                                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef __LCD_H
#define __LCD_H

#include <stdio.h>

// Debe ser colocada debajo de <osystem.h> por requerir FILENAME_MAX

////////////////////////////////////////////////////////////////////////////////
// CONSTANTES                                                                 //
////////////////////////////////////////////////////////////////////////////////

#define LCD_LINES 2
#define LCD_LENGTH 16
#define LCD_BUFSIZ (LCD_LINES*LCD_LENGTH+1)

#define NIBBLE_SEND_INSTR 0
#define NIBBLE_SEND_DATA 1

////////////////////////////////////////////////////////////////////////////////
// DECLARACIÓN DE FUNCIONES                                                   //
////////////////////////////////////////////////////////////////////////////////

void lcdFsmInit(void);

void lcdFsmParser(void);

void lcdNibbleSend(char mode,char command);

/////////////////////////////////////////////////////////////////////////
// DEFINICIONES ENUM PARA FSM                                          //
/////////////////////////////////////////////////////////////////////////

enum e_lcdEvent{LCD_NO_EVENT,ALWAYS,UNFINISHED,TIMEOUT_30MS,REFRESH_FINISHED,
             FIRST_LINE_FINISHED,LCD_TABLE_END};
// No event se usa por defecto para enviar a la fsm, en el caso de que no ocurra
// nada. Dado que NO_EVENT es distinto a cualquier otro evento que pueda
// ocurrir en cualquier circunstancia, indefectiblemente la fsm llegará a
// TABLE_END y ejecutará esa acción, es decir, justo lo que se quería hacer.

enum e_lcdAction{LCD_A000,LCD_A001,LCD_A002,LCD_A003,LCD_A004,LCD_A005,
                 LCD_A006,LCD_A007,LCD_A008,
                 LCD_DO_NOTHING};

#define SET_DATA_LENGTH LCD_A000
#define CLEAR_DISPLAY LCD_A001
#define SET_ENTRY_MODE LCD_A002
#define SET_VISIBILITY LCD_A003
#define REWIND LCD_A004
#define SEND_CHARACTER LCD_A005
#define LCD_INIT_TMR_30MS LCD_A006
#define START_LCD_SECOND_LINE LCD_A007

/******************************************************************************/
/* DEFINICIÓN DE CONSTANTES                                                   */
/******************************************************************************/
#define LCD_CMD_FUNCTION 0x20 /* Comando functionSet (con las opciones=0)     */
#define LCD_CMD_VIS      0x08 /* Comando displayControl (con las opciones=0)  */
#define LCD_CMD_ENTRYM   0x04 /* Comando entryModeSet (con las opciones=0)    */
#define LCD_CMD_CLRDISP  0x01 /* Comando clearDisplay                         */
#define LCD_CMD_RETHOME  0x02 /* Comando returnHome                           */
#define LCD_CMD_SETDDRAM 0x80 /* Comando para establecer address de la DDRAM  */
#define LCD_8B_IF        0x10 /* Opción de functionSet: 8 bit interface       */
#define LCD_4B_IF        0x00 /* Opción de functionSet: 4 bit interface       */
#define LCD_2_DL         0x08 /* Opción de functionSet: 2 display lines       */
#define LCD_1_DL         0x00 /* Opción de functionSet: 1 line display        */
#define LCD_5X10D        0x04 /* Opción de functionSet: 5x10 dot font         */
#define LCD_5X8D         0x00 /* Opción de functionSet: 5x8 dot font          */

/////////////////////////////////////////////////////////////////////////
// DEFINICION ESTRUCTURAS                                              //
/////////////////////////////////////////////////////////////////////////

struct t_lcdTransition
   {
   char event;
   const struct t_lcdTransition *nextState;
   char action;
   };

typedef struct t_lcdTransition t_lcdState;

typedef struct
  {
  unsigned dispVis:1;                   /* Seteo Visibility: displayVisibility                      */
  unsigned curVis:1;                   /* Seteo Visibility: cursorVisibility                       */
  unsigned blink:1;                   /* Seteo Visibility: positionBlinking                       */
  unsigned incDec:1;                   /* Seteo Entry Mode: displayShifts                          */
  unsigned shift:1;                   /* Seteo Entry Mode: displayShifts                          */
  unsigned bkLight:1;                   /* Seteo Backlight*/

  unsigned dispVis_rsh:1;                   /* Seteo: displayVisibility                      */
  unsigned curVis_rsh:1;                   /* Seteo: cursorVisibility                       */
  unsigned blink_rsh:1;                   /* Seteo: positionBlinking                       */
  unsigned incDec_rsh:1;                   /* Seteo: displayShifts                          */
  unsigned shift_rsh:1;                   /* Seteo: displayShifts                          */
  unsigned bkLight_rsh:1;
  
  } t_lcdSettings;



/////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATION OF STATES (modificar para cada caso)            //
//                                                                     //
// Hay estados en la tabla de estados, que son referenciados antes de  //
// que los mismos sean definidos. Es por eso que antes de la creacion  //
// de la tabla de estados, se deben declarar todos los estados         //
// existentes.                                                         //
/////////////////////////////////////////////////////////////////////////

extern const t_lcdState lcdWaitToSetDataLength[];
extern const t_lcdState lcdWaitToClearDisplay[];
extern const t_lcdState lcdWaitToSetEntryMode[];
extern const t_lcdState lcdWaitToSetVisibility[];
extern const t_lcdState lcdWaitForRefresh[];
extern const t_lcdState lcdCommandFirstLine[];
extern const t_lcdState lcdCommandSecondLine[];

extern const t_lcdState *p2tablaDeEstadoLcd;



extern t_lcdSettings lcdSettings;

////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////

#define LCD_DATA_LINES(byte) (PORTC=(PORTC&0x0F)|(byte<<4))

#define LCD_SEND_COMMAND(comm) {                                          \
                               lcdNibbleSend(NIBBLE_SEND_INSTR,(comm)>>4);\
                               lcdNibbleSend(NIBBLE_SEND_INSTR,(comm)>>0);\
                               }

#define LCD_SEND_DATA(data) {                                          \
                               lcdNibbleSend(NIBBLE_SEND_DATA,(data)>>4);\
                               lcdNibbleSend(NIBBLE_SEND_DATA,(data)>>0);\
                               }

#define LCD_SET_DDRAM_ADDR(addr) LCD_SEND_COMMAND(LCD_CMD_SETDDRAM|addr)



#define DISP_VIS_ON() { \
                        lcdSettings.dispVis=1;\
                        lcdSettings.dispVis_rsh=1;\
                       }
//#define lcdSettings.curVis                   /* Seteo Visibility: cursorVisibility                       */
//#define lcdSettings.blink                   /* Seteo Visibility: positionBlinking                       */
//#define lcdSettings.incDec                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.shift                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.bkLight                   /* Seteo Backlight*/

//#define DISP_VIS_OFF() lcdSettings.dispVis=0                   /* Seteo Visibility: displayVisibility                      */
//#define lcdSettings.curVis                   /* Seteo Visibility: cursorVisibility                       */
//#define lcdSettings.blink                   /* Seteo Visibility: positionBlinking                       */
//#define lcdSettings.incDec                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.shift                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.bkLight                   /* Seteo Backlight*/
  


extern char lcdBuffer[LCD_BUFSIZ];
extern FILE lcdFile;

#endif
// __LCD_H