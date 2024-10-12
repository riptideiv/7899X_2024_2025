#include "main.h"

double xrobot::prevL,xrobot::prevR,xrobot::prevAngle,xrobot::odomX,xrobot::odomY;

pros::Task *xrobot::odomTask;

void xrobot::updatePos(){
    double currL=get_avg_pos(left_mg)/360*constants.wheelDia, // because they're in degrees and we want inches
           currR=get_avg_pos(right_mg)/360*constants.wheelDia,
           currAngle=sinertial.get_rotation();
    double dL=currL-prevL,
           dR=currR-prevR,
           dS=horizTracker.get_position()/3.6*constants.trackDia, // because it's in centidegrees and we want inches
           dAngle=currAngle-prevAngle;
    prevL=currL;
    prevR=currR;
    prevAngle=currAngle;
    double dX,dY;
    if(dAngle==0){
        dX=dS;
        dY=dR;
    }else{
        dX=(2*dsin(dAngle/2))*((dL+dR)/2/dAngle);
        dY=(2*dsin(dAngle/2))*(dS/dAngle+constants.hWheelOffset);
    }
    odomX+=dX;
    odomY+=dY;
    horizTracker.reset_position();
}

void xrobot::initTracking(){
    horizTracker.reset_position();
    odomTask = new pros::Task {[=]{
        while(true){
            updatePos();
            pros::delay(10);
        }
    }};
}