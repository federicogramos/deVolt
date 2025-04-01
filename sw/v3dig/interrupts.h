////////////////////////////////////////////////////////////////////////////////
// interrupts.h                                                               //
////////////////////////////////////////////////////////////////////////////////
// Librería que maneja las interrupciones.

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS                                                                  //
////////////////////////////////////////////////////////////////////////////////

#define IRQ_TIMER0_RESET_VAL 241
// Se setea el tiempo de interrupción en 2.5ms (oscilador=20Mhz,
// timer0 prescaler=64). Calculo a realizar:
// n=256-(Tinterrupt[s])*(fclk[Hz]/[8*prescaler])=256-(3.125E-3)*(48E6/[4*256])=109

#define IRQ_TIMER3_RESET_VAL 64036UL
// Importantísimo: es indispensable especificar que el número es UL (unsigned
// long), porque de otro modo, el compilador lo pierde en el camino, y cuando
// lo quiero asignar, solamente asigna un byte, y el resto cero.
// Se setea el tiempo de interrupción en 250ms (oscilador interno=20Mhz,
// timer1 con prescaler=8). Calculo a realizar:
// n=65536-(Tinterrupt[s])*(fclk[Hz]/[4*prescaler])
// n=65536-25E-3*(48E6/[4*8])=28036

#define IRQ_TIMER2_RESET_VAL 255

////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////

#define IRQ_ENABLE()  {GIE=1;}
#define IRQ_DISABLE() {GIE=0;}

#define IRQ_PERIPHERAL_ENABLE()  {PEIE=1;}
#define IRQ_PERIPHERAL_DISABLE() {PEIE=0;}
// Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
   



// Esta función, asigna un valor al acumulador del timer0.
// If TMR0 is written, the increment is inhibited for the following two
// instruction cycles. The user can work around this by writing an adjusted
// value to the TMR0 register.

#define IRQ_TIMER1_SET(value) {                      \
                              TMR1L=LOW_BYTE(value); \
                              TMR1H=HIGH_BYTE(value);\
                              }



// Esta función, asigna un valor al acumulador del timer0.
// If TMR0 is written, the increment is inhibited for the following two
// instruction cycles. The user can work around this by writing an adjusted
// value to the TMR0 register.



#define IRQ_TIMER0_SETUP() {                                    \
                           T0CONbits.T08BIT=1;              \
                           T0CONbits.T0CS=0;                       \
                           T0CONbits.PSA=0;                               \
                           T0CONbits.T0PS=0x07;                          \
                           TMR0=IRQ_TIMER0_RESET_VAL;\
                           T0CONbits.TMR0ON=1;           \
                           }

#define IRQ_TIMER1_SETUP() {                                    \
                           T1CONbits.TMR1CS=0;                            \
                           T1CONbits.T1CKPS=0x03;                          \
                           T1CONbits.T1SYNC=1;                            \
                           TMR1=IRQ_TIMER1_RESET_VAL;         \
                           T1CONbits.TMR1ON=1;                            \
                           T1CONbits.T1RUN=1;\
                           }



#define IRQ_TIMER3_SETUP() {                                    \
                           T3CONbits.TMR3CS=0;                            \
                           T3CONbits.T3CKPS=0x03;                          \
                           T3CONbits.T3SYNC=1;                            \
                           TMR3=IRQ_TIMER3_RESET_VAL;         \
                           T3CONbits.TMR3ON=1;                            \
                           T3CONbits.RD16=1;\
                           }



#define IRQ_TIMER0 TMR0IE&&TMR0IF
// Timer0 interrupt enable and flag set.

#define IRQ_TIMER1 TMR1IE&&TMR1IF
// Timer1 interrupt enable and flag set.

#define IRQ_TIMER2 TMR2IE&&TMR2IF
// Timer2 interrupt enable and flag set.

#define IRQ_CCP1 CCP1IE&&CCP1IF
#define IRQ_CCP2 CCP2IE&&CCP2IF

#define IRQ_ADC ADIE&&ADIF
// ADC


////////////////////////////////////////////////////////////////////////////////
// FUNCIONES                                                                  //
////////////////////////////////////////////////////////////////////////////////

void isr_timer0(void);
void isr_timer3(void);

