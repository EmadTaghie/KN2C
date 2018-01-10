#include "tactictest3.h"
#include "game_state.h"
#define Radius 500
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
    //sTest->execute(rc);
//    if(flag==0)
//    {
//        rc.fin_pos.loc=Vector2D(-1500,-2500);
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50 ))
//            flag=1;
//    }
//    if(flag==1)
//    {
//        rc.fin_pos.loc=Vector2D(-1500,0);
//        if(wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50 ))
//            flag=0;
//    }
    /*game mode1*/

    if(wm->gs==STATE_Halt)
        qDebug()<<"Halt";
    if(wm->gs==STATE_Start)
        qDebug()<<"Start";
    if(wm->gs==STATE_Free_kick_Our)
        qDebug()<<"Our Free kick";
    if(wm->gs==STATE_Stop)
        qDebug()<<"Stop";
    if(wm->gs==STATE_ForceStart)
        qDebug()<<"Force Start";
    if(wm->gs==STATE_Free_kick_Opp)
        qDebug()<<"opp Free kick";
    if(wm->gs==STATE_Free_kick_Our)
        qDebug()<<"Our Free kick";
    if(wm->gs==STATE_Indirect_Free_kick_Opp)
        qDebug()<<"opp IndirectFree kick";
    if(wm->gs==STATE_Indirect_Free_kick_Our)
        qDebug()<<"Our Free kick";
    if(wm->gs==STATE_Kick_off_Our)
        qDebug()<<"Our Kick off";
    if(wm->gs==STATE_Kick_off_Opp)
        qDebug()<<"Opp Kick Off";
    if(wm->gs==STATE_Penalty_Opp)
        qDebug()<<"Opp Penalty";
    if(wm->gs==STATE_Penalty_Our)
        qDebug()<<"Our Penalty";

    /*game mode2*/

//    if(wm->cmgs.GameState::gameOn())
//        qDebug()<<"Game On";
//    else
//        qDebug()<<"Game Stop";
//    if(wm->cmgs.GameState::freeKick())
//    {
//        qDebug()<<"Free Kick";
//        if(wm->cmgs.GameState::ourDirectKick())
//        {
//            qDebug()<<"Our Free Kick";
//            if(wm->cmgs.GameState::directKick())
//                qDebug()<<"Direct Kick";
//            if(wm->cmgs.GameState::indirectKick())
//                qDebug()<<"Direct InKick";
//        }
//        if(wm->cmgs.GameState::theirFreeKick())
//        {
//            qDebug()<<"Our Free Kick";
//            if(wm->cmgs.GameState::directKick())
//                qDebug()<<"Direct Kick";
//            if(wm->cmgs.GameState::indirectKick())
//                qDebug()<<"Direct InKick";
//        }
//    }
//    if(wm->cmgs.GameState::kickoff())
//        qDebug()<<"Kick Off";
//    if(wm->cmgs.GameState::penaltyKick())
//        qDebug()<<"Penalty Kick";
//    if(wm->cmgs.GameState::timeout())
//        qDebug()<<"Time Out";
//    if(wm->cmgs.GameState::restart())
//        qDebug()<<"Restart Game";
//    if(!(wm->cmgs.GameState::canMove()))
//        qDebug()<<"Halted";


    /*Circle*/
//    rc.useNav=false;
//    Vector2D startPoint(-2600 ,-1500);
//    if(state<0)
//    {
//        rc.fin_pos.loc=startPoint;
//        if( wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,startPoint,50) )
//            state=0;
//    }
//    if( (x<500) && (state==0) )
//    {
//        y=sqrt(Radius*Radius - x*x);
//        rc.fin_pos.loc=Vector2D(x-2000,y-1500);
//        if( wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50) )
//            x=x+100;
//        if(x==500)
//            state=1;
//    }
//    if( (x>=-500) && (state==1) )
//    {
//        y=-sqrt(Radius*Radius - x*x);
//        rc.fin_pos.loc=Vector2D(x-2000,y-1500);
//        if( wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50) )
//            x=x-100;
//        if(x==-500)
//            state=0;
//    }
 /*Darvaze*/
        int count=0;
        for(int i=0;i<=5;i++)
            if(wm->oppRobot[i].isValid)
                opRobot[i]=1;
        rc.fin_pos.dir=(wm->ball.pos.loc - wm->ourRobot[id].pos.loc).dir().radian();

        if(state>=0)
        {
            qDebug()<<"0 scop:";
            if( ( wm->ball.pos.loc.x<Field::ourGoalCenter.x + 1000 )&& ( wm->ball.pos.loc.y<=Field::ourGoalPost_L.y + 1000 )
                 && ( wm->ball.pos.loc.y>=Field::ourGoalPost_R.y - 1000 ) && ( (wm->ball.vel.loc.length() < 0.2 ) ) )
            {
                qDebug()<<"Shoot ";
                rc.useNav=true;
                rc.fin_pos.loc.y=wm->ball.pos.loc.y;
                rc.fin_pos.loc.x=wm->ball.pos.loc.x - BALL_RADIUS*2 ;
                rc.kickspeedx=10;
            }
            else if(wm->ball.vel.loc.length() < 0.2)
            {
                qDebug()<<"positioning ";
                for(int i=0;i<=5;i++)
                {
                    if(wm->oppRobot[i].isValid)
                    {
                        opRobot[count]=i;
                        count++;
                    }
                }
                if( (wm->oppRobot[opRobot[0]].isValid) && (wm->oppRobot[opRobot[1]].isValid) )
                {
                    Line2D upLine (wm->oppRobot[opRobot[0]].pos.loc , Field::ourGoalPost_L);
                    Line2D downLine (wm->oppRobot[opRobot[1]].pos.loc , Field::ourGoalPost_R);
                    Vector2D tu1,tu2,td1,td2,TU,TD;
                    Field::ourDefenceCircle.intersection(upLine,&tu1,&tu2);
                    if(tu1.x>tu2.x)
                        TU=tu1;
                    else TU=tu2;
                    Field::ourDefenceCircle.intersection(downLine,&td1,&td2);
                    if(td1.x>td2.x)
                        TD=td1;
                    else TD=td2;
                    TDmid=(TD+Field::ourGoalPost_R)/2;
                    TUmid=(TU+Field::ourGoalPost_L)/2;
                    Vector2D newGoalCenter=(TDmid+TUmid)/2;
                    rc.fin_pos.loc=newGoalCenter;
                }
                else    if(wm->oppRobot[opRobot[0]].isValid)
                {
                    Line2D upLine (wm->oppRobot[opRobot[0]].pos.loc , Field::ourGoalPost_L);
                    Line2D downLine (wm->oppRobot[opRobot[0]].pos.loc , Field::ourGoalPost_R);
                    Vector2D tu1,tu2,td1,td2,TU,TD;
                    Field::ourDefenceCircle.intersection(upLine,&tu1,&tu2);
                    if(tu1.x>tu2.x)
                        TU=tu1;
                    else TU=tu2;
                    Field::ourDefenceCircle.intersection(downLine,&td1,&td2);
                    if(td1.x>td2.x)
                        TD=td1;
                    else TD=td2;
                    TDmid=(TD+Field::ourGoalPost_R)/2;
                    TUmid=(TU+Field::ourGoalPost_L)/2;
                    Vector2D newGoalCenter=(TDmid+TUmid)/2;
                    rc.fin_pos.loc=newGoalCenter;
                }
                else    if(wm->oppRobot[opRobot[1]].isValid)
                {
                    Line2D upLine (wm->oppRobot[opRobot[1]].pos.loc , Field::ourGoalPost_L);
                    Line2D downLine (wm->oppRobot[opRobot[1]].pos.loc , Field::ourGoalPost_R);
                    Vector2D tu1,tu2,td1,td2,TU,TD;
                    Field::ourDefenceCircle.intersection(upLine,&tu1,&tu2);
                    if(tu1.x>tu2.x)
                        TU=tu1;
                    else TU=tu2;
                    Field::ourDefenceCircle.intersection(downLine,&td1,&td2);
                    if(td1.x>td2.x)
                        TD=td1;
                    else TD=td2;
                    TDmid=(TD+Field::ourGoalPost_R)/2;
                    TUmid=(TU+Field::ourGoalPost_L)/2;
                    Vector2D newGoalCenter=(TDmid+TUmid)/2;
                    rc.fin_pos.loc=newGoalCenter;
                }
                else rc.fin_pos.loc=Field::ourGoalCenter;
            }
            else if(wm->ball.vel.loc.length() > 0.2)
            {
                qDebug()<<"moving ball scop";
                Line2D ballLine(wm->ball.pos.loc , wm->ball.pos_predicted.loc);
                Line2D newGoalline(Field::ourGoalPost_L,Field::ourGoalPost_R);
                fixedPoint=ballLine.intersection(newGoalline);
                if( (fixedPoint.y<Field::ourGoalPost_L.y + 50)&&(fixedPoint.y>Field::ourGoalPost_R.y - 50)  )
                {
                    qDebug()<<"Moving to FixedPoint";
                    rc.fin_pos.loc=fixedPoint;
                }
                else
                {
                    qDebug()<<"FIXEDPOINT.Y="<<fixedPoint.y;
                    Vector2D newGoalCenter=(TDmid+TUmid)/2;
                    rc.fin_pos.loc=newGoalCenter;
                }
            }
        }
        rc.maxSpeed=4;


    /*Passing*/
//    if (wm->gs==STATE_Stop)
//        rc.fin_pos.loc=Vector2D (-1500,0);
//    else
//    {
//        if(wm->gs==STATE_Free_kick_Our)
//        {
//               qDebug()<<"State="<<state;
//              rc.fin_pos.loc.x=wm->ball.pos.loc.x+BALL_RADIUS;
//              rc.fin_pos.loc.y=wm->ball.pos.loc.y;
//               rc.fin_pos.dir= (wm->ourRobot[2].pos.loc - wm->ourRobot[1].pos.loc).dir().radian();





//        }
//        if(wm->gs==STATE_Free_kick_Opp)
//        {


//        }
//    }
    return rc;
}
//rc.fin_pos.dir=(rc.fin_pos.loc- wm->ourRobot[id].pos.loc).dir().radian();
//Lineballmovement=(wm->ball.pos.loc , wm->ball.pos_predicted.loc
/*
        sKick->setIndex(this->id);
        sKick->setTarget(target);
        sKick->setKickType(true);
        sKick->execute(rc);
 */

