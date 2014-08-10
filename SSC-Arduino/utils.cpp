#ifndef H_UTILS
#include "utils.h"
#define H_UTILS
#endif
#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

double doubleMap(double v,double xi,double xf,double yi,double yf)
{
  return (v-xi)/(xf-xi)*(yf-yi)+yi;
}

double linearRegAngCoef(unsigned int dim, double * X, double * Y)
{
  return (vectorDot(dim,X,Y)*dim-vectorSum(dim,X)*vectorSum(dim,Y))/
    (vectorDot(dim,X,X)*dim-vectorSum(dim,X)*vectorSum(dim,X));
}

double linearRegLinCoef(unsigned int dim, double * X, double * Y)
{
  return (vectorSum(dim,Y)*vectorDot(dim,X,X)-vectorSum(dim,X)*vectorDot(dim,X,Y))/
    (vectorDot(dim,X,X)*dim-vectorSum(dim,X)*vectorSum(dim,X));
}

double * linearReg(unsigned int dim, double * X, double * Y)
{
  double Det = vectorDot(dim,X,X)*dim-vectorSum(dim,X)*vectorSum(dim,X);
  double coef[2];
  coef[0] = (vectorSum(dim,Y)*vectorDot(dim,X,X)-vectorSum(dim,X)*vectorDot(dim,X,Y))/Det;
  coef[1] = (vectorDot(dim,X,Y)*dim-vectorSum(dim,X)*vectorSum(dim,Y))/Det;
  return coef;
}

double vectorSum(unsigned int dim, double * vector)
{
  double sum = 0;
  unsigned int i;
  for(i=0;i<dim;i++)
    sum+=vector[i];
  return sum;
}

double vectorDot(unsigned int dim, double * vector1, double * vector2)
{
  double sum = 0;
  unsigned int i;
  for(i=0;i<dim;i++)
    sum+=vector1[i]*vector2[i];
  return sum;
}

double vectorMean(unsigned int dim, double * vector)
{
  return vectorSum(dim,vector)/dim;
}

void printDouble(double value, unsigned int precision)
{
  unsigned int i;
  double frac;
  Serial.print(int(value));
  Serial.print('.');
  frac = value - int(value);
  for(i=1;i<=precision;i++)
  {
    Serial.print(abs(int(10*frac)));
    frac = 10*frac - int(10*frac);
  }
}
