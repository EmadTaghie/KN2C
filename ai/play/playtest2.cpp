#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    // Goaler.
    tGolie = new TacticGoalie(wm);
    tTF = new TacticTestFriction(wm);
    thalt = new TacticHalt(wm);
    tTest = new TacticTest(wm);

}

int PlayTest2::enterCondition()
{
    if(wm->gs == STATE_Stop)
    return 0;
    else
        return 120000;
}

void PlayTest2::initRole()
{

}

void PlayTest2::execute()
{
//    tactics[wm->ref_goalie_our] = tGolie;
    tactics[1] = tTest;
    //qDebug()<<"Ball Speed is "<<wm->ball.vel.loc.length();
}

