#ifndef TACTICTEST2_H
#define TACTICTEST2_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticTest2: public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
private:
    Skill *sTest;
    int state;
    int counter;
    Vector2D point1,point2,target;
//    vector <Circle2D> obs;
//    void addObs();
//    Vector2D KN2CNav(Vector2D target);
//    bool isAnyObsInTheWay(Vector2D start , Vector2D end , Vector2D * up , Vector2D * bot);

};
#endif // TACTICTEST2_H
