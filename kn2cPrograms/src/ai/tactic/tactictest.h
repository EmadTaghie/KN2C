#ifndef TACTICTEST_H
#define TACTICTEST_H
#include "tactic.h"
#define DangerDist 300
class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:
    Skill *sTest;
    int state;
    int counter;
    Vector2D point1,point2,target;
};
#endif // TACTICTEST_H

