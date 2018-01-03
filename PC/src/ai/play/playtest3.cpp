#include "playtest3.h"
PlayTest3::PlayTest3(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest3", worldmodel, parent)
{//////////////////////////////////
    test3 = new TacticTest3(wm);
    ///////////////////////////////////
}

int PlayTest3::enterCondition()
{
    return 100000
}

void PlayTest3::initRole()
{
}

void PlayTest3::execute()
{//---////////////////////////////////////////////////////
        wm->debug_pos.clear();
        tactics[1] = test3;

}

