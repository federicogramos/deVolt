//////// Standard Header file for the PIC12F683 device ///////////////
//#device PIC12F683
//#nolist
//////// Program memory: 2048x14  Data RAM: 128  Stack: 8
//////// I/O: 6   Analog Pins: 4
//////// Data EEPROM: 256
//////// C Scratch area: 20   ID Location: 2000
//////// Fuses: LP,XT,HS,EC_IO,NOWDT,WDT,CPD,NOCPD,PROTECT,NOPROTECT,NOMCLR
//////// Fuses: MCLR,PUT,NOPUT,INTRC_IO,INTRC,RC_IO,RC,BROWNOUT,NOBROWNOUT
//////// Fuses: BROWNOUT_NOSL,BROWNOUT_SW,IESO,NOIESO,FCMEN,NOFCMEN
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  40
#define PIN_A1  41
#define PIN_A2  42
#define PIN_A3  43
#define PIN_A4  44
#define PIN_A5  45

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int8
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:
#define WDT_FROM_SLEEP  3     
#define WDT_TIMEOUT     11    
#define MCLR_FROM_SLEEP 19    
#define MCLR_FROM_RUN   27    
#define NORMAL_POWER_UP 25    
#define BROWNOUT_RESTART 26   

////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define RTCC_INTERNAL   0
#define RTCC_EXT_L_TO_H 32
#define RTCC_EXT_H_TO_L 48

#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7


#define RTCC_8_BIT      0     

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
// WDT base is 18ms
//

#define WDT_18MS        8   
#define WDT_36MS        9   
#define WDT_72MS       10   
#define WDT_144MS      11   
#define WDT_288MS      12   
#define WDT_576MS      13   
#define WDT_1152MS     14   
#define WDT_2304MS     15   

// One of the following may be OR'ed in with the above:

#define WDT_ON             0x4100   
#define WDT_OFF            0       
#define WDT_DIV_16         0x100
#define WDT_DIV_8          0x300
#define WDT_DIV_4          0x500
#define WDT_DIV_2          0x700
#define WDT_TIMES_1        0x900  // Default
#define WDT_TIMES_2        0xB00
#define WDT_TIMES_4        0xD00
#define WDT_TIMES_8        0xF00
#define WDT_TIMES_16      0x1100
#define WDT_TIMES_32      0x1300
#define WDT_TIMES_64      0x1500
#define WDT_TIMES_128     0x1700

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         5
#define T1_EXTERNAL         7
#define T1_EXTERNAL_SYNC    3

#define T1_CLK_OUT          8

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

#define T1_GATE           0x40
#define T1_GATE_INVERTED  0xC0

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
long CCP_1;
//#byte   CCP_1    =                      0x13          
//#byte   CCP_1_LOW=                      0x13          
//#byte   CCP_1_HIGH=                     0x14          
////////////////////////////////////////////////////////////////// COMP
// Comparator Variables: C1OUT, C2OUT
// Constants used in setup_comparator() are:
#define NC_NC_NC_NC  0x0ff07
#define NC_NC  0x0ff07
#define A0_A1  0x3ff02
#define A1_VR_OUT_ON_A2  0x6fb03
#define A1_VR  0x2ff04
#define A0_A1_OUT_ON_A2  0x3fb01

//Optionally OR with the following
#define COMP_INVERT           0x10

//#bit C1OUT = 0x19.6

////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_vref() are:
//
#define VREF_LOW  0xa0
#define VREF_HIGH 0x80
// Or (with |) the above with a number 0-15

////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_31KHZ   1
#define OSC_125KHZ  0x11
#define OSC_250KHZ  0x21
#define OSC_500KHZ  0x31
#define OSC_1MHZ    0x41
#define OSC_2MHZ    0x51
#define OSC_4MHZ    0x61
#define OSC_8MHZ    0x71
#define OSC_INTRC   1
#define OSC_NORMAL  0
// Result may be (ignore all other bits)
#define OSC_STATE_STABLE 4
#define OSC_31KHZ_STABLE 2



////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF                0              // ADC Off
#define ADC_CLOCK_DIV_2    0x100
#define ADC_CLOCK_DIV_4     0x40
#define ADC_CLOCK_DIV_8     0x10
#define ADC_CLOCK_DIV_16    0x50
#define ADC_CLOCK_DIV_32    0x20
#define ADC_CLOCK_DIV_64    0x60
#define ADC_CLOCK_INTERNAL  0x30              // Internal 2-6us

// Constants used in SETUP_ADC_PORTS() are:
#define sAN0                   1         //| GP0
#define sAN1                   2         //| GP1
#define sAN2                   4         //| GP2
#define sAN3                   8         //| GP4
#define NO_ANALOGS             0         // None
#define AN0_ANALOG             1         //!old only provided for compatibility
#define AN1_ANALOG             2         //!old only provided for compatibility
#define AN2_ANALOG             4         //!old only provided for compatibility
#define AN3_ANALOG             8         //!old only provided for compatibility
#define ALL_ANALOG             7         //!old only provided for compatibility

// The following may be OR'ed in with the above using |
#define VSS_VDD              0x0000        //| Range 0-Vdd
#define VSS_VREF             0x4000        //| Range 0-Vref


// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6





////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0x0BC0
#define INT_RTCC                  0x0B20
#define INT_EXT                   0x0B10
#define INT_AD                    0x8C40
#define INT_TIMER1                0x8C01
#define INT_TIMER2                0x8C02
#define INT_TIMER0                0x0B20
#define INT_EEPROM                0x8C80
#define INT_COMP                  0x8C08
#define INT_RA                    0xFF0B08
#define INT_CCP1                  0x8C20
#define INT_OSC_FAIL              0x8C04
#define INT_RA0                   0x010B08
#define INT_RA1                   0x020B08
#define INT_RA2                   0x040B08
#define INT_RA3                   0x080B08
#define INT_RA4                   0x100B08
#define INT_RA5                   0x200B08

//#list
