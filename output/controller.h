#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controller_struct.h"
#include <fstream>
#include "QDebug"
using namespace std;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);
    ControllerResult calc(ControllerInput &ci);

private:
    QTime timer;

    RobotSpeed calcRobotSpeed_main(ControllerInput &ci);
    MotorSpeed calcSimul(RobotSpeed rs, ControllerInput &ci);

private:

    Vector2D err0,err1;
    Vector2D u1;
    Vector2D derived0,derived1;
    Vector2D integral;
    Vector2D last_setpoint ;
    //kamin
    Vector2D LinearSpeed;
    Vector2D LinearSpeed_past;
    //kamout
    double wu1,wu1_last,wintegral,werr0,werr1;
    double wderived0,wderived1;


    ///////////////////////////////////////////////////////////////new controller
    double wp,wi,wd;
    Vector2D p,i,d,i_near,i_far;
    int fault_counter;
    ///////////////////////////////////////////////////////////////


    int stateCTRL;

    ofstream out;
};

#endif // CONTROLLER_H
