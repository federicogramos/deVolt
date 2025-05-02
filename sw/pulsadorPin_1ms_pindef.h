// pulsadorPin_pindef.h

#ifndef __PULSADOR_PIN_PINDEF_H
#define __PULSADOR_PIN_PINDEF_H

enum e_flancoPos {FP_DIS,FP_EN};
enum e_flancoNeg {FN_DIS,FN_EN};
enum e_unbounceRst {UNBOUNCE_RST_DIS,UNBOUNCE_RST_EN};

t_pulsPin pulsPin[PULS_PIN_CANT]={
                                 {(char*)&PORTC,0,1,1,FP_DIS,FN_EN,UNBOUNCE_RST_EN,0},
                                 {(char*)&PORTC,1,1,1,FP_DIS,FN_EN,UNBOUNCE_RST_EN,0},
                                 {(char*)&PORTC,0,1,1,FP_EN,FN_DIS,UNBOUNCE_RST_EN,0},
                                 {(char*)&PORTC,1,1,1,FP_EN,FN_DIS,UNBOUNCE_RST_EN,0}
                                 };

#endif//__PULSADOR_PIN_PINDEF_H
