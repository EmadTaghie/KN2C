#include "tactictest2.h"
TacticTest2::TacticTest2(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest2", worldmodel, parent)
{
    state = 0;
    counter = 0;
}
RobotCommand TacticTest2::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
//    switch(state){
//    case 0:
//        rc.fin_pos.loc = Vector2D(0,0);
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, Vector2D(0,0),50))
//            state = 1;
//        break;
//    case 1:
//        rc.fin_pos.loc = Field::oppGoalCenter;
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, Field::oppGoalCenter,50))
//            state = 0;
//        break;
//    }
    //*************************************************************************************************************************//
    int real = -30;
    int diviner = 3;
    Vector2D space(0,1500);
    Vector2D predictRobatLocation = (wm->ourRobot[0].vel.loc*diviner + wm->ourRobot[0].pos.loc);
    Vector2D vectPoints[3] = {Field::oppPenaltySpot, Field::oppPenaltySpot - space, Field::oppPenaltySpot + space};
    Line2D recivingLine(Field::oppPenaltySpot, Field::oppPenaltySpot + space);
    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Circle2D behindBall(wm->ball.pos.loc, 150);
    Circle2D atTheBall(wm->ball.pos.loc, BALL_RADIUS + ROBOT_RADIUS);
    Vector2D intersect1, intersect2;
    if(wm->ourRobot[1].Status == AgentStatus::FollowingBall)
        target = Vector2D(0,0);
    else if(wm->ourRobot[1].Status == Kicking){
        if(wm->ball.pos.loc.x > (Field::oppPenaltySpot.x - 500) && wm->ball.pos.loc.x < (Field::oppPenaltySpot.x + 500) && wm->ball.vel.loc.length() < 0.7){
            if(predictRobatLocation.y > Field::MinY || predictRobatLocation.y < Field::MaxY){
                Line2D predictLine(predictRobatLocation, wm->ball.pos.loc);
                switch(state){
                case 0:
                    rc.useNav = true;
                    rc.isBallObs=true;
                    behindBall.intersection(predictLine, &intersect1, &intersect2);
                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
                        target = intersect1;
                    else
                        target = intersect2;
                    if((wm->ourRobot[1].pos.loc - target).length() < 50)
                        state = 1;
                    break;
                case 1:
                    rc.useNav = false;
                    rc.isBallObs = false;
                    atTheBall.intersection(predictLine, &intersect1, &intersect2);
                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
                        target = intersect1;
                    else
                        target = intersect2;
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.kickspeedx = 5;
                    if((wm->ball.pos.loc - wm->ourRobot[1].pos.loc).length() > 150 || !wm->ball.isValid){
                        rc.kickspeedx = 0;
                        state = 0;
                    }
                    break;
                }
            }
            else{
                diviner = -diviner;
                Line2D predictLine(predictRobatLocation, wm->ball.pos.loc);
                switch(state){
                case 0:
                    rc.useNav = true;
                    rc.isBallObs=true;
                    behindBall.intersection(predictLine, &intersect1, &intersect2);
                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
                        target = intersect1;
                    else
                        target = intersect2;
                    if((wm->ourRobot[1].pos.loc - target).length() < 50)
                        state = 1;
                    break;
                case 1:
                    rc.useNav = false;
                    rc.isBallObs = false;
                    atTheBall.intersection(predictLine, &intersect1, &intersect2);
                    if((intersect1 - predictRobatLocation).length() > (intersect2 - predictRobatLocation).length())
                        target = intersect1;
                    else
                        target = intersect2;
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.kickspeedx = 5;
                    if((wm->ball.pos.loc - wm->ourRobot[1].pos.loc).length() > 150 || !wm->ball.isValid){
                        rc.kickspeedx = 0;
                        state = 0;
                    }
                    break;
                }
            }
        }
        else{
            switch(counter){
            case 0:
                target = vectPoints[0];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                break;
            case 1:
                target = vectPoints[1];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                break;
            case 2:
                target = vectPoints[2];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                break;
            }
        }

    }
    else if(wm->ourRobot[1].Status == RecievingPass){
        target = recivingLine.intersection(ballMoveMent);
        if(target.y < Field::MinY || target.y > Field::MaxY || wm->ball.vel.loc.length() < 0.5)
            switch(counter){
            case 0:
                target = vectPoints[0];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                qDebug() << "varede sharte aval";
                break;
            case 1:
                target = vectPoints[1];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                qDebug() << "varede sharte dovom ";
                break;
            case 2:
                target = vectPoints[2];
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                    counter = rand()%3;
                qDebug() << "varede sharte sevom ";
                break;
            }
        if((wm->ball.pos.loc.x < Field::oppPenaltySpot.x + 500) && (wm->ball.pos.loc.x > Field::oppPenaltySpot.x - 500) && wm->ball.vel.loc.length() < 0.5){
            switch(state){
            case 0:
                rc.useNav = true;
                rc.isBallObs = true;
                target = wm->ball.pos.loc - Vector2D(150,0);
                qDebug() << "varede sharte beine pnolti target x="<< target.x << " y=" << target.y;
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 1;
            case 1:
                rc.useNav = false;
                rc.isBallObs = false;
                target = wm->ball.pos.loc - Vector2D(BALL_RADIUS + ROBOT_RADIUS - real, 0);
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 0;
            }
        }
        qDebug() << "target x = "<< target.x << " y=" << target.y;
        qDebug() << "robot y = "<< wm->ourRobot[1].pos.loc.x << " y=" << wm->ourRobot[1].pos.loc.y;
    }
    else{
        switch(counter){
        case 0:
            target = vectPoints[0];
            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                counter = rand()%3;
            break;
        case 1:
            target = vectPoints[1];
            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                counter = rand()%3;
            break;
        case 2:
            target = vectPoints[2];
            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
                counter = rand()%3;
            break;
        }
    }
//    Vector2D space(0,1500);
//    Vector2D vectPoints[3] = {Field::oppPenaltySpot, Field::oppPenaltySpot - space, Field::oppPenaltySpot + space};
//    switch(counter){
//    case 0:
//        target = vectPoints[0];
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//            counter = rand()%3;
//        break;
//    case 1:
//        target = vectPoints[1];
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//            counter = rand()%3;
//        break;
//    case 2:
//        target = vectPoints[2];
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target,50))
//            counter = rand()%3;
//        break;
//    }
//    rc.fin_pos.loc = target;
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[0].pos.loc).dir().radian();
//    rc.maxSpeed = 4;

    rc.fin_pos.loc = target;
    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();
    rc.maxSpeed = 4;
    return rc;
}
//void TacticTest2::addObs(){
//    obs.clear();
//    for(int i = 1 ; i <8 ; i++){
//        if(i != id){
//            Circle2D our(wm->ourRobot[i].pos.loc , ROBOT_RADIUS * 1.5);
//            obs.push_back(our);
//        }
//        Circle2D opp(wm->oppRobot[i].pos.loc , ROBOT_RADIUS * 1.5);
//        obs.push_back(opp);
//    }
//}
//Vector2D TacticTest2::KN2CNav(Vector2D target){
//    addObs();
//}
//bool TacticTest2::isAnyObsInTheWay(Vector2D start, Vector2D end, Vector2D *up, Vector2D *bot){
//    Segment2D way(start , end);
//    bool intersect = false;
//    for(int i = 0 ; i <  obs.size() ; i++){
//        //if(obs.at(i))
//        Circle2D t;

//    }
//}





