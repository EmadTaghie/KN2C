#include "tactictest.h"

TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    sTest = new SkillKick(wm);
//    emad
 //   flag = 0;
//    //emad
    state = 0;
    counter = rand()%3;
}

RobotCommand TacticTest::getCommand()
{
//    if(wm->gs != wm->gs_last)
//        counter = rand()%3; //for recieving
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
//    int speed = 4;
//    int real = 20;
//    wm->ourRobot[id].Status = AgentStatus::RecievingPass;
//    Vector2D space(1000,0);
//    Vector2D ourPenaltiSpot(-2500,-2250);
//    Vector2D oppPenaltiSpot(-2500,2250);
//    Vector2D penaltiSpot;
//    int ID;
//    if(id == 1)
//    {
//        penaltiSpot = oppPenaltiSpot;
//        ID = 1;
//    }
//    else
//    {
//        penaltiSpot = ourPenaltiSpot;
//        ID = -1;
//    }
//    Vector2D vectPoints[3] = {penaltiSpot, penaltiSpot - space, penaltiSpot + space};
//    Vector2D intersectRecive;
//    Line2D recivingLine(penaltiSpot, penaltiSpot + space);
//    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
//    target = vectPoints[counter];
//    intersectRecive = ballMoveMent.intersection(recivingLine);
//    if(wm->ball.vel.loc.length() > 0.5 && intersectRecive.x > Field::MinX && intersectRecive.x < Field::MaxX)
//        target = intersectRecive;
//    else if(wm->ball.pos.loc.y > (vectPoints[0].y - 500) && wm->ball.pos.loc.y < (vectPoints[0].y + 500) && wm->ball.vel.loc.length() < 0.5){
//        switch(state){
//        case 0:
//            rc.useNav = true;
//            rc.isBallObs = true;
//            target = wm->ball.pos.loc + Vector2D(0,ID*150);
//            qDebug() << "varede sharte beine pnolti target x="<< target.x << " y=" << target.y;
//            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
//                state = 1;
//        case 1:
//            speed = 0.1;
//            rc.useNav = false;
//            rc.isBallObs = false;
//            target = wm->ball.pos.loc + Vector2D(0, ID*(BALL_RADIUS + ROBOT_RADIUS -real));
//            if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150 || (wm->ball.pos.loc.y*ID > wm->ourRobot[id].pos.loc.y*ID))
//                state = 0;
//        }
//    }
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
//    rc.fin_pos.loc = target;
//    rc.maxSpeed = speed;

    //***************************************************************************************************************************************************
    if(wm->ball.pos.loc.y == 0) counter = rand()%3;
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
    int ID;
    int real = 0;
    int speed = 4;
    if(id == 1) ID = -1;
    else ID = 1;
    int recieverRobot = 4 - id;
    Vector2D penaltiSpot(-2500, ID*2250);
    Vector2D space(500, 0);
    Vector2D vectPoints[3] = {penaltiSpot, penaltiSpot - space, penaltiSpot + space};
    Ray2D ballMovement(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Line2D recieveLine(vectPoints[0], vectPoints[1]);
    Vector2D intersectRecieve = ballMovement.intersection(recieveLine);
    Vector2D behindTheBall = (wm->ourRobot[id].pos.loc - wm->ourRobot[recieverRobot].pos.loc).setLengthVector(150);
    Vector2D atTheBall = (wm->ourRobot[id].pos.loc - wm->ourRobot[recieverRobot].pos.loc).setLengthVector(BALL_RADIUS + ROBOT_RADIUS - real);
    if(wm->ourRobot[id].Status == AgentStatus::Kicking && wm->ball.isValid){
        if(intersectRecieve != Vector2D(0,0) && wm->ball.vel.loc.length() > 0.2 && intersectRecieve.x > Field::MinX && intersectRecieve.x < 0) target = intersectRecieve;
        else if(wm->ball.pos.loc.x > Field::MinX && wm->ball.pos.loc < 0){
            if(wm->kn->findNearestTo(wm->ourRobot[id].pos.loc).isEmpty()) target = (wm->ball.pos.loc + Vector2D(0, ID*(BALL_RADIUS + ROBOT_RADIUS - real)));
            else if(wm->ball.vel.loc.length() < 0.2){
                recieverRobot = wm->kn->findNearestTo(wm->ourRobot[id].pos.loc).takeFirst();
                switch(state){
                case 0:
                    rc.useNav = true;
                    rc.isBallObs = true;
                    target = wm->ball.pos.loc + behindTheBall;
                    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50)) state = 1;
                    break;
                case 1:
                    rc.useNav = false;
                    rc.isBallObs = false;
                    speed = 1;
                    target = wm->ball.pos.loc + atTheBall;
                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 200) state = 0;
                    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 25)) state = 2;
                    break;
                case 2:
                    rc.fin_pos.dir = (wm->ourRobot[recieverRobot].pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
                    rc.kickspeedx = 50;
                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 200){
                        state = 0;
                        rc.kickspeedx = 0;
                        break;
                    }
                }
            }
            else target = vectPoints[counter];
        }
        else target = vectPoints[counter];
    }
    else if(wm->ourRobot[id].Status == AgentStatus::RecievingPass && wm->ball.isValid){
        if(intersectRecieve != Vector2D(0,0) && wm->ball.vel.loc.length() > 0.2 && intersectRecieve.x > Field::MinX && intersectRecieve.x < 0) target = intersectRecieve;
        else if(wm->ball.vel.loc.length() < 0.2 && wm->ball.pos.loc.y * ID > 0){
            if(wm->kn->findNearestTo(wm->ourRobot[id].pos.loc).isEmpty()) target = (wm->ball.pos.loc + Vector2D(0, ID*(BALL_RADIUS + ROBOT_RADIUS - real)));
            else if(wm->ball.pos.loc.x > Field::MinX && wm->ball.pos.loc.x < 0){
                recieverRobot = wm->kn->findNearestTo(wm->ourRobot[id].pos.loc).takeFirst();
                switch(state){
                case 0:
                    rc.useNav = true;
                    rc.isBallObs = true;
                    target = wm->ball.pos.loc + behindTheBall;
                    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50)) state = 1;
                    break;
                case 1:
                    rc.useNav = false;
                    rc.isBallObs = false;
                    speed = 1;
                    target = wm->ball.pos.loc + atTheBall;
                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 200) state = 0;
                    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 25)) state = 2;
                    break;
                case 2:
//                    rc.fin_pos.dir = (wm->ourRobot[recieverRobot].pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
//                    rc.kickspeedx = 50;
                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 200){
                        state = 0;
//                        rc.kickspeedx = 0;
                        break;
                    }
                }
            }
            else target = vectPoints[counter];
        }
        else target = vectPoints[counter];
    }
    else{
        target = vectPoints[counter]*ID;
    }
        rc.fin_pos.loc = target;
        rc.maxSpeed = speed;
        return rc;
}
