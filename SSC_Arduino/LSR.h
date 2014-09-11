/** \file LSR.h Least Squares Regression.

  This header file contains the LSR algorithm abstraction and its
  corresponding functions; such as calculating the trend and axis intersection
  and adding a new value to the list.
  */

/** pseudo-class abstraction for the least squares algorithm.

    The implementation does not use a vector, rather, it uses single variables
    to keep track of the necessary sums and smapling size; thus, keep in mind that
    the internal variables may overflow eventually for a huge sample.
  */
typedef struct LSR
{
  //! internal sampling size.
  unsigned long n;
  /** true sampling size.

    When the internal sampling size reaches the index; the abstraction performs
    the necessary calculations to store the trend and constant into its internal
    varibles, which can be acessed at any time.

    */
  unsigned long cut_index;
  //! sum if all X values.
  double sx;
  //! sum of all Y values.
  double sy;
  //! sum of all X values squared.
  double sxx;
  //! sum of the product of all the X and Y values.
  double sxy;
  //! the trend calculated for the sample.
  double trend;
  //! the constant calculated for the sample.
  double constant;
  //! A denominator internal variable for the calculations.
  double Den;
} LSR_t;

/** LSR pseudo-class initialization.

  by giving \a cut_index to the funciton; an empty LSR is allocated within memory
  and returned. If later the cutting index need to be changed, this can be done
  by directly acessing the structure internal variables; no harm is done o the
  calculations in this matter.

  @param[in] cut_index_ Initial cutting index; can be changed.
  @return LSR
  */
LSR_t* initLSR(unsigned long cut_index_);

/** adds a new value pair to \a target of type LSR.

  By giving \a x and \a y values, all the internal calculations and necessary
  updates within the least squares algorithm are taken case of. If the sample
  size has reached the cutting index; this algorithm calculates the trend and
  the constant of the linear regression.

  @see LSR
  @param[in] target abstraction to me modified.
  @param[in] x an X value for the algorithm.
  @param[in] y an X corresponding Y value for the algorithm.
  */
void addValuePairLSR(LSR_t *target, double x, double y);

/** adds a new value pair to \a target assuming that X is the current index.

  This functions behaves exactly in the same manner as addValuePairLSR(), except
  that the \a y corresponding X value is assumed to be the integer representing
  the y index in the list, e.g. if the sample size is 6, the next y index would
  be 7.

  @param[in] target abstraction to me modified.
  @see addValuePairLSR(LSR_t *target, double x, double y)
  @param[in] y an Y value for the algorithm calculation.
  */

void addValueLSR(LSR_t *target, double y);

/** \deprecated Can be safely removed, but does not add any size to the code
  simple function to return the calculated trend.

  Deprecated since the internal variables can be accessed directly; exists
  as a reminiscent of a previous class-driven implementation.

  @param[in] target abstraction to me modified.
  @return double
  */
double getTrendLSR(LSR_t *target);
