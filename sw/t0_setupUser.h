//******************************************************************************
// ARCHIVO: timer_user_settings.h
//******************************************************************************


#ifndef __TIMER_USER_SETTINGS_H
#define __TIMER_USER_SETTINGS_H


//******************************************************************************
// ALIAS
typedef unsigned int type_timerSize;//TAMAÑO DE VARIABLE QUE VA A CONTABILIZAR EL TIEMPO: char, int, long (unsigned or not)
typedef type_timerSize type_timerDelayConstant;//SE GENERA UN ARRAY QUE CONTIENE LOS TIEMPOS DE DURACIÓN DE CADA TIMER. SE PUEDE DECLARAR "const" A ESTE TIPO DE DATO, PARA QUE NO OCUPE RAM EN CASO DE NO NECESITAR ALTERAR EL TIEMPO DE LOS TEMPORIZADORES.
//******************************************************************************


#endif//__TIMER_INT_ALIASES_H