typedef struct LSR
{
  unsigned long n;
  unsigned long cut_index;
  double sx;
  double sy;
  double sxx;
  double sxy;
  double trend;
  double constant;
  double Den;
} LSR_t;

LSR_t* initLSR(unsigned long cut_index_);
void addValuePairLSR(LSR_t *target, double x, double y);
void addValueLSR(LSR_t *target, double x, double y);
double getTrendLSR(LSR_t *target);
