#include "tactictest3.h"
TacticTest3::TacticTest3(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest3", worldmodel, parent)
{
    //sTest = new SkillKick(wm);
    state=0;
}
RobotCommand TacticTest3::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    int sectionLengthY, sectionLengthX, i, index;
    int counter = 0;
        Line2D golieGreneralLine (Field::ourGoalPost_L , Field::ourGoalPost_R);
                Line2D ballMoveMent (wm->ball.pos.loc , wm->ball.pos_predicted.loc);
                Line2D lineR (wm->ball.pos.loc , Field::ourGoalPost_R);
                Line2D lineL (wm->ball.pos.loc , Field::ourGoalPost_L);
                Circle2D dangerArea ((Field::ourGoalPost_L + Field::ourGoalPost_R)/2 , 600);
                Vector2D intersectPointL1 , intersectPointL2 , intersectPointR1 , intersectPointR2 , intersectGolieGeneral;
                Vector2D goalPoints[20][2];
                Vector2D sumVect(0,0);
                intersectGolieGeneral = ballMoveMent.intersection(golieGreneralLine);
                for(i=0; i < 20; i++) goalPoints[i][1] = Vector2D(1,1);
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
                        else{

                        }
         //                qDebug() <<"dar sharte aval";
                        qDebug()<<" R pos : "<< wm->ourRobot[1].pos.loc.x << ", "<< wm->ourRobot[1].pos.loc.y;
                            qDebug()<<"R pos.loc.dir : "<< wm->ourRobot[1].pos.loc.dir().degree(); //)<<" "<<wm->ball.pos.loc.y;
                            qDebug()<<"R pos.dir : "<<AngleDeg::rad2deg(wm->ourRobot[1].pos.dir);
                            qDebug()<<"Ball vel loc dir :" << wm->ball.vel.loc.dir().degree();
                            qDebug()<<"Ball vel dir :" << wm->ball.vel.dir;
                    }
                    else
                    {
                        sectionLengthY = (point1.y - point2.y)/20;
                        sectionLengthX = (point1.x - point2.x)/20;
                        for(i = 0; i < 20; i++) goalPoints[i][0] = point2 + Vector2D(sectionLengthX*i, sectionLengthY*i);
                        for(index = 1; index < 5; index++)
                            for(i = 0; i < 20; i++){
                                Ray2D targetRay(wm->ball.pos.loc, goalPoints[i][0]);
                                Circle2D RobotCircle(wm->ourRobot[index].pos.loc, ROBOT_RADIUS);
                                Vector2D RobotIntersect1, RobotIntersect2;
                                RobotCircle.intersection(targetRay, &RobotIntersect1, &RobotIntersect2);
                                if(RobotIntersect1 != Vector2D(0,0) || RobotIntersect2 != Vector2D(0,0))
                                    goalPoints[i][1] = Vector2D(0,1);
                            }
                        for(i = 0; i < 20; i++)
                        {
                            qDebug() << "goal points "<<i<<" x = "<<goalPoints[i][1].x;
                            if(goalPoints[i][1].x == 1){
                                sumVect += goalPoints[i][0];
                                counter++;
                            }
                        }
                        target = sumVect/counter;

                        qDebug() << "sum x =" <<sumVect.x<<" y ="<<sumVect.y;
                         qDebug() <<"dar sharte dovom";
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

    return rc;
}
