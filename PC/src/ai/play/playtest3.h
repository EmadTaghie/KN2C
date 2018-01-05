#ifndef PLAYTEST3_H
#define PLAYTEST3_H

#include "play.h"

class PlayTest3 : public Play
{
    Q_OBJECT
public:
    explicit PlayTest3(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();

 ////////////////////////////
private:
    int flag=0;
    TacticTest3 *test3;
    ///////////////////////////
};

#endif // PLAYTEST3_H

