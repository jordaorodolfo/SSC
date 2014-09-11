/** \file RLSR.h Recursive least squares regression algorithm abstraction header/

  Except for the underlying algorithms, All the organization is the same as
  the LSR abstraction. The difference is that for each new added variable,
  a new trend and constant is calculated immediatly.
  */

/** Recursive least squares regression algorithm pseudo-class.

  In the same fashion as the LSR abstraction, this pseudo-class contains
  all the internal calculations variables necessary to better performance and
  variables representing the trend and constant after each sampling.

  @see LSR
  */
typedef struct RLSR
{
  //! variable for the sample size.
  unsigned int n;
  //! internal variable representing a denominator.
  double D1;
  //! internal variable representing a second denomiator.
  double D2;
  //! internal variable representing the X values summation.
  double sx;
  //! internal variable representing the Y values summation.
  double sy;
  //! internal variable representing the X squared summation.
  double sxx;
  //! internal variable representing the X mutlipled by Y summation.
  double sxy;
  //! variable representing the calculated trend.
  double trend;
  //! variable representing the calculated constant.
  double constant;
} RLSR_t;

/** RLSR initialization procedure.

  Unlike LSR, no cutting index is necessary as every pair addition results
  in an automatic calculation of the trend and constant without having to
  redo all the LSR calculations.

  A note is needed in this respect: Just like the LSR suffers from msicalculation
  if the cutting index is really big, the recursive estimation eventually wears
  off and give wrong results as samplign size increases witout bounds. Of course,
  this can be corrected by manually reseting the sampling size to 0, Restarting
  the algorithm.
  */
RLSR_t* initRLSR();

/** add a value pair to the RLSR abstraction algorithm.

  Works exactly like adding a pair to \a LSR abstraction, except that the
  new trend and constant are avialable right away.

  @see addValuePairLSR()
  */
void addValuePairRLSR(RLSR_t *target, double x, double y);

/** add a value to the RLSR algorithm assuming X value to be the current index.

  Works exactly like its LSR counterpart, except that the
  new trend and constant are avialable right away.

  @see addValueLSR()
  */
void addValueRLSR(RLSR_t *target, double y);

//! deprecated since the pseudo-class trend can be accessed directly.
double getTrendRLSR(RLSR_t *target);
