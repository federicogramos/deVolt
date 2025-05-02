////////////////////////////////////////////////////////////////////////////////
// main.h                                                                     //
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAIN_H
#define __MAIN_H


#pragma config PLLDIV=5
#pragma config CPUDIV=OSC1_PLL2

#pragma config FOSC=HSPLL_HS

//FGR: En el voltimetro 20cm ocurria que al tener BORV=3 (2.05V) aparentemente,
// al apagar la alimentacion, habia suficiente tiempo para un funcionamiento erratico
// escribiendo la EEPROM (en la variable que controlaba al brillo del cartel).
// Cambiando a BOTV=1 (4.33V) deja de ocurrir.
#pragma config BOR=ON
#pragma config BORV=1
#pragma config PWRT=ON

#pragma config WDT=OFF

#pragma config PBADEN=OFF
#pragma config LPT1OSC=OFF
#pragma config MCLRE=OFF

#pragma config DEBUG=OFF
#pragma config STVREN=OFF
#pragma config LVP=OFF

#pragma config CP0=ON
#pragma config CP1=ON
#pragma config CP2=ON
#pragma config CP3=ON

#pragma config CPD=ON
#pragma config CPB=ON

#pragma config WRT0=ON
#pragma config WRT1=ON
#pragma config WRT2=ON
#pragma config WRT3=ON

//#pragma config WRTD=OFF
#pragma config WRTB=ON
#pragma config WRTC=ON

#pragma config EBTR0=1
#pragma config EBTR1=1
#pragma config EBTR2=1
#pragma config EBTR3=1

#pragma config EBTRB=1

#pragma config IDLOC0=0
#pragma config IDLOC1=0
#pragma config IDLOC2=0
#pragma config IDLOC3=0
#pragma config IDLOC4=0
#pragma config IDLOC5=0
#pragma config IDLOC6=0
#pragma config IDLOC7=0

#endif
// __MAIN_H