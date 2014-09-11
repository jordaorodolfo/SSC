/** \file utils.h header containing useful functions.

  As the project progressed, many of these functions were not used anymore, but
  they were kept here in case they are needed later on. Most of them consists
  of useful mathematical operations.
  */

/** arduino built-in map for double.

  Similiar to the arduino built-in function map, working in the same way but
  accepting double as inputs and return a double as result.
  */
double doubleMap(double, double, double, double, double); //just a map with double precision

/** dot product for vector.

  takes two double vectors and their length (they must be equal, hence only one
  is needed), and compute their euclidian dot product, return a double.
  */
double vectorDot(unsigned int,double*,double*);

/** sum the elements of a vector.

  Takes a double vector and its length and return the sum of its elements as
  a double.
  */
double vectorSum(unsigned int,double*);

/** separate linear regression trend

  Takes the length of two double vectors along themselves and calculte the
  linear regression trend of the data.
  */
double linearRegAngCoef(unsigned int, double*, double*);

/** separate linear regression coefficient

  Takes the length of two double vectors along themselves and calculte the
  linear regression coefficient of the data.
  */
double linearRegLinCoef(unsigned int, double*, double*);

/** separate linear regression

  Takes the length of two double vectors along themselves and calculte the
  linear regression of the data, returning a two-dimensional vector of the
  trend and coefficient as a result.
  */
double * linearReg(unsigned int, double*, double*);

/** arithmetic mean of a vector

  Takes the lenght of a vector along the vector itself and return the mean
  of its elements.
  */
double vectorMean(unsigned int, double*);

/** print in Arduino in a double format.

  meant to be more malleable than the standard Serial.print of the Arduino
  platform, by inputting the desired double to be printed and the decimal
  cases which should also be printed.
  */
void printDouble(double, unsigned int);
