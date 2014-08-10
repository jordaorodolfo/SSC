#ifndef H_LSR
#include "LSR.h"
#define H_LSR
#endif
#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

LSR_t* initLSR(unsigned long cut_index_)
{
  LSR_t * newLSR = (LSR_t*)malloc(sizeof(LSR_t));
  newLSR->n = 0;
  newLSR->he = 0;
  newLSR->se = 0;
  newLSR->trend = 0;
  newLSR->cut_index = cut_index_;
  return newLSR;
}

void addErrorLSR(LSR_t *target, double e)
{
  if(target->n >= target->cut_index)
  {
    double den = denominatorLSR(target);
    target->trend = double(target->n)*target->he-target->se*double(target->n*(target->n+1)/2)/den;
  }
  else
  {
    target->se += e;
    target->he += e*double(target->n);
    target->n++;
  }
}

double getTrendLSR(LSR_t *target)
{
  return target->trend;
}

double denominatorLSR(LSR_t * target)
{
  unsigned long square_power = target->n*target->n;
  unsigned long fourth_power = square_power*square_power;
  return 1.0/12.0*(double(fourth_power-square_power));
}

