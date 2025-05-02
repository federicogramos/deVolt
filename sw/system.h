// system.h

#define ALL_INPUT 0xFF
#define INPUT 1
#define OUTPUT 0

// PUERTOS

#define UP0 PORTAbits.RA0
#define UP1 PORTAbits.RA1
#define UP2 PORTAbits.RA5
#define UP3 PORTAbits.RA3
#define UP4 PORTAbits.RA4

#define SEGA PORTAbits.RA2
#define SEGB PORTBbits.RB7
#define SEGC PORTBbits.RB1
#define SEGD PORTBbits.RB2
#define SEGE PORTBbits.RB4
#define SEGF PORTBbits.RB6
#define SEGG PORTBbits.RB5
#define DP PORTBbits.RB3

#define PULS_UP PORTCbits.RC0
#define PULS_DWN PORTCbits.RC1
#define BUZZER PORTCbits.RC6

////////////////////////////////////////////////////////////////////////////////
// DATA DIRECTION REGISTERS

#define DDR_UP0 TRISA0
#define DDR_UP1 TRISA1
#define DDR_UP2 TRISA5
#define DDR_UP3 TRISA3
#define DDR_UP4 TRISA4

#define DDR_SEGA TRISA2
#define DDR_SEGB TRISB7
#define DDR_SEGC TRISB1
#define DDR_SEGD TRISB2
#define DDR_SEGE TRISB4
#define DDR_SEGF TRISB6
#define DDR_SEGG TRISB5
#define DDR_DP TRISB3

#define DDR_PULS_UP TRISC0
#define DDR_PULS_DWN TRISC1
#define DDR_BUZZER TRISC6

#define INIT_DDR() {               \
                   DDR_UP0=OUTPUT; \
                   DDR_UP1=OUTPUT; \
                   DDR_UP2=OUTPUT; \
                   DDR_UP3=OUTPUT; \
                   DDR_UP4=OUTPUT; \
                   \
                   DDR_SEGA=OUTPUT;\
                   DDR_SEGB=OUTPUT;\
                   DDR_SEGC=OUTPUT;\
                   DDR_SEGD=OUTPUT;\
                   DDR_SEGE=OUTPUT;\
                   DDR_SEGF=OUTPUT;\
                   DDR_SEGG=OUTPUT;\
                   DDR_DP=OUTPUT;\
                   \
                   DDR_BUZZER=OUTPUT;\
                   }   

#define INIT_PORTS() {      \
                     UP0=0; \
                     UP1=0; \
                     UP2=0; \
                     UP3=0; \
                     UP4=0; \
                     \
                     SEGA=0;\
                     SEGB=0;\
                     SEGC=0;\
                     SEGD=0;\
                     SEGE=0;\
                     SEGF=0;\
                     SEGG=0;\
                     DP=0;\
                     \
                     BUZZER=0;\
                     }

////////////////////////////////////////////////////////////////////////////////
// FUNCIONES
void systemInit(void);
