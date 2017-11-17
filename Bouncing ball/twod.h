#ifndef TWOD
#define TWOD

#include<string>
using std::string;

struct TwoD{
  double x = 0;
  double y = 0;

  TwoD() =default;
  TwoD(double xval, double yval);

  string to_string();
  TwoD diff(TwoD);
  TwoD mult(double);
  double dot_product(TwoD);
  double magnitude_squared();
};

#endif
