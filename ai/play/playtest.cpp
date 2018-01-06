#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{//////////////////////////////////
    test = new TacticTest(wm);
    test2 = new TacticTest2(wm);
    test3 = new TacticTest3(wm);
    testStop = new tacticTestStop(wm);
    ///////////////////////////////////
}

int PlayTest::enterCondition()
{
//    if(wm->gs == STATE_Stop)
//    return 120000;
//    else
//        return 0;
    return 1000000;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{//---////////////////////////////////////////////////////
        wm->debug_pos.clear();

//        tactics[1] = testStop;
//        tactics[3] = testStop;
        tactics[0] = test3;
}
