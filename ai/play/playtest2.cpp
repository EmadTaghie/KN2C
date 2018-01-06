#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    // Goaler.
    tGolie = new TacticGoalie(wm);
    tTF = new TacticTestFriction(wm);
    thalt = new TacticHalt(wm);
    Test = new TacticTest(wm);
    Test2 = new TacticTest2(wm);

}

int PlayTest2::enterCondition()
{
//    if(wm->gs == STATE_Stop)
    return 0;
//    else
//        return 120000;
}

void PlayTest2::initRole()
{

}

void PlayTest2::execute()
{
//    tactics[wm->ref_goalie_our] = tGolie;
    if(wm->gs == STATE_Free_kick_Our){
       tactics[1] = Test;
       tactics[3] = Test2;
    }
    else if(wm->gs == STATE_Free_kick_Opp){
        tactics[1] = Test2;
        tactics[3] = Test;
    }
    //qDebug()<<"Ball Speed is "<<wm->ball.vel.loc.length();
}

