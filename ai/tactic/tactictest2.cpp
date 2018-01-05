#include "tactictest2.h"
TacticTest2::TacticTest2(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest2", worldmodel, parent)
{
    sTest = new SkillKick(wm);
    state = 0;
    counter = 0;
}
Vector2D sortVec(Vector2D vect1 , Vector2D vect2){
    if (vect1.x > vect2.x)
        return vect1;
    else
        return vect2;
}
RobotCommand TacticTest2::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
    int speed = 4;
    int real = 0;
    int reciver;
    if(id == 1) reciver = 3;
    else if(id == 3) reciver = 1;
    if(wm->gs != wm->gs_last)
        counter = rand()%3;
    wm->ourRobot[id].Status = AgentStatus::Kicking;
    Vector2D space(1000,0);
    Vector2D ourPenaltiSpot(-2500,-2250);
    Vector2D oppPenaltiSpot(-2500,2250);
    Vector2D penaltiSpot;
    Circle2D behindBall(wm->ball.pos.loc, 150);
    Circle2D atTheBall(wm->ball.pos.loc, BALL_RADIUS + ROBOT_RADIUS - real);
    Vector2D intersect1, intersect2;
    Vector2D vectPoints[3] = {penaltiSpot, penaltiSpot - space, penaltiSpot + space};
    Vector2D intersectRecive;
    Line2D recivingLine(penaltiSpot, penaltiSpot + space);
    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Line2D reciveriToBall (wm->ourRobot[reciver].pos.loc, penaltiSpot);
    if(id == 1) penaltiSpot = oppPenaltiSpot;
    else penaltiSpot = ourPenaltiSpot;
    target = vectPoints[counter];
    intersectRecive = ballMoveMent.intersection(recivingLine);
    if(wm->ball.vel.loc.length() > 0.5 && intersectRecive.x > Field::MinX && intersectRecive.x < 0) target = intersectRecive;
    else if(wm->ball.vel.loc.length() < 0.5 && wm->ball.pos.loc.y < penaltiSpot.y + 500 && wm->ball.pos.loc.y > penaltiSpot.y - 500 && wm->ball.pos.loc.x > Field::MinX && wm->ball.pos.loc.x < 0){
        switch(state){
        case 0:
            rc.useNav = true;
            rc.isBallObs = true;
            behindBall.intersection(reciveriToBall, &intersect1, &intersect2);
            if((intersect1 - penaltiSpot).length() < (intersect2 - penaltiSpot).length()) target = intersect1;
            else target = intersect2;
            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50)) state = 1;
            break;
        case 1:
            rc.fin_pos.dir = (wm->ourRobot[reciver].pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
            rc.useNav = false;
            rc.isBallObs = false;
            atTheBall.intersection(reciveriToBall, &intersect1, &intersect2);
            if((intersect1 - penaltiSpot).length() < (intersect2 - penaltiSpot).length()) target = intersect1;
            else target = intersect2;
            if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150) state = 0;
            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 25)) state = 2;
            break;
        case 2:
            rc.fin_pos.dir = (wm->ourRobot[reciver].pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
            rc.kickspeedx = 5;
            if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150) {
                state = 0;
                rc.kickspeedx = 0;
            }
        }
    }
   rc.fin_pos.loc = target;
   rc.maxSpeed = speed;
    return rc;
}



