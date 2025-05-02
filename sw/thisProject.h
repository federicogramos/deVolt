// thisProject.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __THIS_PROJECT_H
#define __THIS_PROJECT_H

enum e_bufferIx	{
				MORE_DIG,
				MIDS_DIG,
				LESS_DIG,
				ADV,
                CANT_BUFFER_IX};

enum e_advMode	{
				ADV_MOD_OFF,
				ADV_MOD_XEVEX_BLANK_EXTREMOS,
				ADV_MOD_XEVEX,
				ADV_MOD_VEXEV,
				ADV_MOD_XEV,
				ADV_MOD_VEX,
				ADV_MOD_EXEVE,
				ADV_MOD_EVEXE,
                CANT_ADV_MODES};

enum e_estados	{
				E_TEST_DISPLAYS,
				E_IDLE,
				E_MENU_BRILLO,
				E_MENU_ADV_MODE,
				E_MENU_LIMITS,
				E_MENU_ESCALA,
				E_MENU_USER_CAL,
				E_MENU_FACTORY_CAL,
				E_SET_BRILLO,
				E_SET_ESCALA_ENT_DESCRIPTION,
				E_SET_ESCALA_ENT,
				E_SET_ESCALA_DEC_DESCRIPTION,
				E_SET_ESCALA_DEC,
				E_SET_ADV_MODE,
				E_SET_ADV_XLO_DESCRIPTION,
				E_SET_ADV_XLO,
				E_SET_ADV_XUP_DESCRIPTION,
				E_SET_ADV_XUP,
				E_SET_ADV_ELO_DESCRIPTION,
				E_SET_ADV_ELO,
				E_SET_ADV_EUP_DESCRIPTION,
				E_SET_ADV_EUP,
				E_SET_ADV_VLO_DESCRIPTION,
				E_SET_ADV_VLO,
				E_SET_ADV_VUP_DESCRIPTION,
				E_SET_ADV_VUP,
				E_SET_CAL_DESCRIPTION,
				E_SET_0V_OFFSET,
				E_SET_CAL_P0_DESCRIPTION,
				E_SET_CAL_P0,
				E_SET_CAL_P1_DESCRIPTION,
				E_SET_CAL_P1,
				E_SET_CAL_P2_DESCRIPTION,
				E_SET_CAL_P2,
				E_SET_RST_DESCRIPTION,
                CANT_ESTADOS};


extern char state;
extern char brilloMem;

#define ALL_DIGITS_BLANK()		{\
							muxBuffer[0]=' ';\
							muxBuffer[1]=' ';\
							muxBuffer[2]=' ';\
							muxBuffer[3]=' ';\
							}
                          
#endif//__TIMER_DELAYS_H