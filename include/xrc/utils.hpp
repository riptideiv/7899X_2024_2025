#pragma once
#include<math.h>

double deg2rad(double degrees){
    return degrees*M_PI/180;
}

double dsin(double degrees){
    return sin(deg2rad(degrees));
}