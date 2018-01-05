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
        rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();
    int real = -20;
    int diviner = 3;
    Vector2D oppPenaltyPos(-2500,2250);
    Vector2D space(1500,0);
    Vector2D predictRobatLocation = (wm->ourRobot[3].vel.loc*diviner + wm->ourRobot[3].pos.loc);
    Vector2D vectPoints[3] = {oppPenaltyPos, oppPenaltyPos - space, oppPenaltyPos + space};
    Line2D recivingLine(oppPenaltyPos, oppPenaltyPos + space);
    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Circle2D behindBall(wm->ball.pos.loc, 150);
    Circle2D atTheBall(wm->ball.pos.loc, BALL_RADIUS + ROBOT_RADIUS - 20);
    Vector2D intersect1, intersect2;
    if(wm->ourRobot[1].Status == AgentStatus::FollowingBall)
    {target = Vector2D(-2500,0);
    qDebug() <<"in the foloowing status";
    }
    else if(wm->ourRobot[1].Status == Kicking){
        qDebug() <<"in the kciking status";
        if(wm->ball.pos.loc.y > (oppPenaltyPos.y - 500) && wm->ball.pos.loc.y < (oppPenaltyPos.y + 500) && wm->ball.vel.loc.length() < 0.7){
            if(predictRobatLocation.x > Field::MinX && predictRobatLocation.x < 0){
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
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
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
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[1].pos.loc).dir().radian();
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
        qDebug() <<"in the reciving status";
        if(wm->ball.pos.loc.length() > 0.5)
        target = recivingLine.intersection(ballMoveMent);
        if(target.x < Field::MinX || target.x > 0 || !wm->ball.isValid || wm->ball.vel.loc.length() < 0.5)
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
        if((wm->ball.pos.loc.y < oppPenaltyPos.y + 500) && (wm->ball.pos.loc.y > oppPenaltyPos.y - 500) && wm->ball.vel.loc.length() < 0.5){
            switch(state){
            case 0:
                rc.useNav = true;
                rc.isBallObs = true;
                target = wm->ball.pos.loc + Vector2D(0,150);
                qDebug() << "varede sharte beine pnolti target x="<< target.x << " y=" << target.y;
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 1;
            case 1:
                rc.useNav = false;
                rc.isBallObs = false;
                target = wm->ball.pos.loc + Vector2D(0, BALL_RADIUS + ROBOT_RADIUS + real);
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 0;
            }
        }
        qDebug() << "target x = "<< target.x << " y=" << target.y;
        qDebug() << "robot y = "<< wm->ourRobot[1].pos.loc.x << " y=" << wm->ourRobot[1].pos.loc.y;
    }
    else{
        qDebug() <<"in the else status";
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
    rc.fin_pos.loc = target;
    rc.maxSpeed = 4;
    return rc;
    //***********************************************************
//    switch(state){
//    case 0:
//        rc.fin_pos.loc = Vector2D(-2000,0);
//        if((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            state=1;
//        break;
//    case 1:
//        rc.fin_pos.loc = Vector2D(-2000,-2500);
//        if((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            state=0;
//    }
//    rc.maxSpeed = 4;
    //rc.kickspeedx = 255;
    //return rc;
//    Circle2D circle (Vector2D (-2400,0) , 500);
//    Vector2D intersect1 ,intersect2;
//    if(state == 0){
//        Line2D targetFinder(Vector2D (-2500,0) , counter);
//        circle.intersection(targetFinder , &intersect1 , &intersect2);
//        if((wm->ourRobot[1].pos.loc - intersect1).length() < (wm->ourRobot[1].pos.loc - intersect2).length())
//            target = intersect1;
//        else
// //        if((wm->ourRobot[1].pos.loc - intersect2).length() < (wm->ourRobot[1].pos.loc - intersect1).length())
//            target = intersect2;
//        counter += 10;
//        if(counter >= 180)
//            counter = -counter;
//        state = 1;
//        qDebug() << "dar sharte 1 counter = " <<counter;
//    }
//    else if(state == 1){
//        rc.fin_pos.loc = target;
//        if((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            state = 0;
//        qDebug() << "dar sharte 2";
//    }
//    rc.maxSpeed = 4;
//    qDebug() <<"dar teste man";
//    rc.fin_pos.dir = (Vector2D (-2500,0) - target ).dir().radian();
//    rc.fin_pos.loc = target;
    //darvaze bane behine start
//    Vector2D golieL = Field::ourGoalPost_L;
//    Vector2D golieR = Field::ourGoalPost_R;
//    Line2D golieGeneralLine (golieL , golieR);
//    Line2D ballMovement (wm->ball.pos.loc , wm->ball.pos_predicted.loc);
//    Line2D lineR (wm->ball.pos.loc , golieR);
//    Line2D lineL (wm->ball.pos.loc , golieL);
//    Circle2D dangerArea ((golieL + golieR)/2 , 600);
//    Vector2D intersectGolieGeneral , intersectionPointL1 , intersectionPointL2 , intersectionPointR1 , intersectionPointR2 , target;
//    intersectGolieGeneral = ballMovement.intersection(golieGeneralLine);
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();
//    if(wm->ball.pos.loc.x > golieR.x){
//        if(intersectGolieGeneral.y < golieL.y && intersectGolieGeneral.y > golieR.y &&
//           intersectGolieGeneral.isValid() && wm->ball.vel.loc.length() > 0.2 &&
//           wm->ball.vel.loc.dir().degree() < 0 && wm->ball.vel.loc.dir().degree() > -180){
//            Line2D golieChangedline(point1, point2);
//            target = golieChangedline.intersection(ballMovement);
//            rc.fin_pos.loc = target;
//            rc.maxSpeed = 4;
//        }
//        else{
//            dangerArea.intersection(lineR , &intersectionPointR1 , &intersectionPointR2);
//            dangerArea.intersection(lineL , &intersectionPointL1 , &intersectionPointL2);
//            point1 = sortVec(intersectionPointL1 , intersectionPointL2);
//            point2 = sortVec(intersectionPointR1 , intersectionPointR2);
//            rc.fin_pos.loc = (point1 + point2)/2;
//            rc.maxSpeed = 4;
//        }
//    }
//    else{
//        rc.fin_pos.loc = (golieL + golieR)/2;
//        rc.maxSpeed = 4;
//    }
//    qDebug()<<" R pos : "<< wm->ourRobot[1].pos.loc.x << ", "<< wm->ourRobot[1].pos.loc.y;
//    qDebug()<<"R pos.loc.dir : "<< wm->ourRobot[1].pos.loc.dir().degree(); //)<<" "<<wm->ball.pos.loc.y;
//    qDebug()<<"R pos.dir : "<<AngleDeg::rad2deg(wm->ourRobot[1].pos.dir);
//    qDebug()<<"Ball vel loc dir :" << wm->ball.vel.loc.dir().degree();
//    qDebug()<<"Ball vel dir :" << wm->ball.vel.dir;
    //darvaze bane behine end
    //darvaze computere khodam
//    Line2D golieGreneralLine (Field::ourGoalPost_L , Field::ourGoalPost_R);
//        Line2D ballMoveMent (wm->ball.pos.loc , wm->ball.pos_predicted.loc);
//        Line2D lineR (wm->ball.pos.loc , Field::ourGoalPost_R);
//        Line2D lineL (wm->ball.pos.loc , Field::ourGoalPost_L);
//        Circle2D dangerArea ((Field::ourGoalPost_L + Field::ourGoalPost_R)/2 , 600);
//        Vector2D intersectPointL1 , intersectPointL2 , intersectPointR1 , intersectPointR2 , intersectGolieGeneral;
//        intersectGolieGeneral = ballMoveMent.intersection(golieGreneralLine);
//        if(wm->ball.pos.loc.x > Field::ourGoalCenter.x){
//            if(/*(wm->ball.pos.loc - Field::ourGoalCenter).length() < 600*/wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && wm->ball.vel.loc.length() < 0.7){
//                switch (state){
//                case 0:
//                    rc.useNav =true;
//                    target = wm->ball.pos.loc + Vector2D(-150 ,0);
//                    if((wm->ourRobot[id].pos.loc - target).length() < 50)
//                        state = 1;
// //                    qDebug() << "dar halate aval";
//                    break;
//                case 1:
//                    rc.useNav = false;
//                    rc.isBallObs = 1;
//                    target = wm->ball.pos.loc - Vector2D(BALL_RADIUS + ROBOT_RADIUS -20, 0);
//                    qDebug() << "sorate toop" <<wm->ball.vel.loc.length();
//                    if((wm->ourRobot[id].pos.loc - target).length() < 20)
//                    state = 2;
//                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150)
//                        state = 0;
// //                    qDebug() << "dar halate dovom";
//                    break;
//                case 2:
//                    rc.isBallObs = 0;
//     //                rc.kickspeedz = 10;
//                    qDebug() << "shooooooooot";
//                    rc.kickspeedx = 100;

//                    if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150){
//     //                    rc.kickspeedz = 0;
//                        qDebug() << "final";
//                        rc.kickspeedx = 0;
//                        state = 0;
//                    }
// //                    qDebug() << "dar halate svom";
//                }
//            }
//            else{
//        if(intersectGolieGeneral.y < Field::ourGoalPost_L.y && intersectGolieGeneral.y > Field::ourGoalPost_R.y &&
//           wm->ball.vel.loc.dir().degree() < 0 &&
//                intersectGolieGeneral.isValid() && wm->ball.vel.loc.length() > 0.2){
//            Line2D goalieChangedLine(point1 , point2);
//            target = goalieChangedLine.intersection(ballMoveMent);
//        }
//        else{
//            dangerArea.intersection(lineR , &intersectPointR1 , &intersectPointR2);
//            dangerArea.intersection(lineL , &intersectPointL1 , &intersectPointL2);
//            if(intersectPointL1.x > intersectPointL2.x)
//                point1 = intersectPointL1;
//            else
//                point1 = intersectPointL2;
//            if(intersectPointR1.x > intersectPointR2.x)
//                point2 = intersectPointR1;
//            else
//                point2 = intersectPointR2;
//            if((wm->oppRobot[1].pos.loc - wm->ball.pos.loc).length() < 200 && (AngleDeg::rad2deg(wm->oppRobot[1].pos.dir) > 90 || AngleDeg::rad2deg(wm->oppRobot[1].pos.dir) < -90)){
//                Line2D stopLine(wm->ball.pos.loc , wm->oppRobot[1].pos.loc);
//                Line2D goalieChangedLine(point1 , point2);
//                Vector2D stopPoint = stopLine.intersection(goalieChangedLine);
//                if(stopPoint.y <point1.y && stopPoint.y >point2.y)
//                target = stopPoint;
//                else
//                    target = (point1 + point2)/2;
// //                qDebug() <<"dar sharte aval";
//                qDebug()<<" R pos : "<< wm->ourRobot[1].pos.loc.x << ", "<< wm->ourRobot[1].pos.loc.y;
//                    qDebug()<<"R pos.loc.dir : "<< wm->ourRobot[1].pos.loc.dir().degree(); //)<<" "<<wm->ball.pos.loc.y;
//                    qDebug()<<"R pos.dir : "<<AngleDeg::rad2deg(wm->ourRobot[1].pos.dir);
//                    qDebug()<<"Ball vel loc dir :" << wm->ball.vel.loc.dir().degree();
//                    qDebug()<<"Ball vel dir :" << wm->ball.vel.dir;
//            }
//            else
//            {
//                target = (point1 + point2)/2;
// //                qDebug() <<"dar sharte dovom";
//            }
//        }
//        }
//        }
//        if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree() > -90 && (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree() < 90 ){
//            rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
// //            qDebug() << "dar sharte daraje aval  " << (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree();
//        }
//        else{
//            rc.fin_pos.dir = (wm->ball.pos.loc - Field::ourGoalCenter).dir().radian();
// //            qDebug() << "dar sharte daraje dovom";
//        }
//        rc.fin_pos.loc = target;
//        rc.maxSpeed = 4;
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





