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
    rc.fin_pos.loc = Vector2D(-2500,0);
//        rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();
//    int real = -20;
//    int diviner = 3;
//    Vector2D oppPenaltyPos(-2500,2250);
//    Vector2D space(1500,0);
//    Vector2D predictRobatLocation = (wm->ourRobot[3].vel.loc*diviner + wm->ourRobot[3].pos.loc);
//    Vector2D vectPoints[3] = {oppPenaltyPos, oppPenaltyPos - space, oppPenaltyPos + space};
//    Line2D recivingLine(oppPenaltyPos, oppPenaltyPos + space);
//    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
//    Circle2D behindBall(wm->ball.pos.loc, 150);
//    Circle2D atTheBall(wm->ball.pos.loc, BALL_RADIUS + ROBOT_RADIUS - 20);
//    Vector2D intersect1, intersect2;
//    if(wm->ourRobot[1].Status == AgentStatus::FollowingBall)
//    {target = Vector2D(-2500,0);
//    qDebug() <<"in the foloowing status";
//    }
//    else if(wm->ourRobot[1].Status == Kicking){
//        qDebug() <<"in the kciking status";
//        if(wm->ball.pos.loc.y > (oppPenaltyPos.y - 500) && wm->ball.pos.loc.y < (oppPenaltyPos.y + 500) && wm->ball.vel.loc.length() < 0.7){
//            if(predictRobatLocation.x > Field::MinX && predictRobatLocation.x < 0){
//                Line2D predictLine(predictRobatLocation, wm->ball.pos.loc);
//                switch(state){
//                case 0:
//                    rc.useNav = true;
//                    rc.isBallObs=true;
//                    behindBall.intersection(predictLine, &intersect1, &intersect2);
//                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
//                        target = intersect1;
//                    else
//                        target = intersect2;
//                    if((wm->ourRobot[1].pos.loc - target).length() < 50)
//                        state = 1;
//                    break;
//                case 1:
//                    rc.useNav = false;
//                    rc.isBallObs = false;
//                    atTheBall.intersection(predictLine, &intersect1, &intersect2);
//                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
//                        target = intersect1;
//                    else
//                        target = intersect2;
//                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
//                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
//                        state = 0;
//                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
//                        state = 2;
//                    break;
//                case 2:
//                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
//                    rc.kickspeedx = 50;
//                    if((wm->ball.pos.loc - wm->ourRobot[1].pos.loc).length() > 150 || !wm->ball.isValid){
//                        rc.kickspeedx = 0;
//                        state = 0;
//                    }
//                    break;
//                }
//            }
//            else{
//                diviner = -diviner;
//                Line2D predictLine(predictRobatLocation, wm->ball.pos.loc);
//                switch(state){
//                case 0:
//                    rc.useNav = true;
//                    rc.isBallObs=true;
//                    behindBall.intersection(predictLine, &intersect1, &intersect2);
//                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
//                        target = intersect1;
//                    else
//                        target = intersect2;
//                    if((wm->ourRobot[1].pos.loc - target).length() < 50)
//                        state = 1;
//                    break;
//                case 1:
//                    rc.useNav = false;
//                    rc.isBallObs = false;
//                    atTheBall.intersection(predictLine, &intersect1, &intersect2);
//                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
//                        target = intersect1;
//                    else
//                        target = intersect2;
//                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
//                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
//                        state = 0;
//                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
//                        state = 2;
//                    break;
//                case 2:
//                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
//                    rc.kickspeedx = 5;
//                    if((wm->ball.pos.loc - wm->ourRobot[1].pos.loc).length() > 150 || !wm->ball.isValid){
//                        rc.kickspeedx = 0;
//                        state = 0;
//                    }
//                    break;
//                }
//            }
//        }
//        else{
//            switch(counter){
//            case 0:
//                target = vectPoints[0];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                break;
//            case 1:
//                target = vectPoints[1];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                break;
//            case 2:
//                target = vectPoints[2];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                break;
//            }
//        }

//    }
//    else if(wm->ourRobot[1].Status == RecievingPass){
//        qDebug() <<"in the reciving status";
//        if(wm->ball.pos.loc.length() > 0.5)
//        target = recivingLine.intersection(ballMoveMent);
//        if(target.x < Field::MinX || target.x > 0 || !wm->ball.isValid || wm->ball.vel.loc.length() < 0.5)
//            switch(counter){
//            case 0:
//                target = vectPoints[0];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                qDebug() << "varede sharte aval";
//                break;
//            case 1:
//                target = vectPoints[1];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                qDebug() << "varede sharte dovom ";
//                break;
//            case 2:
//                target = vectPoints[2];
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                    counter = rand()%3;
//                qDebug() << "varede sharte sevom ";
//                break;
//            }
//        if((wm->ball.pos.loc.y < oppPenaltyPos.y + 500) && (wm->ball.pos.loc.y > oppPenaltyPos.y - 500) && wm->ball.vel.loc.length() < 0.5){
//            switch(state){
//            case 0:
//                rc.useNav = true;
//                rc.isBallObs = true;
//                target = wm->ball.pos.loc + Vector2D(0,150);
//                qDebug() << "varede sharte beine pnolti target x="<< target.x << " y=" << target.y;
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
//                    state = 1;
//            case 1:
//                rc.useNav = false;
//                rc.isBallObs = false;
//                target = wm->ball.pos.loc + Vector2D(0, BALL_RADIUS + ROBOT_RADIUS + real);
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
//                    state = 0;
//            }
//        }
//        qDebug() << "target x = "<< target.x << " y=" << target.y;
//        qDebug() << "robot y = "<< wm->ourRobot[1].pos.loc.x << " y=" << wm->ourRobot[1].pos.loc.y;
//    }
//    else{
//        qDebug() <<"in the else status";
//        switch(counter){
//        case 0:
//            target = vectPoints[0];
//            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                counter = rand()%3;
//            break;
//        case 1:
//            target = vectPoints[1];
//            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                counter = rand()%3;
//            break;
//        case 2:
//            target = vectPoints[2];
//            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//                counter = rand()%3;
//            break;
//        }
//    }
//    rc.fin_pos.loc = target;
//    rc.maxSpeed = 0.1;
    return rc;
}



