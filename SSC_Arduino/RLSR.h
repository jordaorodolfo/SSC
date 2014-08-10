typedef struct RLSR
{
  unsigned long n;
  double D1;
  double D2;
  double sx;
  double sy;
  double sxx;
  double sxy;
  double trend;
  double constant;
} RLSR_t;

RLSR_t* initRLSR();
void addValuePairRLSR(RLSR_t *target, double x, double y);
void addValueRLSR(RLSR_t *target, double y);
double getTrendRLSR(RLSR_t *target);
