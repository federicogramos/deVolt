//******************************************************************************
// ARCHIVO: timer_delays.h
//******************************************************************************


#ifndef __TIMER_DELAYS_H
#define __TIMER_DELAYS_H


//******************************************************************************
// DEFINICION DE TIEMPOS POR PARTE DEL USUARIO
//******************************************************************************
type_timerDelayConstant timerDelayConstant[CANT_TIMERS]=
	{
	40,
	16,
	8,
	1,
	0,
	1,
	0//mem_tZero=000.0[ms] -> LEVANTA EL VALOR DESDE MEMORIA
	};


#endif//__TIMER_DELAYS_H