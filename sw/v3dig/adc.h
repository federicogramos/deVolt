// adc.h

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4
#define CHANNEL5 5
#define CHANNEL6 6
#define CHANNEL7 7
#define CHANNEL12 12

#define ADC_VIN CHANNEL12

typedef struct
{
unsigned int completeFlg:1;//conversion complete
unsigned int inProcessFlg:1;//está haciendo una conversión. Se mantiene en 1
// mientras esté "ocupado" el ADC. Solo cuando el usuario leyó la conversión,
// regresa a cero.
unsigned char chComp;//numero de canal completado
unsigned int flgs2convert;//flags que indican canales que tienen que convertir
char nx2convert;// Next to convert. Avanza desde channel0 a channel12 preguntando si tiene
// que convertir. Al llegar al 7, comienza nuevamente desde el 0. Esto permite
// que le de bola a todos, y que no haya priodidades.
}t_adc;

int getConv(void);
void adcDriver(void);
void isr_adc(void);
void adcSetup(void);

extern t_adc adcStruct;

#define ADC_START(n) BIT_SET(adcStruct.flgs2convert,n)
#define ADC_NEW_RESULT(channel) (adcStruct.completeFlg && adcStruct.chComp==channel)

//ADCHS

