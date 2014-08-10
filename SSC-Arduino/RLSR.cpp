#ifndef H_RLSR
#include "RLSR.h"
#define H_RLSR
#endif
#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

RLSR_t* initRLSR()
{
  RLSR_t * newRLSR = (RLSR_t*)malloc(sizeof(RLSR_t));
  newRLSR->sx = 0;
  newRLSR->sy = 0;
  newRLSR->sxx = 0;
  newRLSR->sxy = 0;
  newRLSR->D1 = 0;
  newRLSR->D2 = 0;
  newRLSR->trend = 0;
  newRLSR->constant = 0;
  return newRLSR;
}

void addValuePairRLSR(RLSR_t *target, double x, double y)
{
  switch(target->n)
  {
  case 0:
    target->sx = x;
    target->sy = y;
    target->sxx = x*x;
    target->sxy = x*y;
    break;
  case 1:
    target->sx += x;
    target->sy += y;
    target->sxx += x*x;
    target->sxy += x*y;
    target->D1 = 2*target->sxx - target->sx*target->sx;
    target->trend = (2*target->sxy - target->sx*target->sx)/target->D1;
    target->constant = (target->sy*target->sxx - target->sx*target->sxy)/target->D1;
    break;
  default:
    target->D2 = target->D1 + target->sxx + double(target->n)*x*x - 2*x*target->sx;
    target->trend = (target->D1*target->trend + target->sxy - double(target->n)*x*y - target->sx*y - target->sy*x)/target->D2;
    target->constant = (target->D1*target->constant + target->sy*x*x + y*target->sxx - target->sx*y - target->sy*x)/target->D2;
    target->sx += x;
    target->sy += y;
    target->sxx += x*x;
    target->sxy += x*y;
    target->D1 = target->D2;
    break;
  }
  target->n++;
}

void addValueRLSR(RLSR_t * target, double y)
{
  addValuePairRLSR(target,target->n+1,y);
}

double getTrendRLSR(RLSR_t *target)
{
  return target->trend;
}
