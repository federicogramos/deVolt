////////////////////////////////////////////////////////////////////////////////
// interrupts.c
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <thisProject.h>
#include <interrupts.h>
#include <system.h>
#include <segments.h>
#include <t0.h>
#include <mainDefinitions.h>
#include <adc.h>
#include <pulsadorPin_lib_1ms.h>

//unsigned char intensidad=8;
char tOnFlag;
unsigned char brilloTon[]={251,246,241,236,231};
unsigned char brilloToff[]={231,236,241,246,251};

void interrupt isr(void)
	{
	if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) isr_timer0();
	}

void interrupt low_priority isr2(void)
	{
	if(PIE2bits.TMR3IE && PIR2bits.TMR3IF) isr_timer3();
	else if(PIE1bits.ADIE && PIR1bits.ADIF) isr_adc();
	}

//Uso ???ms por display independientemente de la intensidad del brillo
void isr_timer0(void)
	{
	if(tOnFlag)
		{
		TMR0=brilloTon[brilloMem];//RESET FLAG INTERRUPCION
		tOnFlag=0;

		if(segments.nextUp>3)//Aqui determino cuanto multiplexo
			{
			rewind(&muxFile);//Empieza a leer de posicion cero
			segments.nextUp=0;
			}
		else segments.nextUp++;
		
DP=0;
		char2pins(fgetc(&muxFile));

		switch(segments.nextUp)
			{
			case 0: UP2=1; break;
			case 1: DP=1;UP1=1; break;
			case 2: UP0=1; break;
			case 3: UP4=1; break;
			}
		}
	else
		{
		TMR0=brilloToff[brilloMem];//RESET FLAG INTERRUPCION
		tOnFlag=1;

		UP0=0;
		UP1=0;
		UP2=0;
		UP4=0;
		DP=0;
		}
	INTCONbits.TMR0IF=0;
	}

void isr_timer3(void)//placa multiplexado = 1ms
	{
	TMR3=IRQ_TIMER3_RESET_VAL;// Reseteo del contador de la interrupción.

	timerDriver(TMR_ADCSAMPLE);
	timerDriver(TMR_250MS);

	timerDriver(TMR_BEEP);
	if(TMR_TIMEOUT(TMR_BEEP)) BUZZER=0;

	pulsPinDriver();

	PIR2bits.TMR3IF=0;
	}
