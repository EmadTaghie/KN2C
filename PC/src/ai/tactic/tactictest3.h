#ifndef TACTICTEST3_H
#define TACTICTEST3_H
#include "tactic.h"
class TacticTest3 : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest3(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:
    Vector2D TDmid,TUmid,fixedPoint;
    int state,flag;
    int angle;
    int x,y;
    int opRobot[6]={0};
};
#endif // TACTICTEST3_H
