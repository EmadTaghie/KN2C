#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{//////////////////////////////////
    test = new TacticTest(wm);
    test2 = new TacticTest2(wm);
    flag = 0;
    ///////////////////////////////////
}

int PlayTest::enterCondition()
{
    if(wm->gs == STATE_Stop)
        return 10000000003;
    else
        return 10000000003;

}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{//---////////////////////////////////////////////////////
        wm->debug_pos.clear();
        tactics[0] = test;
        tactics[1] = test2;
        if(wm->gs == STATE_Stop){
            wm->ourRobot[0].Status = AgentStatus::FollowingBall;
            wm->ourRobot[1].Status = AgentStatus::FollowingBall;
        }
        else if(wm->gs == STATE_Free_kick_Our){
            wm->ourRobot[0].Status = AgentStatus::Kicking;
            wm->ourRobot[1].Status = AgentStatus::RecievingPass;
        }
        else if(wm->gs == STATE_Free_kick_Opp){
            wm->ourRobot[0].Status = AgentStatus::RecievingPass;
            wm->ourRobot[1].Status = AgentStatus::Kicking;
        }
        else{
            wm->ourRobot[0].Status = AgentStatus::Idle;
            wm->ourRobot[1].Status = AgentStatus::Idle;
        }
//        tactics[2] = test;
//        tactics[3] = test;

}
