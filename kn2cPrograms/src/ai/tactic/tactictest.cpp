    #include "tactictest.h"
#include <cmath>
#include <stdlib.h>
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    sTest = new SkillKick(wm);
    state = 0;
    counter = 0;
}
RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
//    Circle2D circle(Vector2D(0,0),1000);
//    Vector2D intersect1 , intersect2;
//    if(state == 0){
//        Line2D targetFinder(Vector2D(0,0) , counter);
//        circle.intersection(targetFinder , &intersect1 , &intersect2);
//        if((wm->ourRobot[0].pos.loc - intersect1).length() < (wm->ourRobot[0].pos.loc - intersect2).length())
//            target = intersect1;
//        if((wm->ourRobot[0].pos.loc - intersect1).length() > (wm->ourRobot[0].pos.loc - intersect2).length())
//            target = intersect2;
//        counter++;
//        if(counter > 180)
//            counter = -counter;
//        state =1;
//    }
//    else if(state == 1){
//        rc.fin_pos.loc = target;
//        if((wm->ourRobot[0].pos.loc - rc.fin_pos.loc).length() < 50)
//            state = 0;
//    }
// //    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[0].pos.loc).dir().radian();
//    rc.maxSpeed=4;
    //*****************************************************************************************************************************************//
    //darvaze ban

    Line2D golieGreneralLine (Field::ourGoalPost_L , Field::ourGoalPost_R);
            Line2D ballMoveMent (wm->ball.pos.loc , wm->ball.pos_predicted.loc);
            Line2D lineR (wm->ball.pos.loc , Field::ourGoalPost_R);
            Line2D lineL (wm->ball.pos.loc , Field::ourGoalPost_L);
            Circle2D dangerArea ((Field::ourGoalPost_L + Field::ourGoalPost_R)/2 , 600);
            Vector2D intersectPointL1 , intersectPointL2 , intersectPointR1 , intersectPointR2 , intersectGolieGeneral;
            intersectGolieGeneral = ballMoveMent.intersection(golieGreneralLine);
            if(wm->ball.pos.loc.x > Field::ourGoalCenter.x){
                if(/*(wm->ball.pos.loc - Field::ourGoalCenter).length() < 600*/wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && wm->ball.vel.loc.length() < 0.7){
                    switch (state){
                    case 0:
                        rc.useNav =true;
                        target = wm->ball.pos.loc + Vector2D(-150 ,0);
                        if((wm->ourRobot[id].pos.loc - target).length() < 50)
                            state = 1;
     //                    qDebug() << "dar halate aval";
                        break;
                    case 1:
                        rc.useNav = false;
                        target = wm->ball.pos.loc - Vector2D(BALL_RADIUS + ROBOT_RADIUS, 0);
                        qDebug() << "sorate toop" <<wm->ball.vel.loc.length();
                        if((wm->ourRobot[id].pos.loc - target).length() < 100)
                        state = 2;
                        if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150)
                            state = 0;
     //                    qDebug() << "dar halate dovom";
                        break;
                    case 2:
                        rc.kickspeedx    = 10;
                        qDebug() << "shooooooooot";
                        if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).length() > 150){
         //                    rc.kickspeedz = 0;
                            qDebug() << "final";
                            rc.kickspeedx = 0;
                            state = 0;
                        }
     //                    qDebug() << "dar halate svom";
                    }
                }
                else{
            if(intersectGolieGeneral.y < Field::ourGoalPost_L.y && intersectGolieGeneral.y > Field::ourGoalPost_R.y &&
               wm->ball.vel.loc.dir().degree() < 0 &&
                    intersectGolieGeneral.isValid() && wm->ball.vel.loc.length() > 0.2){
                Line2D goalieChangedLine(point1 , point2);
                target = goalieChangedLine.intersection(ballMoveMent);
            }
            else{
                dangerArea.intersection(lineR , &intersectPointR1 , &intersectPointR2);
                dangerArea.intersection(lineL , &intersectPointL1 , &intersectPointL2);
                if(intersectPointL1.x > intersectPointL2.x)
                    point1 = intersectPointL1;
                else
                    point1 = intersectPointL2;
                if(intersectPointR1.x > intersectPointR2.x)
                    point2 = intersectPointR1;
                else
                    point2 = intersectPointR2;
                if((wm->oppRobot[1].pos.loc - wm->ball.pos.loc).length() < 200 && (AngleDeg::rad2deg(wm->oppRobot[1].pos.dir) > 90 || AngleDeg::rad2deg(wm->oppRobot[1].pos.dir) < -90)){
                    Line2D stopLine(wm->ball.pos.loc , wm->oppRobot[1].pos.loc);
                    Line2D goalieChangedLine(point1 , point2);
                    Vector2D stopPoint = stopLine.intersection(goalieChangedLine);
                    if(stopPoint.y <point1.y && stopPoint.y >point2.y)
                    target = stopPoint;
                    else
                        target = (point1 + point2)/2;
     //                qDebug() <<"dar sharte aval";
                    qDebug()<<" R pos : "<< wm->ourRobot[1].pos.loc.x << ", "<< wm->ourRobot[1].pos.loc.y;
                        qDebug()<<"R pos.loc.dir : "<< wm->ourRobot[1].pos.loc.dir().degree(); //)<<" "<<wm->ball.pos.loc.y;
                        qDebug()<<"R pos.dir : "<<AngleDeg::rad2deg(wm->ourRobot[1].pos.dir);
                        qDebug()<<"Ball vel loc dir :" << wm->ball.vel.loc.dir().degree();
                        qDebug()<<"Ball vel dir :" << wm->ball.vel.dir;
                }
                else
                {
                    target = (point1 + point2)/2;
     //                qDebug() <<"dar sharte dovom";
                }
            }
            }
            }
            if((wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree() > -90 && (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree() < 90 ){
                rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
     //            qDebug() << "dar sharte daraje aval  " << (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().degree();
            }
            else{
                rc.fin_pos.dir = (wm->ball.pos.loc - Field::ourGoalCenter).dir().radian();
     //            qDebug() << "dar sharte daraje dovom";
            }
            rc.fin_pos.loc = target;
            rc.maxSpeed = 4;
    //*************************************************************************************************************************************************************//
//    //moraba

//    switch (state) {
//    case 0:
//        target = Vector2D(0 , 0);
//        if((target - wm->ourRobot[id].pos.loc).length() < 100)
//            state = 1;
//        break;
//    case 1:
//        target = Vector2D (1000 , 0);
//        if((target - wm->ourRobot[id].pos.loc).length() < 100)
//            state = 2;
//        break;
//    case 2:
//        target = Vector2D (1000 , 1000);
//        if((target - wm->ourRobot[id].pos.loc).length() < 100)
//            state = 3;
//        break;
//    case 3:
//        target = Vector2D (0 , 1000);
//        if((target - wm->ourRobot[id].pos.loc).length() < 100)
//            state = 0;
//        break;
//    }
//    rc.fin_pos.loc = target;
//    rc.maxSpeed = 4;
    //***************************************************************************************************************************************************************//
//    int real = -30;
//    int diviner = 3;
//    Vector2D space(0,1500);
//    Vector2D predictRobatLocation = (wm->ourRobot[1].vel.loc*diviner + wm->ourRobot[1].pos.loc);
//    Vector2D vectPoints[3] = {Field::ourPenaltySpot, Field::ourPenaltySpot - space, Field::ourPenaltySpot + space};
//    Line2D recivingLine(Field::ourPenaltySpot, Field::ourPenaltySpot + space);
//    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
//    Circle2D behindBall(wm->ball.pos.loc, 150);
//    Circle2D atTheBall(wm->ball.pos.loc, BALL_RADIUS + ROBOT_RADIUS);
//    Vector2D intersect1, intersect2;
//    if(wm->ourRobot[0].Status == AgentStatus::FollowingBall)
//        target = Vector2D(0,0);
//    else if(wm->ourRobot[0].Status == Kicking){
//        if(wm->ball.pos.loc.x > (Field::ourPenaltySpot.x - 500) && wm->ball.pos.loc.x < (Field::ourPenaltySpot.x + 500) && wm->ball.vel.loc.length() < 0.7){
//            if(predictRobatLocation.y > Field::MinY || predictRobatLocation.y < Field::MaxY){
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
//                    if((wm->ourRobot[0].pos.loc - target).length() < 50)
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
//                    if((wm->ourRobot[0].pos.loc - target).length() > 150)
//                        state = 0;
//                    if((wm->ourRobot[0].pos.loc - target).length() < 25)
//                        state = 2;
//                    break;
//                case 2:
//                    rc.kickspeedx = 5;
//                    if((wm->ball.pos.loc - wm->ourRobot[0].pos.loc).length() > 150 || !wm->ball.isValid){
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
//                    if((wm->ourRobot[0].pos.loc - target).length() < 50)
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
//                    if((wm->ourRobot[0].pos.loc - target).length() > 150)
//                        state = 0;
//                    if((wm->ourRobot[0].pos.loc - target).length() < 25)
//                        state = 2;
//                    break;
//                case 2:
//                    rc.kickspeedx = 5;
//                    if((wm->ball.pos.loc - wm->ourRobot[0].pos.loc).length() > 150 || !wm->ball.isValid){
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
//    else if(wm->ourRobot[0].Status == RecievingPass){
//        target = recivingLine.intersection(ballMoveMent);
//        if(target.y < Field::MinY || target.y > Field::MaxY || wm->ball.vel.loc.length() < 0.5)
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
//        if((wm->ball.pos.loc.x < Field::ourPenaltySpot.x + 500) && (wm->ball.pos.loc.x > Field::ourPenaltySpot.x - 500) && wm->ball.vel.loc.length() < 0.5){
//            switch(state){
//            case 0:
//                rc.useNav = true;
//                rc.isBallObs = true;
//                target = wm->ball.pos.loc - Vector2D(150,0);
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
//                    state = 1;
//            case 1:
//                rc.useNav = false;
//                rc.isBallObs = false;
//                target = wm->ball.pos.loc - Vector2D(BALL_RADIUS + ROBOT_RADIUS - real, 0);
//                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
//                    state = 0;
//            }
//        }
//    }
//    else{
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
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[0].pos.loc).dir().radian();
//    rc.maxSpeed = 4;
    return rc;
}
