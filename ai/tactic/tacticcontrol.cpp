 #include "tacticcontrol.h"
tacticControl::tacticControl(WorldModel *worldmodel, QObject *parent) :
Tactic("tacticControl", worldmodel, parent)
{
canKick = false;
firstKick = false;
kicked = false;
timer = new QTimer();
state=0;
connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
alfa = 0;
}
RobotCommand tacticControl::getCommand()
{
RobotCommand rc;
if(!wm->ourRobot[id].isValid) return rc;
////moving on width direction to ball////////////////////////////////////////////
//state =1;
rc.useNav = true;
 switch (state) {

 //line2000

// case 0:
// rc.fin_pos.loc = Vector2D(-1600,-400);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=1;
//    wm->debug_pos.clear();
//}
// break;
// case 1:
// rc.fin_pos.loc=Vector2D(-1600,-2000);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=2;
//    wm->debug_pos.clear();
//}
//     break;
// case 2:
// rc.fin_pos.loc = Vector2D(-1600,-400);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=3;
//    wm->debug_pos.clear();
//}

// break;
// case 3:
// rc.fin_pos.loc=Vector2D(-1600,-2000);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=1;
//    wm->debug_pos.clear();
//}
//     break;
// }
//rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();


 //line


 //zigzag
// case 0:
// rc.fin_pos.loc = Vector2D(-1600,-2000);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=1;
//    wm->debug_pos.clear();
//}
// break;
// case 1:
// rc.fin_pos.loc=Vector2D(-2700,-1000);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=2;
//    wm->debug_pos.clear();
//}
//     break;
// case 2:
// rc.fin_pos.loc = Vector2D(-900,-400);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=3;
//    wm->debug_pos.clear();
//}
// break;
// case 3:
// rc.fin_pos.loc=Vector2D(-2700,800);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=4;
//    wm->debug_pos.clear();
//}
//     break;
// case 4:
// rc.fin_pos.loc=Vector2D(-1600,1800);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=5;
//    wm->debug_pos.clear();
//}
//     break;
// case 5:
// rc.fin_pos.loc=Vector2D(-900,700);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=6;
//    wm->debug_pos.clear();
//}
//     break;
// case 6:
// rc.fin_pos.loc=Vector2D(-900,-700);
// if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=0;
//    wm->debug_pos.clear();
//}
//     break;
// }
//rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();

//zigzag








 //star

 case 0:
 rc.fin_pos.loc = Vector2D(-1600,-1000);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=1;
    wm->debug_pos.clear();
}
 break;
 case 1:
 rc.fin_pos.loc=Vector2D(-2900,100);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=2;
    wm->debug_pos.clear();
}
 break;
 case 2:
 rc.fin_pos.loc=Vector2D(-1600,1200);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=3;
    wm->debug_pos.clear();
}
 break;
 case 3:
 rc.fin_pos.loc=Vector2D(-2400,-1000);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=4;
    wm->debug_pos.clear();
}
 break;
 case 4:
 rc.fin_pos.loc=Vector2D(-2400,1200);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=5;
    wm->debug_pos.clear();
}
 break;
 case 5:
 rc.fin_pos.loc=Vector2D(-1600,-1000);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=6;
    wm->debug_pos.clear();
}
 break;

 case 6:
 rc.fin_pos.loc=Vector2D(-2200,100);
 if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100){ state=6;
    wm->debug_pos.clear();
}
 break;


 }
//rc.fin_pos.dir = (wm->ball.pos.loc - wm->ourRobot[1].pos.loc).dir().radian();

 //star


 Vector2D a =wm->ball.pos.loc - wm->ourRobot[id].pos.loc;
 //rc.fin_pos.dir=a.dir().radian();
/////////////////////////////////////////////////////////////////////////////////
 ////moving on rectabgel direction to ball////////////////////////////////////////////
// switch (state) {
// case 0:
//     rc.fin_pos.loc = Vector2D(-1200,-2200);
//     if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100) state=1;
//     break;
// case 1:
//     rc.fin_pos.loc=Vector2D(-1200,2200);
//     if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100) state=2;
//     break;
// case 2:
//     rc.fin_pos.loc=Vector2D(-3000,2200);
//     if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100) state=3;
//     break;
// case 3:
//     rc.fin_pos.loc=Vector2D(-3000,-2200);
//     if((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length()<100) state=0;
//     break;
// }
//  Vector2D a =wm->ball.pos.loc - wm->ourRobot[id].pos.loc;
//  rc.fin_pos.dir=a.dir().radian();
 /////////////////////////////////////////////////////////////////////////////////
////going to center & loking to ball/////////////////////////////////////////////
//rc.fin_pos.loc =Vector2D(-1200,-2200);
//Vector2D a =wm->ball.pos.loc - wm->ourRobot[id].pos.loc;
//rc.fin_pos.dir=a.dir().radian();
/////////////////////////////////////////////////////////////////////////////////
////just looking at ball/////////////////////////////////////////////////////////
// Vector2D a =wm->ball.pos.loc - wm->ourRobot[id].pos.loc;
// rc.fin_pos.loc = wm->ourRobot[this->id].pos.loc;
// rc.fin_pos.dir=a.dir().radian();
/////////////////////////////////////////////////////////////////////////////////
////just looking at ball/////////////////////////////////////////////////////////
// Vector2D a =wm->ball.pos.loc - wm->ourRobot[id].pos.loc;
// Vector2D b ;
// b = {1,1};
// b.setLength(200);
// b.setDir(sin(alfa/100)*180);
// alfa++;
// rc.fin_pos.dir=a.dir().radian();
// rc.fin_pos.loc = wm->ball.pos.loc + b;
/////////////////////////////////////////////////////////////////////////////////
rc.maxSpeed=4;
rc.useNav = true;false;
rc.isBallObs = true;
rc.isKickObs = true;
cout <<"armin ! "<<endl;
wm->debug_type = 2;
wm->debug_pos.append(wm->ourRobot[1].pos.loc);
return rc;
}
RobotCommand tacticControl::goBehindBall()
{
RobotCommand rc;
canKick=false;
rc.maxSpeed = 4;                                                                       ;


// int index = findBestPlayerForPass();
// if(index != -1)
// {
// Vector2D target(wm->ourRobot[index].pos.loc.x,wm->ourRobot[index].pos.loc.y);
// Vector2D goal(target.x+500*cos(target.dir().DEG2RAD),target.y+500*sin(target.dir().DEG2RAD));
// rc.fin_pos = wm->kn->AdjustKickPoint(wm->ball.pos.loc,goal);
// }
return rc;
}
int tacticControl::findBestPlayerForPass()
{
int index = -1;
double min = 10000;
QList<int> ourAgents = wm->kn->ActiveAgents();
QList<int> freeAgents;
while( !ourAgents.isEmpty() )
{
int index = ourAgents.takeFirst();
if(isFree(index))
freeAgents.append(index);
}
while ( !freeAgents.isEmpty() )
{
int i = freeAgents.takeFirst();
if(wm->ourRobot[i].isValid && this->id != i)
{
if( (wm->ball.pos.loc-wm->ourRobot[i].pos.loc).length() < min)
{
min = (wm->ball.pos.loc-wm->ourRobot[i].pos.loc).length();
index = i;
}
}
}
return index;
}
void tacticControl::setKickerID(int index)
{
this->id = index;
}
bool tacticControl::isFree(int index)
{
QList<int> oppAgents = wm->kn->ActiveOppAgents();
bool isFree = true;
while( !oppAgents.isEmpty() )
{
int indexOPP = oppAgents.takeFirst();
if( (wm->ourRobot[index].pos.loc-wm->oppRobot[indexOPP].pos.loc).length() < DangerDist)
{
isFree = false;
}
if(!isFree)
break;
}
return isFree;
}
void tacticControl::timerEvent()
{
timer->stop();
if(firstKick)
{
if( (wm->ball.pos.loc-wm->ourRobot[id].pos.loc).length() > 200 )
{
kicked = true;
}
else
{
firstKick = false;
}
}
}
