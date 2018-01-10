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
    Vector2D point1, point2, target;
    int state,flag;
};
#endif // TACTICTEST3_H
