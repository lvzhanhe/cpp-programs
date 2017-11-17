#include<iostream>
using std::fixed;
#include<cmath>
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
#include<iomanip>
using std::setprecision; 

#include "twod.h"

TwoD::TwoD(double xval, double yval){
	x = xval;
	y = yval;
}

string TwoD::to_string(){
	ostringstream result;
	result << fixed << setprecision(2);
	result << "(" << x << ", " << y << ")";
	return result.str();
}

TwoD TwoD::diff(TwoD a){
	return TwoD(x - a.x, y - a.y);
}

TwoD TwoD::mult(double b){
	return TwoD(x * b, y * b);
}

double TwoD::dot_product(TwoD v1){
	return (x * v1.x) + (y * v1.y);
}

double TwoD::magnitude_squared(){
	return pow(x,2) + pow(y,2);
}