////////////////////////////////////////////////////////////////////////////////
// iir.c
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <iir.h>

//Filter type: Low Pass
//Filter model: Butterworth
//Filter order: 2
//Sampling Frequency: 100Hz
//Cut Frequency: 1Hz

#define NCoef 2

float x[NCoef+1];
float y[NCoef+1];

//int iir(float NewSample)
float iir(float NewSample)
   {
   float ACoef[NCoef+1]={  0.00094547653094439164,0.00189095306188878330,0.00094547653094439164};
   float BCoef[NCoef+1]={1.00000000000000000000,-1.91119706742607360000,0.91497583480143418000};
    //output samples. Warning! This variable should be signed (input sample width + Coefs width + 2 )-bit width to avoid saturation.
    //input samples
   char n;

   for(n=NCoef;n>0;n--)//shift the old samples
      {
      x[n]=x[n-1];
      y[n]=y[n-1];
      }

   //Calculate the new output
   x[0]=NewSample;
   y[0]=ACoef[0]*x[0];
   for(n=1;n<=NCoef;n++) y[0]+=ACoef[n]*x[n]-BCoef[n]*y[n];
   y[0]/=BCoef[0];

//   return (int)y[0];
	return y[0];
   }
