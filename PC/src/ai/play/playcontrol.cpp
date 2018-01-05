
#include "playcontrol.h"
playControl::playControl(WorldModel *worldmodel, QObject *parent) :
    Play("playcontrol", worldmodel, parent)
{

    anghezy=new tacticControl(wm);

}

int playControl::enterCondition()
{
    //std::cout<<"aasdasdas";
    return 0;//10002;
}

void playControl::initRole()
{
}

void playControl::execute()
{
    tactics[1] = anghezy ;
    tactics[3] = anghezy ;
}

