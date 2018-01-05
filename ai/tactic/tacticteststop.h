#ifndef TACTICTESTSTOP_H
#define TACTICTESTSTOP_H
#include "tactic.h"
#include "geom2/shape2d.h"
class tacticTestStop: public Tactic
{
    Q_OBJECT
public:
    explicit tacticTestStop(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
private:
    SkillKick *sTest;
    int state;
    int counter;
    Vector2D point1,point2,target;
};

#endif // TACTICTESTSTOP_H
