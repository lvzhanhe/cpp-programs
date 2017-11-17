#ifndef BALL
#define BALL

#include<string>
using std::string;

#include "twod.h"

struct Ball{
  double mass = 0;
  TwoD coords;
  TwoD velocity;
  double radius = 0;

  Ball()=default;
  Ball(double m, TwoD pos, TwoD speed, double r);

  string to_string();
  bool contact_ball(Ball);
  bool contact_wall(long xdim, long ydim);
  TwoD update_velocity_ball(Ball);
  TwoD update_velocity_wall(long xdim, long ydim);
};

#endif
