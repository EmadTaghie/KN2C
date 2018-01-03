#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{//////////////////////////////////
    test = new TacticTest(wm);
    test2 = new TacticTest2(wm);
    test3 = new TacticTest3(wm);
    ///////////////////////////////////
}

int PlayTest::enterCondition()
{
    return 120000;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{//---////////////////////////////////////////////////////
        wm->debug_pos.clear();
        tactics[1] = test2;
        tactics[3] = test;
        if(wm->gs == STATE_Stop){
            wm->ourRobot[3].Status = AgentStatus::FollowingBall;
            wm->ourRobot[1].Status = AgentStatus::FollowingBall;
        }
        else if(wm->gs == STATE_Free_kick_Our){
            wm->ourRobot[3].Status = AgentStatus::Kicking;
            wm->ourRobot[1].Status = AgentStatus::RecievingPass;
        }
        else if(wm->gs == STATE_Free_kick_Opp){
            wm->ourRobot[3].Status = AgentStatus::RecievingPass;
            wm->ourRobot[1].Status = AgentStatus::Kicking;
        }
        else{
            wm->ourRobot[3].Status = AgentStatus::Idle;
            wm->ourRobot[1].Status = AgentStatus::Idle;
        }
//        tactics[0] = test;
//        tactics[3] = test3;
//        tactics[2] = test;
//        tactics[3] = test2;
//        tactics[3] = test;
//        tactics[1] = test2;

}
