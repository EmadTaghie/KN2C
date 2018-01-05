#include "tacticteststop.h"

tacticTestStop::tacticTestStop(WorldModel *worldmodel, QObject *parent) :
    Tactic("tacticteststop", worldmodel, parent)
{
    sTest = new SkillKick(wm);
    state = 0;
    counter = 0;
}
RobotCommand tacticTestStop::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.useNav = true;
    rc.isBallObs = true;
    rc.fin_pos.loc = Vector2D(-2500,0);
    return rc;
}
