#include "tactictest.h"
#include "constants.h"
//#include <cmath>
//#define darM1x -2500
//#define darM1y -2500
//#define darM2x -1500
//#define darM2y -2500
//#define darM3x -1500
//#define darM3y -1500
//#define darM4x -2500
//#define darM4y -1500
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    sTest = new SkillKick(wm);
//    emad
 //   flag = 0;
//    //emad
    state = 0;
    counter = 0;
}
//static Vector2D t,t1,t2;
//emad
//Vector2D sortVec(Vector2D vect1 , Vector2D vect2){
//    if (vect1.x > vect2.x)
//        return vect1;
//    else
//        return vect2;
//}

//emad

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
//    qDebug() <<"varede tactic mishavad";
    int real = 20;
    int diviner = 3;
    Vector2D ourPenaltiSpot(-2500,-2250);
    Vector2D space(1000,0);
    Vector2D predictRobatLocation = (wm->ourRobot[1].vel.loc*diviner + wm->ourRobot[1].pos.loc);
    Vector2D vectPoints[3] = {ourPenaltiSpot, ourPenaltiSpot - space, ourPenaltiSpot + space};
    Line2D recivingLine(ourPenaltiSpot, ourPenaltiSpot + space);
    Line2D ballMoveMent(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Circle2D behindBall(wm->ball.pos.loc, 150);
    Circle2D atTheBall(wm->ball.pos.loc, (BALL_RADIUS + ROBOT_RADIUS));
    Vector2D intersect1, intersect2;
//    qDebug() <<"varede tactic1 mishavad";
    if(wm->ourRobot[3].Status == AgentStatus::FollowingBall)
    {target = Vector2D(-2500,0);
//    qDebug() <<"varede follow mishavad";
    }
    else if(wm->ourRobot[3].Status == Kicking){
        if(wm->ball.pos.loc.y > (ourPenaltiSpot.y - 500) && wm->ball.pos.loc.y < (ourPenaltiSpot.y + 500) && wm->ball.vel.loc.length() < 0.7){
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
                    if((wm->ourRobot[3].pos.loc - target).length() < 50)
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
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[3].pos.loc).dir().radian();
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[3].pos.loc).dir().radian();
                    rc.kickspeedx = 5;
                    if((wm->ball.pos.loc - wm->ourRobot[3].pos.loc).length() > 150 || !wm->ball.isValid){
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
                    if((wm->ourRobot[3].pos.loc - target).length() < 50)
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
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[3].pos.loc).dir().radian();
                    if((wm->ourRobot[1].pos.loc - target).length() > 150)
                        state = 0;
                    if((wm->ourRobot[1].pos.loc - target).length() < 25)
                        state = 2;
                    break;
                case 2:
                    rc.fin_pos.dir = (predictRobatLocation - wm->ourRobot[3].pos.loc).dir().radian();
                    rc.kickspeedx = 5;
                    if((wm->ball.pos.loc - wm->ourRobot[3].pos.loc).length() > 150 || !wm->ball.isValid){
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
    else if(wm->ourRobot[3].Status == RecievingPass){
        target = recivingLine.intersection(ballMoveMent);
        if(target.x < Field::MinX || target.x > 0 || wm->ball.vel.loc.length() < 0.5 || !wm->ball.isValid)
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
        if((wm->ball.pos.loc.y < ourPenaltiSpot.y + 500) && (wm->ball.pos.loc.y > ourPenaltiSpot.y - 500) && wm->ball.vel.loc.length() < 0.5){
            switch(state){
            case 0:
                rc.useNav = true;
                rc.isBallObs = true;
                target = wm->ball.pos.loc - Vector2D(0,150);
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 1;
            case 1:
                rc.useNav = false;
                rc.isBallObs = false;
                target = wm->ball.pos.loc - Vector2D(0, BALL_RADIUS + ROBOT_RADIUS - real);
                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc, target, 50))
                    state = 0;
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
//    qDebug() << " target  x= " <<target.x<<" y= "<<target.y;
    rc.fin_pos.loc = target;
    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[3].pos.loc).dir().radian();
    rc.maxSpeed = 4;
    //************************************************
//    qDebug()<<"armin is here"<<endl;
//    rc.fin_pos.loc = Vector2D (-2000 , -2000);
//    rc.maxSpeed = 4;



    //moraba
//        switch( state )
//        {
//             case 0:
//                rc.fin_pos.loc = Vector2D( -2500 , -1500 );
//                if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state = 1 ;}
//               break;
//            case 1:
//                rc.fin_pos.loc = Vector2D ( -2500 , -500 );
//                if((wm->ourRobot[id].pos.loc - rc.fin_pos.loc).length()<100 ){ state = 2 ;}
//                break;
//            case 2:
//                rc.fin_pos.loc = Vector2D ( -1500 , -500 );
//                if((wm->ourRobot[id].pos.loc - rc.fin_pos.loc).length()<100){ state = 3 ; }
//                break;
//            case 3:
//               rc.fin_pos.loc = Vector2D ( -1500 , -1500 );
//                if((wm->ourRobot[id].pos.loc - rc.fin_pos.loc).length()<100){ state = 0 ; }
//                break;
//        }
//        rc.fin_pos.dir = (rc.fin_pos.loc - wm->ourRobot[id].pos.loc ).dir().radian();
//        rc.maxSpeed = 4;
    //moraba
    /******************************************************/
    //dayere
//        Vector2D markaz (-1500 , -1500 );
//        Circle2D c (markaz , 500 );
//        AngleDeg a (20 * state );
//        Line2D l (markaz , a.degree() );
//        Vector2D intersect1 , intersect2 ;
//        c.intersection( l , &intersect1 , & intersect2 );
//        if (wm->ourRobot[id].pos.loc.dist(intersect1) < wm->ourRobot[id].pos.loc.dist(intersect2) )
//        {
//            rc.fin_pos.loc = intersect1 ;
//            if ( wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc , rc.fin_pos.loc , 100 ) )
//            {
//                state = (state + 1 )%18 ;
//            }
//        }
//        else
//        {
//             rc.fin_pos.loc = intersect2 ;
//             if (  wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc , rc.fin_pos.loc , 100 ) )
//             {
//                 state = (state + 1 )%18 ;
//             }
//         }
//        rc.fin_pos.dir = (rc.fin_pos.loc - wm->ourRobot[id].pos.loc ).dir().radian();
//        rc.maxSpeed = 4;
    //dayere
    /***************************************************/
    //daravze ban bedoon  e robot e harif
//    Line2D ballToGoalieLeft ( wm->ball.pos.loc , Field::ourGoalPost_L );
//    Line2D ballToGoalieRight ( wm->ball.pos.loc , Field::ourGoalPost_R );
//    Vector2D intersect_left , intersect1 , intersect2 ;
//    Field::ourDefenceCircle.intersection( ballToGoalieLeft , &intersect1 , &intersect2 );
//    if ( intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//    {
//        intersect_left = intersect1;
//    }
//    else
//    {
//        intersect_left = intersect2;
//    }
//    Vector2D intersect_Right;
//    Field::ourDefenceCircle.intersection( ballToGoalieRight , &intersect1 , &intersect2 );
//    if (intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//    {
//        intersect_Right = intersect1;
//    }
//    else
//    {
//        intersect_Right = intersect2;
//    }
//    Vector2D min_Mid;
//    if ( intersect_left.dist( Field::ourGoalPost_L ) < intersect_Right.dist( Field::ourGoalPost_R ))
//    {
//        min_Mid = ( intersect_left + Field::ourGoalPost_L )/2;
//    }
//    else
//    {
//        min_Mid = ( intersect_Right + Field::ourGoalPost_R )/2;
//    }
//    Vector2D temp ;
//    temp.y = min_Mid.y -10;
//    temp.x = min_Mid.x;
//    Line2D goalie_Line ( min_Mid , temp );
//    Vector2D fin_goalie_L = goalie_Line.intersection( ballToGoalieLeft );
//    Vector2D fin_goalie_R = goalie_Line.intersection( ballToGoalieRight );
//    rc.fin_pos.loc = ( fin_goalie_L + fin_goalie_R ) / 2;
//    Vector2D ball_next_pos = wm->ball.pos.loc + wm->ball.vel.loc;
//    Line2D ball_Line ( wm->ball.pos.loc , ball_next_pos );
//    Vector2D intersect_Goal = goalie_Line.intersection( ball_Line );
//    if ( intersect_Goal.y < fin_goalie_L.y && intersect_Goal.y > fin_goalie_R.y && wm->ball.vel.loc.length() > 0.2 )
//    {
//        rc.fin_pos.loc = intersect_Goal;
//    }
//    rc.maxSpeed = 4 ;
    //darvaze ban bedoon e robot e harif
    /*********************************************************************************/
    //darvaze ban ba robot e harif
//        Line2D ballToGoalieLeft ( wm->ball.pos.loc , Field::ourGoalPost_L );
//        Line2D ballToGoalieRight ( wm->ball.pos.loc , Field::ourGoalPost_R );
//        Vector2D intersect_left , intersect1 , intersect2 ;
//        Field::ourDefenceCircle.intersection( ballToGoalieLeft , &intersect1 , &intersect2 );
//        if ( intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//        {
//            intersect_left = intersect1;
//        }
//        else
//        {
//            intersect_left = intersect2;
//        }
//        Vector2D intersect_Right;
//        Field::ourDefenceCircle.intersection( ballToGoalieRight , &intersect1 , &intersect2 );
//        if (intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//        {
//            intersect_Right = intersect1;
//        }
//        else
//        {
//            intersect_Right = intersect2;
//        }
//        Vector2D min_Mid;
//        if ( intersect_left.dist( Field::ourGoalPost_L ) < intersect_Right.dist( Field::ourGoalPost_R ))
//        {
//            min_Mid = ( intersect_left + Field::ourGoalPost_L )/2;
//        }
//        else
//        {
//            min_Mid = ( intersect_Right + Field::ourGoalPost_R )/2;
//        }
//        Vector2D temp ;
//        temp.y = min_Mid.y -10;
//        temp.x = min_Mid.x;
//        Line2D goalie_Line (min_Mid, temp);
//        Vector2D fin_goalie_L = goalie_Line.intersection( ballToGoalieLeft );
//        Vector2D fin_goalie_R = goalie_Line.intersection( ballToGoalieRight );
//        rc.fin_pos.loc = ( fin_goalie_L + fin_goalie_R ) / 2;
//        qDebug() << " ID : "<<id;
//        Line2D ball_Line (wm->ball.pos.loc, AngleDeg::rad2deg(wm->oppRobot[id].pos.dir));
//        Vector2D intersect_Goal = goalie_Line.intersection( ball_Line );
//        if ( intersect_Goal.y < fin_goalie_L.y && intersect_Goal.y > fin_goalie_R.y)// && wm->ball.vel.loc.length() > 0.2 )
//        {
//            rc.fin_pos.loc = intersect_Goal;
//        }
//        rc.maxSpeed = 4 ;
    //darvaze ban ba robot e harif
    /******************************************************/

    //darvaze ban vaghti ke ba nav shoot mizanad
//        Line2D ballToGoalieLeft ( wm->ball.pos.loc , Field::ourGoalPost_L );
//        Line2D ballToGoalieRight ( wm->ball.pos.loc , Field::ourGoalPost_R );
//        Vector2D intersect_left , intersect1 , intersect2;
//        Field::ourDefenceCircle.intersection( ballToGoalieLeft , &intersect1 , &intersect2 );
//        if ( intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//        {
//            intersect_left = intersect1;
//        }
//        else
//        {
//            intersect_left = intersect2;
//        }
//        Vector2D intersect_Right;
//        Field::ourDefenceCircle.intersection( ballToGoalieRight , &intersect1 , &intersect2 );
//        if (intersect1.x > Field::MinX && intersect1.x < Field::MaxX && intersect1.y > Field::MinY && intersect2.y < Field::MaxY )
//        {
//            intersect_Right = intersect1;
//        }
//        else
//        {
//            intersect_Right = intersect2;
//        }
//        Vector2D min_Mid;
//        if ( intersect_left.dist( Field::ourGoalPost_L ) < intersect_Right.dist( Field::ourGoalPost_R ))
//        {
//            min_Mid = ( intersect_left + Field::ourGoalPost_L )/2;
//        }
//        else
//        {
//            min_Mid = ( intersect_Right + Field::ourGoalPost_R )/2;
//        }
//        Vector2D temp ;
//        temp.y = min_Mid.y -10 ;
//        temp.x = min_Mid.x ;
//        Line2D goalie_Line ( min_Mid , temp ) ;
//        Vector2D fin_goalie_L = goalie_Line.intersection( ballToGoalieLeft ) ;
//        Vector2D fin_goalie_R = goalie_Line.intersection( ballToGoalieRight );
//        rc.fin_pos.loc = ( fin_goalie_L + fin_goalie_R ) / 2;
//        Vector2D ball_next_pos = wm->ball.pos.loc + wm->ball.vel.loc;
//        Line2D ball_Line ( wm->ball.pos.loc , ball_next_pos );
//        Vector2D intersect_Goal = goalie_Line.intersection( ball_Line );
//        if ( intersect_Goal.y < fin_goalie_L.y && intersect_Goal.y > fin_goalie_R.y && wm->ball.vel.loc.length() > 0.2 )
//        {
//            rc.fin_pos.loc = intersect_Goal;
//        }
//        if ( ( (wm->ball.pos.loc.x - Field::ourDefenceCircle.center().x) * (wm->ball.pos.loc.x - Field::ourDefenceCircle.center().x)
//               + (wm->ball.pos.loc.y - Field::ourDefenceCircle.center().y) * (wm->ball.pos.loc.y - Field::ourDefenceCircle.center().y) <
//               Field::ourDefenceCircle.radius() * Field::ourDefenceCircle.radius() ) )
//        {
//            Vector2D temp1 ;
//            temp.x = wm->ball.pos.loc.x - 1 ; //
//            temp.y = wm->ball.pos.loc.y ;
//            Line2D ball_To_GoalieLine ( wm->ball.pos.loc , temp1 );
////            Vector2D temp2 ;
////            temp2.x = wm->ourRobot[id].pos.loc.x - 10 ;
////            temp2.y = wm->ourRobot[id].pos.loc.y ;
////            Line2D robot_To_GoalieLine ( wm->ourRobot[id].pos.loc , temp2 );
//            Vector2D dist1;// , dist2 ;
//            Line2D primary_Goalie_Line ( Field::ourDefPost_L , Field::ourDefPost_R );
//            dist1 = primary_Goalie_Line.intersection( ball_To_GoalieLine );
////            dist2 = primary_Goalie_Line.intersection( robot_To_GoalieLine );
//            rc.fin_pos.loc = ( wm->ball.pos.loc + dist1 )/2 ;
//            if ( state == 0 && wm->kn->ReachedToPos( wm->ourRobot[id].pos.loc , rc.fin_pos.loc , 100 ) )
//            {
//                state = 1 ;
//                qDebug()<<" state =0  ";
//            }
//            rc.useNav = true ;
//            if ( state == 1 )
//            {
//               rc.fin_pos.loc = wm->ball.pos.loc ;
//               if ( wm->kn->ReachedToPos( wm->ourRobot[id].pos.loc , rc.fin_pos.loc , BALL_RADIUS + ROBOT_RADIUS ) )
//               {
//                    qDebug()<<" shoooooooooooooooooooooooooot !!!!!!!!!!!!!!!! ";
//                    rc.kickspeedx = 3;
//                    //state = 3 ;
//               }
//               rc.useNav = false;
//            }
//        }
//        qDebug() <<" State : "<< state <<" , Use Nav : "<<rc.useNav;
//        rc.kickspeedx = 0;
//        rc.maxSpeed = 4 ;




    //sadaf's code
    //        rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
    //        Vector2D v1 (-1500 , -2500);
    //        Vector2D v2 (-2500 , -2500);
    //        Line2D l1 (v1 , v2);
    //        Vector2D b = wm->ball.pos.loc + wm->ball.vel.loc;
    //        Line2D l2 (wm->ball.pos.loc , b);
    //        Vector2D vt = l1.intersection(l2);
    //        if((vt.x < -1500 && vt.x>-2500)&&(wm->ball.vel.loc.length() >0.2))
    //        {
    //            rc.fin_pos.loc = vt;
    //            rc.maxSpeed = 4;
    //        }
    //        else
    //        {
    //            Vector2D v (-2000 , -2500 );
    //            rc.fin_pos.loc = v;
    //        }

    //end sadaf's code

    //1396/8/15
/*     rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
    Vector2D VectDarvazeR (-1500 ,-2500 ); 
    Vector2D VectDarvazeL (-2500 , -2500 );
    Vector2D VectDarvazeMid ( -2000 , -2500 );
    Circle2D CircleDarvaze  (VectDarvazeMid , 500);
    Vector2D vball = wm->ball.pos.loc;
    Vector2D VectBall = wm->ball.pos.loc + wm->ball.vel.loc;
    qDebug()<<" R pos : "<< wm->ourRobot[1].pos.loc.x << ", "<< wm->ourRobot[1].pos.loc.y;
    qDebug()<<"R pos.loc.dir : "<< wm->ourRobot[1].pos.loc.dir().degree(); //)<<" "<<wm->ball.pos.loc.y;
    qDebug()<<"R pos.dir : "<<AngleDeg::rad2deg(wm->ourRobot[1].pos.dir);
    qDebug()<<"Ball vel loc dir :" << wm->ball.vel.loc.dir().degree();
    qDebug()<<"Ball vel dir :" << wm->ball.vel.dir;
    Line2D LinBall (VectBall,vball);
    Vector2D c;
    if(vball.x<VectDarvazeMid.x && vball.y>VectDarvazeMid.y)//samt e chap e zamin
    {
        if(flag == 0)//ja giri
        {

             Line2D BallToDarvazeR (VectBall , VectDarvazeR);
             Vector2D taghato1 , taghato2 , taghato;
             CircleDarvaze.intersection(BallToDarvazeR , &taghato1 , &taghato2);
             if(taghato1==VectDarvazeR)
             {
                  taghato = taghato2;
             }
             else
             {
                  taghato = taghato1;
             }
             Vector2D MidBall = (taghato+VectDarvazeR)/2;
             Line2D GolieL (MidBall , VectDarvazeL);
             Vector2D i = GolieL.intersection(LinBall);
             Vector2D y = (taghato + VectDarvazeL)/2;
             rc.fin_pos.loc=y;
             rc.maxSpeed = 4;

             if(i.x>-2500 && i.x < MidBall.x && i.y > -2500 && i.y<MidBall.y && wm->ball.vel.loc.length() > 0.2)
               {
                 flag=1;
                 StopPoint=i;
             }
       }
       else if(flag == 1)//darvaze bani
       {
            Vector2D c=StopPoint;
            Line2D GolieL(StopPoint,VectDarvazeL);
            Vector2D taghato,taghato1,taghato2;
            CircleDarvaze.intersection(GolieL,&taghato1,&taghato2);
            if(taghato1==VectDarvazeR)
            {
                 taghato = taghato2;
            }
            else
            {
                 taghato = taghato1;
            }
            Vector2D i=GolieL.intersection(LinBall);
            if(i.x>-2500 && i.x<taghato.x && i.y>-2500 &&i.y<taghato.y && wm->ball.vel.loc.length()>0.2)
                c=i;
            else
                flag=0;
            rc.fin_pos.loc=c;
            rc.maxSpeed=4;
       }
    }

    else if(vball.x>-2000 && vball.y>-2500)//samt e rast zamin
    {
        if(flag == 0)//ja giri
        {

             Line2D BallToDarvazeL (VectBall , VectDarvazeL);
             Vector2D taghato1 , taghato2 , taghato;
             CircleDarvaze.intersection(BallToDarvazeL , &taghato1 , &taghato2);
             if(taghato1==VectDarvazeL)
             {
                  taghato = taghato2;
             }
             else
             {
                  taghato = taghato1;
             }
             Vector2D MidBall = (taghato+VectDarvazeL)/2;
             Line2D GolieL (MidBall , VectDarvazeR);
             Vector2D i=GolieL.intersection(LinBall);
             Vector2D y = (taghato + VectDarvazeR)/2;
             rc.fin_pos.loc=y;
             rc.maxSpeed = 4;
             if(i.x<-2000 && i.x > MidBall.x && i.y > -2500 && i.y<MidBall.y && wm->ball.vel.loc.length() > 0.2)
               {
                 flag=1;
                 StopPoint=i;
             }
       }
       else if(flag == 1)//darvaze bani
       {
            Vector2D c=StopPoint;
            Line2D GolieL(StopPoint,VectDarvazeR);
            Vector2D taghato,taghato1,taghato2;
            CircleDarvaze.intersection(GolieL,&taghato1,&taghato2);
            if(taghato1==VectDarvazeL)
            {
                 taghato = taghato2;
            }
            else
            {
                 taghato = taghato1;
            }
            Vector2D i=GolieL.intersection(LinBall);
            if(i.x<-2000 && i.x > taghato.x && i.y > -2500 && i.y<taghato.y && wm->ball.vel.loc.length() > 0.2)
                c=i;
            else
                flag=0;
            rc.fin_pos.loc=c;
             rc.maxSpeed=4;
       }
    }
    else{
        rc.fin_pos.loc=VectDarvazeMid;
        rc.maxSpeed=4;
    }*/
    //1396/8/15



//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
//    Vector2D vdarvazer (-1500 , -2500);
//    Vector2D vdarvazel (-2500 , -2500);
//    Vector2D vdarvazemid (-2000,-2500);
//    Circle2D cd  (vdarvazemid , 500);
//    Vector2D b = wm->ball.pos.loc + wm->ball.vel.loc;
//    Line2D lb (wm->ball.pos.loc , b);
//    Vector2D vball = wm->ball.pos.loc;
//    if(vball.x<-2010 && vball.y >-2500)
//    {
//        Line2D l1 (vball , vdarvazer);
//        //Line2D l2(vball , vdarvazel);
//        Vector2D vtaghato (-1647,-2147);
//        Line2D lt(vtaghato , vdarvazel);
//        Vector2D v = lt.intersection(l1);
//        //Line2D g (v , v2);
//       Vector2D i = lt.intersection(lb);
//       if(i.x >-2500 && i.x<v.x && i.y >-2500 && i.y <v.y && wm->ball.vel.loc.length() >0.2)
//       {
//           rc.fin_pos.loc=i;
//           rc.maxSpeed = 4;
//       }
//       else
//       {
//           Vector2D mid = (vdarvazel+v)/2;
//           rc.fin_pos.loc = mid;
//           rc.maxSpeed  =4;
//       }

//    }
//    else if(vball.x > -1990 && vball.y >-2500)
//    {
//        //Line2D l1 (vball , vdarvazer);
//        Line2D l2(vball , vdarvazel);
//        Vector2D vt (-2353,-2147);
//        Line2D lt(vt , vdarvazer);
//        Vector2D v = lt.intersection(l2);
//        //Line2D g (v , v2);
//       Vector2D i = lt.intersection(lb);
//       if(i.x <-1500 && i.x<v.x && i.y >-2500 && i.y <v.y && wm->ball.vel.loc.length() >0.2 )
//       {
//           rc.fin_pos.loc=i;
//           rc.maxSpeed = 4;
//       }
//       else
//       {
//           Vector2D mid = (vdarvazer+v)/2;
//           rc.fin_pos.loc = mid;
//           rc.maxSpeed  =4;
//       }

//    }
//    else
//    {
//        rc.fin_pos.loc = vdarvazemid;
//        rc.maxSpeed = 4;
//    }



   //darvaze behine
//    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
//        Vector2D vdarvazer (-1500 , -2500);
//        Vector2D vdarvazel (-2500 , -2500);
//        Vector2D vdarvazemid (-2000,-2500);
//        Circle2D cd  (vdarvazemid , 500);
//        Vector2D b = wm->ball.pos.loc + wm->ball.vel.loc;
//        Line2D lb (wm->ball.pos.loc , b);
//        Vector2D vball = wm->ball.pos.loc;
//        if(vball.x<-2010 && vball.y>-2500)//samt e chap e zamin
//        {
//            Line2D l1 (vball , vdarvazer);
//            Vector2D t1 , t2 , taghato;
//            cd.intersection(l1 , &t1 , &t2);
//            if(t2==vdarvazer)
//            {
//                taghato = t1;
//            }
//            else
//            {//        Vector2D tir1(darM1x,darM1y);
    //        Vector2D tir2(darM2x,darM2y);
    //        Vector2D tir3(darM3x,darM3y);
    //        Vector2D tir4(darM4x,darM4y);
    //        rc.maxSpeed=2;
    //        qDebug()<<flag;
    //        if(flag==0)
    //        {
    //            rc.fin_pos.loc=tir1;
    //            rc.maxSpeed=1;
    //            if( (wm->ourRobot[id].pos.loc - tir1).length() <50)
    //                flag=1;
    //        }
    //        else if(flag==1)
    //        {
    //            rc.fin_pos.loc=tir2;
    //            rc.maxSpeed=1;
    //            if( (wm->ourRobot[id].pos.loc - tir2).length() <50)
    //                flag=2;
    //        }
    //        else if(flag==2)
    //        {
    //            rc.fin_pos.loc=tir3;
    //            rc.maxSpeed=1;
    //            if( (wm->ourRobot[id].pos.loc - tir3).length() <50)
    //               flag=3;
    //        }
    //        else if(flag==3)
    //        {
    //            rc.fin_pos.loc=tir4;
    //            rc.maxSpeed=1;
    //            if( (wm->ourRobot[id].pos.loc - tir4).length() <50)
    //                flag=0;
    //        }
    //        else //unnecessary
    //        {
    //            rc.fin_pos.loc=tir1;
    //            rc.maxSpeed=1;
    //        }
//                taghato = t2;
//            }
//            Vector2D midball = (vball+vdarvazer)/2;
//            double MIDy=midball.y,TAy=taghato.y;
//            qDebug()<<"MIDy= "<<MIDy<<"TAy "<<TAy;
//            if(MIDy >TAy)//dakhel e dayere
//            {
//                qDebug()<<"Hooooooooooooooooooooy, midball.y: "<<midball.y << "taghato.y: "<< taghato.y;
//                Line2D lt (vdarvazel , midball);
//                Vector2D i = lt.intersection(lb);
//                if(i.x>-2500 && i.x<midball.x && i.y>-2500 && i.y<midball.y && wm->ball.vel.loc.length()>0.2)
//                {
//                    rc.fin_pos.loc = i;
//                    rc.maxSpeed = 4;
//                }
//                else
//                {
//                    Vector2D mid = (vdarvazel+midball)/2;
//                    rc.fin_pos.loc = mid;
//                    rc.maxSpeed=4;
//                }
//            }
//            else// kharej e dayere
//            {
//                Vector2D vtmid =(taghato +vdarvazer)/2;
//                Line2D lt (vtmid , vdarvazel);
//                Vector2D i = lt.intersection(lb);
//                if(i.x>-2500 &&i.x<vtmid.x && i.y>-2500 && i.y<vtmid.y && wm->ball.vel.loc.length()>0.2)
//                {
//                    rc.fin_pos.loc = i;
//                    rc.maxSpeed = 4;
//                }
//                else
//                {
//                    Vector2D mid = (vdarvazel +vtmid)/2;
//                    rc.fin_pos.loc = mid;
//                    rc.maxSpeed = 4;
//                }

//            }

//        }
//        else if(vball.x>-1990 && vball.y>-2500)//samt e rast zamin
//        {
//            rc.fin_pos.loc = vdarvazemid;
//            rc.maxSpeed = 4;
//        }
//        else//vasat e zamin
//        {
//            rc.fin_pos.loc = vdarvazemid;
//            rc.maxSpeed = 4;
//        }
   //darvaze behine

//dms.square
//        Vector2D tir1(darM1x,darM1y);
//        Vector2D tir2(darM2x,darM2y);
//        Vector2D tir3(darM3x,darM3y);
//        Vector2D tir4(darM4x,darM4y);
//        rc.maxSpeed=2;
//        qDebug() << "Flag: " << flag;
//        if(flag==0)
//        {
//            rc.fin_pos.loc=tir1;
//            rc.fin_pos.dir = (rc.fin_pos.loc-tir4).dir().radian();
//            if( (wm->ourRobot[id].pos.loc - rc.fin_pos.loc).length() <50)
//                flag=1;
//        }
//        else if(flag==1)
//        {
//            rc.fin_pos.loc=tir2;
//            rc.fin_pos.dir = (rc.fin_pos.loc-tir1).dir().radian();
//            if( (wm->ourRobot[id].pos.loc - tir2).length() <50)
//                flag=2;
//        }
//        else if(flag==2)
//        {
//            rc.fin_pos.loc=tir3;
//            rc.fin_pos.dir = (rc.fin_pos.loc-tir2).dir().radian();
//            rc.maxSpeed=1;
//            if( (wm->ourRobot[id].pos.loc - tir3).length() <50)
//               flag=3;
//        }
//        else if(flag==3)
//        {
//            rc.fin_pos.loc=tir4;
//            rc.maxSpeed=1;
//            rc.fin_pos.dir = (rc.fin_pos.loc-tir3).dir().radian();
//            if( (wm->ourRobot[id].pos.loc - tir4).length() <50)
//                flag=0;
//        }
//        else //unnecessary
//        {
//            rc.fin_pos.loc=tir1;
//            rc.maxSpeed=1;
//        }

    //emad's code
    //darvaze bane behine start
//    Vector2D golieL = Field::ourGoalPost_L;
//    Vector2D golieR = Field::ourGoalPost_R;
//    Line2D golieGeneralLine (golieL , golieR);
//    Vector2D ballNextPos = wm->ball.pos.loc + wm->ball.vel.loc;
//    Line2D ballMovement (wm->ball.pos.loc , ballNextPos);
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
//            Line2D golieChangedline(saveL , saveR);
//            target = golieChangedline.intersection(ballMovement);
//            rc.fin_pos.loc = target;
//            rc.maxSpeed = 4;
//        }
//        else{
//            dangerArea.intersection(lineR , &intersectionPointR1 , &intersectionPointR2);
//            dangerArea.intersection(lineL , &intersectionPointL1 , &intersectionPointL2);
//            saveL = sortVec(intersectionPointL1 , intersectionPointL2);
//            saveR = sortVec(intersectionPointR1 , intersectionPointR2);
//            rc.fin_pos.loc = (saveL + saveR)/2;
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
    //moraba start
//    Vector2D locA(-1500 , -2500);
//    Vector2D plusX(-1000 , 0);
//    Vector2D plusY(0 , 1000);
//    switch (flag){
//    case 0 :
//    rc.fin_pos.loc = locA ;
//    if ((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//        flag =1;
//    break;
//    case 1 :
//        rc.fin_pos.loc = (locA + plusX);
//        if ((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            flag =2;
//        break;
//    case 2 :
//        rc.fin_pos.loc = (locA + plusX + plusY);
//        if ((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            flag =3;
//        break;
//    case 3 :
//        rc.fin_pos.loc = (locA + plusY);
//        if ((wm->ourRobot[1].pos.loc - rc.fin_pos.loc).length() < 100)
//            flag =0;
//        break;

//    }
    //Vector2D golieMid (-2000 , -2500);
    //qDebug() << "daraje = "<< (wm->ball.pos.loc - golieMid).dir.radian();

    //moraba end

//        Vector2D t(-2000 ,-2500);
//        //Vector2D t(-4400 ,0);
//        Vector2D t1(-500 , -2500);
//       rc.fin_pos.dir=(wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();
//        Line2D l(t,t1);
//        Vector2D t2,t3,t4,t5,t6;
//        t2=wm->ball.pos.loc;
//        t3=t2+wm->ball.vel.loc;
//        Line2D l1(t2,t3);
//        t6=l.intersection(l,l1);
//       if(((t6.x-wm->ourRobot[id].pos.loc.x)<=100&&(t6.x-wm->ourRobot[id].pos.loc.x)>0)||((wm->ourRobot[id].pos.loc.x-t6.x)<=100&&(wm->ourRobot[id].pos.loc.x-t6.x)>0))
//          t6.y+=200;
//        t5=t;
//        t5.x-=500;
//        if(wm->ball.pos.loc.y<0)
//        {
//            t.x+=(wm->ball.pos.loc.x+2000)/4;
//            t.y-=(wm->ball.pos.loc.x+2000)/15;
//            Line2D l2(t5,t);
//            t6=l.intersection(l2,l1);
//        }
//        if(t6.isValid()&&(t6.x>-2600&&t6.x<-1400)&&(wm->ball.vel.loc.length()>0.2))
//            rc.fin_pos.loc=t6;
//        else
//            rc.fin_pos.loc=t;
//        rc.maxSpeed=4;
        //wm->debug_pos.append(wm->ball.pos.loc);
        //wm->debug_type = 2;

    //end emad's code

    //Vector2D pos=wm->ourRobot[id].pos.loc;
    //t1=wm->ball.pos.loc;
    //t2 = t1 + wm->ball.vel.loc;
    //t2=wm->ball.pos.loc;
    //Line2D l(t1,t2);
    //Circle2D c(pos,500);
    //Vector2D t3,t4;
    //int inters = c.intersection(l,&t3,&t4);
    //if(inters == 0){
    // rc.fin_pos.loc = wm->ourRobot[id].pos.loc;
    //}
    //else if(inters == 1){

    //}


    //rc.fin_pos.dir=(t3-t4).dir().radian();
    //rc.fin_pos.loc=t3;
    //Vector2D pos=wm->ourRobot[id].pos.loc;
    //Vector2D ball=wm->ball.pos.loc;!=
    //rc.fin_pos.loc=pos;
    //rc.fin_pos.dir = (ball-pos).dir().radian();
    //rc.maxSpeed=4;
    //  wm->ball.vel.loc.length();
    // rc.fin_pos.loc = wm->ball.pos.loc;
    // rc.maxSpeed = 4;



    //    Vector2D pos = wm->ball.pos.loc;
    //    Vector2D def(0 , 0);
    //    Line2D l(def , pos);
    //    Circle2D c(pos , 200);


    //    Vector2D t1 , t2;
    //    c.intersection(l , &t1 , &t2);

    //    Vector2D real;
    //    if(t1.dist(def) < t2.dist(def)){
    //        real = t2;
    //    }
    //    else{
    //        real = t1;
    //    }

    //    wm->debug_pos.append(t1);
    //    wm->debug_pos.append(t2);
    //    //wm->debug_type = 2;

    //    rc.fin_pos.loc = real;
    //    rc.fin_pos.dir = ( def - pos ).dir().radian();
    //    rc.useNav = true;
    //    rc.maxSpeed = 3;




    //    if(!wm->ourRobot[id].isValid) return rc;
    //    static bool flag = false;
    //    Vector2D u(-1000 , -1500);
    //    Vector2D d(-2000 , -1500);
    //    Line2D goalLine(u , d);
    //    Vector2D ballPos = wm->ball.pos.loc;
    //    Vector2D preBallPos = wm->ball.pos.loc + wm->ball.vel.loc;
    //    Line2D ballDirection(ballPos , preBallPos);

    //    Vector2D pos = goalLine.intersection(ballDirection);
    //    if(wm->ball.vel.loc.length() < 1 || pos.x < -2000 || pos.x > -1000 ){
    //        pos.x = -1500;
    //        pos.y = -1500;
    //    }
    //   else{

    //        int range = 400;
    //        if(pos.x > wm->ourRobot[1].pos.loc.x && wm->ball.pos.loc.dist(wm->ourRobot[1].pos.loc) > 300){
    //            pos.x += range;
    //        }
    //        if(pos.x < wm->ourRobot[1].pos.loc.x && wm->ball.pos.loc.dist(wm->ourRobot[1].pos.loc) > 300){
    //            pos.x -= range;
    //        }
    //   }
    //    wm->debug_pos.append(u);
    //    wm->debug_pos.append(d);
    //    rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();
    //    rc.fin_pos.loc = pos;
    //    rc.maxSpeed = 4;
//    Vector2D p1 = Vector2D(-2000,-1000);
//    Vector2D p2 = Vector2D(-2000,-2000);
//    if(state==1)
//    {
//        rc.fin_pos.loc = p1;
//        if(wm->kn->ReachedToPos(wm->ourRobot[1].pos.loc,p1,50))
//            state = 2;
//        rc.useNav = true;
//    }
//    else
//    {
//        rc.fin_pos.loc = p2;
//        if(wm->kn->ReacDebug() <<" Runinnnnnnnnnnnnnnnnnnnnnnnnnnnnng";
//                Vector2D p1 = Vector2D(-2000,-1000);
//                Vector2D p2 = Vector2D(-2000,-2000);
//                if(state==1)
//                {
//                    rc.fin_pos.loc = p1;
//                    if(wm->kn->ReachedToPos(wm->ourRobot[1].pos.loc,p1,50))
//                        state = 2;
//                    rc.useNav = true;
//                }
//                else
//                {hedToPos(wm->ourRobot[1].pos.loc,p2,50))
//            state = 1;
//        rc.useNav = true;
//    }
//    qDebug() <<" State : "<< state << " Fin Pos: "<<rc.fin_pos.loc.x<< ", "<<rc.fin_pos.loc.y;
//    rc.maxSpeed = 1;
    return rc;
}
