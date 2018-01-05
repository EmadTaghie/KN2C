#include "tactictest3.h"
TacticTest3::TacticTest3(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest3", worldmodel, parent)
{
    //sTest = new SkillKick(wm);
    flag=0;
    state=-1;
    x=-500;
    y=0;
    opRobot[6]={0};

}
RobotCommand TacticTest3::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    return rc;
}
