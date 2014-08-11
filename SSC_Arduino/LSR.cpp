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
  newLSR->sx = 0;
  newLSR->sy = 0;
  newLSR->sxy = 0;
  newLSR->sxx = 0;
  newLSR->trend = 0;
  newLSR->constant = 0;
  newLSR->Den = 0;
  newLSR->cut_index = cut_index_;
  return newLSR;
}

void addValuePairLSR(LSR_t *target, double x, double y)
{
  if(target->n >= target->cut_index)
  {
    target->Den = target->sxx*double(target->n)-target->sx*target->sx;
    target->trend = (target->sx*target->sxy-target->sx*target->sx)/target->Den;
    target->constant = (target->sy*target->sxx - target->sx*target->sxy)/target->Den;
  }
  else
  {
    target->sx += x;
    target->sy += y;
    target->sxx += x*x;
    target->sxy += y*x;
    target->n++;
  }
}

void addValueLSR(LSR_t *target, double y)
{
  addValuePairLSR(target,double(target->n+1),y);
}

double getTrendLSR(LSR_t *target)
{
  return target->trend;
}

