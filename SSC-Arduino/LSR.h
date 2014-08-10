typedef struct LSR
{
  unsigned long n;
  unsigned long cut_index;
  double he;
  double se;
  double trend;
} LSR_t;

LSR_t* initLSR(unsigned long cut_index_);
void addErrorLSR(LSR_t *target, double e);
double getTrendLSR(LSR_t *target);
double denominatorLSR(LSR_t * target);
