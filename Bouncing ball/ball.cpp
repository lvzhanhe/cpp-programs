#include<iostream>
using std::fixed;
#include<cmath>
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
#include<iomanip>
using std::setprecision; 

#include "ball.h"

Ball::Ball(double m, TwoD pos, TwoD speed, double r){
	mass = m;
	coords = pos;
	velocity = speed;
	radius = r;
}

string Ball::to_string(){
	ostringstream result;
	result << fixed << setprecision(2);
	result << mass << ", (" << coords.x << ", " << coords.y << "), (" << velocity.x << ", " << velocity.y << "), " << radius;
	return result.str();
}

bool Ball::contact_ball(Ball a){
	double total_r = a.radius + radius;
	double total_d = sqrt(pow((a.coords.x - coords.x), 2) + pow((a.coords.y - coords.y), 2));	
	if(total_r >= total_d)
		return true;
	return false;
}

bool Ball::contact_wall(long xdim, long ydim){
	if(coords.x + radius > xdim || coords.x - radius < 0 || coords.y + radius > ydim || coords.y - radius < 0)
		return true;
	return false;
}

TwoD Ball::update_velocity_wall(long xdim, long ydim){
	if(contact_wall(xdim, ydim)){
		if(coords.x + radius > xdim || coords.x - radius < 0)
			return TwoD(-velocity.x, velocity.y);
		else
			return TwoD(velocity.x, -velocity.y);
	}
	return TwoD(velocity.x, velocity.y);
}

TwoD Ball::update_velocity_ball(Ball b){
	if(contact_ball(b)){
		double up = (velocity.diff(b.velocity)).dot_product(coords.diff(b.coords));
		double down = (coords.diff(b.coords)).magnitude_squared();
		double front = (2 * b.mass / (mass + b.mass)) * up / down;
		return velocity.diff((coords.diff(b.coords)).mult(front));
	}
	return TwoD(velocity.x, velocity.y);
}