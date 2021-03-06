#ifndef PLAYTEST2_H
#define PLAYTEST2_H

#include "play.h"
#include "QDebug"

class PlayTest2 : public Play
{
    Q_OBJECT
public:
    explicit PlayTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticGoalie* tGolie;
    TacticTestFriction* tTF;
    TacticHalt* thalt;
    TacticTest* Test;
    TacticTest2* Test2;

    virtual void initRole();
};

#endif // PLAYTEST2_H
