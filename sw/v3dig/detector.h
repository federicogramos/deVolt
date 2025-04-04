////////////////////////////////////////////////////////////////////////////////
// detector.h                                                                    //
////////////////////////////////////////////////////////////////////////////////

#ifndef __DETECTOR_H
#define __DETECTOR_H



#define DET_PERIOD_MIN 19
#define DET_PERIOD_MAX 255

////////////////////////////////////////////////////////////////////////////////
// ESTRUCTURAS                                          //
////////////////////////////////////////////////////////////////////////////////

struct structure_detector
{
unsigned char period;
unsigned char state;
unsigned char trh;
unsigned char trl;
unsigned char tfh;
unsigned char tfl;

};

typedef struct structure_detector t_detector;

extern t_detector det;


#endif
   // __DETECTOR_H