//==============================================================================
// Archivo: /deVolt/sw/v3dig/main.c
// Autor: Federico Ramos
// Modificado: 20250401 1748
//==============================================================================


//==============================================================================
// Headers
//==============================================================================

#include <projectHeader.h>
#include <thisProject.h>
#include <main.h>// Fuses y otras cosas.
#include <system.h>// Inicializaci�n del sistema.
#include <segments.h>
#include <timer_lib.h>
#include <mainDefinitions.h>
#include <adc.h>
#include <iir.h>
#include "stdio.h"

#include <pulsadorPin_lib_1ms.h>
//#include <kPin.h>;;


__EEPROM_DATA	(
				0x00,//EEADDR_BRILLO_MEM
				0x00,//EEADDR_ADV_MODE_MEM
				0x00,0x00,//EEADDR_XLO_MEM
				0x00,0x00,//EEADDR_XUP_MEM
				0x00,0x00//EEADDR_ELO_MEM
				);
__EEPROM_DATA	(
				0x00,0x00,//EEADDR_EUP_MEM
				0x00,0x00,//EEADDR_VLO_MEM
				0x00,0x00,//EEADDR_VUP_MEM
				0x00,0x01//EEADDR_ESC_ENT_MEM
				);
__EEPROM_DATA	(
				0x00,0x00,//EEADDR_ESC_DEC_MEM
				0x00,0x00,//
				0x00,0x00,//
				0x00,0x00
				);

void ee_write_byte(unsigned char address, unsigned char _data)
	{
	EEDATA = _data;
	EEADR = address;
	// start write sequence as described in datasheet, page 91
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1; // enable writes to data EEPROM
	INTCONbits.GIE = 0;  // disable interrupts
	EECON2 = 0x55;
	EECON2 = 0x0AA;
	EECON1bits.WR = 1;   // start writing
	while(EECON1bits.WR) asm("nop");
	//if(EECON1bits.WRERR) printf("ERROR: writing to EEPROM failed!n");
	EECON1bits.WREN = 0;
	INTCONbits.GIE = 1;  // enable interrupts
	}



unsigned char ee_read_byte(unsigned char address)
	{
	EEADR = address;
	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	return EEDATA;
	}


unsigned int measurement,display;

int escEntMem,escDecMem;
float escala,medicionFloat;

int xLoMem,xUpMem,eLoMem,eUpMem,vLoMem,vUpMem;
char brilloMem,advModeMem;
char state;
char ignoreNextFp,setInc=1;

void enterMenu(void)
	{
	if(state==E_MENU_BRILLO) state=E_SET_BRILLO;
	else if(state==E_MENU_ADV_MODE) state=E_SET_ADV_MODE;
	else if(state==E_MENU_LIMITS)
		{
		setInc=1;
		state=E_SET_ADV_XLO_DESCRIPTION;
		}
	else if(state==E_MENU_ESCALA)
		{
		setInc=1;
		state=E_SET_ESCALA_ENT_DESCRIPTION;
		}
	else if(state==E_MENU_USER_CAL) state=E_SET_CAL_DESCRIPTION;
	else if(state==E_MENU_FACTORY_CAL) state=E_SET_RST_DESCRIPTION;
	}
void incVar(void)
	{
	//int aux;
	//short long pulseLimitAux;

	if(state==E_SET_BRILLO)
		{
		if(brilloMem<4)
			{
			brilloMem++;
			EEPROM_WRITE_CHAR(EEADDR_BRILLO_MEM,brilloMem);
			}
		}
	if(state==E_SET_ESCALA_ENT)
		{
		if((escEntMem+setInc)<=999)
			{
			escEntMem=escEntMem+setInc;
			EEPROM_WRITE_INT(EEADDR_ESC_ENT_MEM,escEntMem);
			escala=(float)escEntMem+(float)escDecMem/1000.0;
			}
		}
	if(state==E_SET_ESCALA_DEC)
		{
		if((escDecMem+setInc)<=999)
			{
			escDecMem=escDecMem+setInc;
			EEPROM_WRITE_INT(EEADDR_ESC_DEC_MEM,escDecMem);
			escala=(float)escEntMem+(float)escDecMem/1000.0;
			}
		}
	if(state==E_SET_ADV_MODE)
		{
		if(advModeMem<CANT_ADV_MODES-1)
			{
			advModeMem++;
			EEPROM_WRITE_CHAR(EEADDR_ADV_MODE_MEM,advModeMem);
			}
		}
	if(state==E_SET_ADV_XLO)
		{
		if((xLoMem+setInc)<=999)
			{
			xLoMem=xLoMem+setInc;
			EEPROM_WRITE_INT(EEADDR_XLO_MEM,xLoMem);
			}
		}
	if(state==E_SET_ADV_XUP)
		{
		if((xUpMem+setInc)<=999)
			{
			xUpMem=xUpMem+setInc;
			EEPROM_WRITE_INT(EEADDR_XUP_MEM,xUpMem);
			}
		}
	if(state==E_SET_ADV_ELO)
		{
		if((eLoMem+setInc)<=999)
			{
			eLoMem=eLoMem+setInc;
			EEPROM_WRITE_INT(EEADDR_ELO_MEM,eLoMem);
			}
		}
	if(state==E_SET_ADV_EUP)
		{
		if((eUpMem+setInc)<=999)
			{
			eUpMem=eUpMem+setInc;
			EEPROM_WRITE_INT(EEADDR_EUP_MEM,eUpMem);
			}
		}
	if(state==E_SET_ADV_VLO)
		{
		if((vLoMem+setInc)<=999)
			{
			vLoMem=vLoMem+setInc;
			EEPROM_WRITE_INT(EEADDR_VLO_MEM,vLoMem);
			}
		}
	if(state==E_SET_ADV_VUP)
		{
		if((vUpMem+setInc)<=999)
			{
			vUpMem=vUpMem+setInc;
			EEPROM_WRITE_INT(EEADDR_VUP_MEM,vUpMem);
			}
		}

	TMR_START(TMR_SHOW_SETTING);
	TMR_START(TMR_SHOW_SETTING_ON);
	}

void decVar(void)
	{
	//int aux;
	//short long pulseLimitAux;

	if(state==E_SET_BRILLO)
		{
		if(brilloMem>0)
			{
			brilloMem--;
			EEPROM_WRITE_CHAR(EEADDR_BRILLO_MEM,brilloMem);
			}
		}
	if(state==E_SET_ESCALA_ENT)
		{
		if((escEntMem-setInc)>=0)
			{
			escEntMem=escEntMem-setInc;
			EEPROM_WRITE_INT(EEADDR_ESC_ENT_MEM,escEntMem);
			escala=(float)escEntMem+(float)escDecMem/1000.0;
			}
		}
	if(state==E_SET_ESCALA_DEC)
		{
		if((escDecMem-setInc)>=0)
			{
			escDecMem=escDecMem-setInc;
			EEPROM_WRITE_INT(EEADDR_ESC_DEC_MEM,escDecMem);
			escala=(float)escEntMem+(float)escDecMem/1000.0;
			}
		}
	if(state==E_SET_ADV_MODE)
		{
		if(advModeMem>0)
			{
			advModeMem--;
			EEPROM_WRITE_CHAR(EEADDR_ADV_MODE_MEM,advModeMem);
			}
		}
	if(state==E_SET_ADV_XLO)
		{
		if((xLoMem-setInc)>=0)
			{
			xLoMem=xLoMem-setInc;
			EEPROM_WRITE_INT(EEADDR_XLO_MEM,xLoMem);
			}
		}
	if(state==E_SET_ADV_XUP)
		{
		if((xUpMem-setInc)>=0)
			{
			xUpMem=xUpMem-setInc;
			EEPROM_WRITE_INT(EEADDR_XUP_MEM,xUpMem);
			}
		}
	if(state==E_SET_ADV_ELO)
		{
		if((eLoMem-setInc)>=0)
			{
			eLoMem=eLoMem-setInc;
			EEPROM_WRITE_INT(EEADDR_ELO_MEM,eLoMem);
			}
		}
	if(state==E_SET_ADV_EUP)
		{
		if((eUpMem-setInc)>=0)
			{
			eUpMem=eUpMem-setInc;
			EEPROM_WRITE_INT(EEADDR_EUP_MEM,eUpMem);
			}
		}
	if(state==E_SET_ADV_VLO)
		{
		if((vLoMem-setInc)>=0)
			{
			vLoMem=vLoMem-setInc;
			EEPROM_WRITE_INT(EEADDR_VLO_MEM,vLoMem);
			}
		}
	if(state==E_SET_ADV_VUP)
		{
		if((vUpMem-setInc)>=0)
			{
			vUpMem=vUpMem-setInc;
			EEPROM_WRITE_INT(EEADDR_VUP_MEM,vUpMem);
			}
		}

	TMR_START(TMR_SHOW_SETTING);
	TMR_START(TMR_SHOW_SETTING_ON);
	}

void endTestDisplayActions(void)
	{
	state=E_IDLE;
   
	BUZZER=0;
	muxBuffer[0]='0';
	muxBuffer[1]='0';
	muxBuffer[2]='0';
	muxBuffer[ADV]=' ';
	TMR_INIT_LOOP(TMR_ADCSAMPLE);
	}

void actionsTimeoutShowSetting(void)
	{
	if(TMR_TIMEOUT(TMR_SHOW_SETTING))
		{
		switch(state)
			{
			case E_SET_ESCALA_ENT_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ESCALA_ENT:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ESCALA_DEC_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ESCALA_DEC:
				state=E_IDLE;
				break;
			case E_SET_ADV_XLO_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_XLO:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_XUP_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_XUP:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_ELO_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_ELO:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_EUP_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_EUP:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_VLO_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_VLO_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_VLO:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_VUP_DESCRIPTION:
				state++;
				TMR_START(TMR_SHOW_SETTING);
				break;
			case E_SET_ADV_VUP:
				state=E_IDLE;
				break;
			default:
				state=E_IDLE;
				break;
			}
		}
	}


char aux;

//==============================================================================
// Punto de entrada.
//==============================================================================

void main(void)
	{
	pulsPinInit();//hago seteo de variables antes de que habilite interrupciones.
	systemInit();
	segments.portState=0x01;//uso este auxiliar en lugar de directamente el puerto, para poder "saltear" el encendido de un digito sin alterar el ciclo de multiplexado

	EEPROM_READ_CHAR(EEADDR_BRILLO_MEM,brilloMem);
	EEPROM_READ_CHAR(EEADDR_ADV_MODE_MEM,advModeMem);

	EEPROM_READ_INT(EEADDR_ESC_ENT_MEM,escEntMem);
	EEPROM_READ_INT(EEADDR_ESC_DEC_MEM,escDecMem);
	escala=(float)escEntMem+(float)escDecMem/1000.0;

	EEPROM_READ_INT(EEADDR_XLO_MEM,xLoMem);
	EEPROM_READ_INT(EEADDR_XUP_MEM,xUpMem);
	EEPROM_READ_INT(EEADDR_ELO_MEM,eLoMem);
	EEPROM_READ_INT(EEADDR_EUP_MEM,eUpMem);
	EEPROM_READ_INT(EEADDR_VLO_MEM,vLoMem);
	EEPROM_READ_INT(EEADDR_VUP_MEM,vUpMem);

	BUZZER=1;
	muxBuffer[0]='8';
	muxBuffer[1]='8';
	muxBuffer[2]='8';
	muxBuffer[ADV]='x';

	TMR_INIT_LOOP(TMR_250MS);

	//FGR: NECESARIOS PARA ESTADO TEST_DISPLAYS
	TMR_START(TMR_TEST_DISPLAYS);
	TMR_START(TMR_TEST_ADVERTENCIA);

	while(1)
		{
		if(TMR_TIMEOUT(TMR_250MS))
			{
			timerDriver(TMR_LONG_PULS_UP);
			timerDriver(TMR_LONG_PULS_DWN);
			timerDriver(TMR_TEST_DISPLAYS);
			timerDriver(TMR_TEST_ADVERTENCIA);
			timerDriver(TMR_SHOW_MENU);
			timerDriver(TMR_SHOW_SETTING);
			timerDriver(TMR_SHOW_SETTING_OFF);
			timerDriver(TMR_SHOW_SETTING_ON);
			timerDriver(TMR_SHOW_DESCRIPTION);
			timerDriver(TMR_SPACE);
			}

		if(TMR_TIMEOUT(TMR_SHOW_MENU)) state=E_IDLE;

		//FGR: ALGUNAS TRANSICIONES DE ESTADO
		actionsTimeoutShowSetting();

		if(TMR_TIMEOUT(TMR_LONG_PULS_UP))
			{
			TMR_STOP(TMR_SHOW_MENU);
			BUZZER=1;
			TMR_START(TMR_BEEP);
			TMR_START(TMR_SHOW_SETTING);
			TMR_START(TMR_SHOW_SETTING_ON);
			enterMenu();
			ignoreNextFp=1;//FGR: SOLO PARA QUE CUENDO SE PULSA LARGO, ACEPTE LA PULSACION PERO NO GENERE AL SOLTAR OTRA PULSACION CORTA
			if( state==E_SET_ADV_XLO || state==E_SET_ADV_XUP
				|| state==E_SET_ADV_ELO || state==E_SET_ADV_EUP
				|| state==E_SET_ADV_VLO || state==E_SET_ADV_VUP
				|| state==E_SET_ESCALA_ENT || state==E_SET_ESCALA_DEC)
				switch(setInc)
					{
					case 1: setInc=10; break;
					case 10: setInc=100; break;
					case 100: setInc=1; break;
					}
			}

		if(TMR_TIMEOUT(TMR_LONG_PULS_DWN))
			{
			TMR_STOP(TMR_SHOW_MENU);
			BUZZER=1;
			TMR_START(TMR_BEEP);
			TMR_START(TMR_SHOW_SETTING);
			TMR_START(TMR_SHOW_SETTING_ON);
			enterMenu();
			ignoreNextFp=1;//FGR: SOLO PARA QUE CUENDO SE PULSA LARGO, ACEPTE LA PULSACION PERO NO GENERE AL SOLTAR OTRA PULSACION CORTA
			if( state==E_SET_ADV_XLO || state==E_SET_ADV_XUP
				|| state==E_SET_ADV_ELO || state==E_SET_ADV_EUP
				|| state==E_SET_ADV_VLO || state==E_SET_ADV_VUP
				|| state==E_SET_ESCALA_ENT || state==E_SET_ESCALA_DEC)
				switch(setInc)
					{
					case 1: setInc=100; break;
					case 10: setInc=1; break;
					case 100: setInc=10; break;
					}
			}


//BOOTEO, SELECCION DE SETEOS Y CONFIGURACION
		if(state==E_TEST_DISPLAYS)
			{
			if(TMR_TIMEOUT(TMR_TEST_ADVERTENCIA))
				{
				TMR_START(TMR_TEST_ADVERTENCIA);
				if(muxBuffer[ADV]=='x') muxBuffer[ADV]='!';
				else if(muxBuffer[ADV]=='!') muxBuffer[ADV]='v';
				}
			if(TMR_TIMEOUT(TMR_TEST_DISPLAYS)) endTestDisplayActions();
			}
		else if(state==E_IDLE)
			{
			adcDriver();
			if(TMR_TIMEOUT(TMR_ADCSAMPLE)) ADC_START(ADC_VIN);
			if(ADC_NEW_RESULT(ADC_VIN))
				{
//FGR: ANTES IIR DEVOLVIA INT PORQUE LO CASTEABA, AHORA PUSE QUE RETORNE FLOAT Y LO CASTEO POSTERIORMENTE LUEGO DE "ESCALAR" CON EL AJUSTE DE USUARIO
				//con -22 de offset daba 0.1 en cero volts vin
				medicionFloat=iir((getConv()-21.8)/2.327);//LINEARIZACION
				medicionFloat=medicionFloat*escala;

				measurement=medicionFloat;

				//measurement=iir((getConv()-22)/0.929);//LINEARIZACION
				//measurement=iir(getConv());//CALIBRACION
				if(measurement>999) measurement=999;
				uintToStr(measurement,&muxBuffer[0],3);

				switch(advModeMem)
					{
					case ADV_MOD_OFF: muxBuffer[3]=' '; break;
					case ADV_MOD_XEVEX_BLANK_EXTREMOS:
						if(measurement<=xLoMem || measurement>=xUpMem) muxBuffer[3]='-';
						else if(measurement>xLoMem && measurement < eLoMem
							|| measurement>eUpMem && measurement<xUpMem) muxBuffer[3]='x';
						else if(measurement>eLoMem && measurement < vLoMem
							|| measurement>vUpMem && measurement<eUpMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem && measurement<=vUpMem) muxBuffer[3]='v';
 						break;
					case ADV_MOD_XEVEX:
						if(measurement<=xLoMem || measurement>=xUpMem) muxBuffer[3]='x';
						else if(measurement>xLoMem && measurement < vLoMem
							|| measurement>vUpMem && measurement<xUpMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem && measurement<=vUpMem) muxBuffer[3]='v';
 						break;
					case ADV_MOD_VEXEV:
						if(measurement<=xLoMem || measurement>=xUpMem) muxBuffer[3]='v';
						else if(measurement>xLoMem && measurement < vLoMem
							|| measurement>vUpMem && measurement<xUpMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem && measurement<=vUpMem) muxBuffer[3]='x';
 						break;
					case ADV_MOD_XEV:
						if(measurement<=xUpMem) muxBuffer[3]='x';
						else if(measurement>xUpMem && measurement < vLoMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem) muxBuffer[3]='v';
 						break;
					case ADV_MOD_VEX:
						if(measurement<=vUpMem) muxBuffer[3]='v';
						else if(measurement>vUpMem && measurement < vLoMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem) muxBuffer[3]='x';
 						break;
					case ADV_MOD_EXEVE:
						if(measurement<=xUpMem && measurement>=eLoMem) muxBuffer[3]='x';
						else if(measurement>xUpMem && measurement < vLoMem
							|| measurement<eLoMem
							|| measurement>eUpMem) muxBuffer[3]='!';
						else if(measurement>=vLoMem && measurement<=eUpMem) muxBuffer[3]='v';
 						break;
					case ADV_MOD_EVEXE:
						if(measurement<=vUpMem && measurement>=eLoMem) muxBuffer[3]='v';
						else if(measurement>vUpMem && measurement < xLoMem
							|| measurement<eLoMem
							|| measurement>eUpMem) muxBuffer[3]='!';
						else if(measurement>=xLoMem && measurement<=eUpMem) muxBuffer[3]='x';
					}
				}
			}
		else if(state==E_MENU_BRILLO)
			{
			muxBuffer[0]='b';
			muxBuffer[1]='r';
			muxBuffer[2]='i';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_MENU_ADV_MODE)
			{
			muxBuffer[0]='n';
			muxBuffer[1]='o';
			muxBuffer[2]='d';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_MENU_LIMITS)
			{
			muxBuffer[0]='L';
			muxBuffer[1]='i';
			muxBuffer[2]='n';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_MENU_ESCALA)
			{
			muxBuffer[0]='E';
			muxBuffer[1]='S';
			muxBuffer[2]='c';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_MENU_USER_CAL)
			{
			muxBuffer[0]='u';
			muxBuffer[1]='C';
			muxBuffer[2]='A';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_MENU_FACTORY_CAL)
			{
			muxBuffer[0]='F';
			muxBuffer[1]='C';
			muxBuffer[2]='A';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_SET_BRILLO)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				muxBuffer[ADV]=' ';
				display=brilloMem;
				uintToStr(display,&muxBuffer[2],1);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_MODE)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				muxBuffer[ADV]=' ';
				display=advModeMem;
				uintToStr(display,&muxBuffer[2],1);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ESCALA_ENT_DESCRIPTION)
			{
			muxBuffer[0]='E';
			muxBuffer[1]='n';
			muxBuffer[2]='t';
			muxBuffer[ADV]=' ' ;
			}
		else if(state==E_SET_ESCALA_ENT)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=escEntMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ESCALA_DEC_DESCRIPTION)
			{
			muxBuffer[0]='d';
			muxBuffer[1]='E';
			muxBuffer[2]='c';
			muxBuffer[ADV]=' ';
			}
		else if(state==E_SET_ESCALA_DEC)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=escDecMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_XLO_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='L';
			muxBuffer[2]='o';
			muxBuffer[ADV]='x';
			}
		else if(state==E_SET_ADV_XUP_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='H';
			muxBuffer[2]='i';
			muxBuffer[ADV]='x';
			}
		else if(state==E_SET_ADV_ELO_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='L';
			muxBuffer[2]='o';
			muxBuffer[ADV]='!';
			}
		else if(state==E_SET_ADV_EUP_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='H';
			muxBuffer[2]='i';
			muxBuffer[ADV]='!';
			}
		else if(state==E_SET_ADV_VLO_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='L';
			muxBuffer[2]='o';
			muxBuffer[ADV]='v';
			}
		else if(state==E_SET_ADV_VUP_DESCRIPTION)
			{
			muxBuffer[0]=' ';
			muxBuffer[1]='H';
			muxBuffer[2]='i';
			muxBuffer[ADV]='v';
			}
		else if(state==E_SET_ADV_XLO)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=xLoMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_XUP)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=xUpMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_ELO)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=eLoMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_EUP)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=eUpMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_VLO)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=vLoMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}
		else if(state==E_SET_ADV_VUP)
			{
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_OFF)) {TMR_START(TMR_SHOW_SETTING_ON);}
			if(TMR_TIMEOUT(TMR_SHOW_SETTING_ON)) {TMR_START(TMR_SHOW_SETTING_OFF);}

			if(TMR_RUNNING(TMR_SHOW_SETTING_ON))
				{
				display=vUpMem;
				uintToStr(display,&muxBuffer[0],3);
				}
			else
				ALL_DIGITS_BLANK();
			}

		//CUANDO PRESIONAN BOTON INCREMENTAR
		if(PULSPIN_EVENT_ID_FP(UP_FP))
			{
			if(ignoreNextFp) ignoreNextFp=0;
			else
				{
				TMR_STOP(TMR_LONG_PULS_UP);
	
				//FGR: CONDICION PARA STATE++ ES QUE EN EL ENUM, LUEGO DEL IDLE VIENEN TODOS LOS MENUES
				if(state>=E_IDLE && state<E_MENU_FACTORY_CAL)
					{
					state++;
					BUZZER=1;
					TMR_START(TMR_SHOW_MENU);
					TMR_START(TMR_BEEP);
					}
				else if(state==E_MENU_FACTORY_CAL)
					{
					state=E_MENU_BRILLO;
					BUZZER=1;
					TMR_START(TMR_SHOW_MENU);
					TMR_START(TMR_BEEP);
					}
				else incVar();
				}
			}

		//CUANDO PRESIONAN BOTON DECREMENTAR
		if(PULSPIN_EVENT_ID_FP(DWN_FP))
			{
			if(ignoreNextFp) ignoreNextFp=0;
			else
				{
				TMR_STOP(TMR_LONG_PULS_DWN);
	
				//FGR: CONDICION PARA STATE++ ES QUE EN EL ENUM, LUEGO DEL IDLE VIENEN TODOS LOS MENUES
				if(state>=E_IDLE && state<E_MENU_FACTORY_CAL)
					{
					state++;
					BUZZER=1;
					TMR_START(TMR_SHOW_MENU);
					TMR_START(TMR_BEEP);
					}
				else if(state==E_MENU_FACTORY_CAL)
					{
					state=E_MENU_BRILLO;
					BUZZER=1;
					TMR_START(TMR_SHOW_MENU);
					TMR_START(TMR_BEEP);
					}
				else decVar();
				}
			}

		//FGR: AQUI SE DETERMINAN TODOS LOS ESTADOS QUE ACEPTAN PULSACION LARGA
		if(PULSPIN_EVENT_ID_FN(UP_FN))
			{
			if(state==E_MENU_BRILLO || state==E_MENU_ADV_MODE || state==E_MENU_LIMITS
				|| state==E_MENU_ESCALA || state==E_SET_ESCALA_ENT || state==E_SET_ESCALA_DEC
				|| state==E_MENU_USER_CAL || state==E_MENU_FACTORY_CAL
				|| state==E_SET_ADV_XLO || state==E_SET_ADV_XUP
				|| state==E_SET_ADV_ELO || state==E_SET_ADV_EUP
				|| state==E_SET_ADV_VLO || state==E_SET_ADV_VUP)
				TMR_START(TMR_LONG_PULS_UP);
			}

		//CUANDO PRESIONAN BOTON DECREMENTAR
		if(PULSPIN_EVENT_ID_FN(DWN_FN))
			{
			if(state==E_MENU_BRILLO || state==E_MENU_ADV_MODE || state==E_MENU_LIMITS
				|| state==E_MENU_ESCALA || state==E_SET_ESCALA_ENT || state==E_SET_ESCALA_DEC
				|| state==E_MENU_USER_CAL || state==E_MENU_FACTORY_CAL
				|| state==E_SET_ADV_XLO || state==E_SET_ADV_XUP
				|| state==E_SET_ADV_ELO || state==E_SET_ADV_EUP
				|| state==E_SET_ADV_VLO || state==E_SET_ADV_VUP)
				TMR_START(TMR_LONG_PULS_DWN);
			}
		}
	}

