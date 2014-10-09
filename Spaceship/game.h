#pragma once

#include "Clock.h"

class CModel;

class CPresenter;

class CController;

//==============================================================================
// Game
//==============================================================================
class CGame : public IClockTarget {

public:
    CGame();

    virtual ~CGame();

    void Start();

    virtual void Tick(double seconds) override;

private:
    CClock *m_pClock;
    CModel *m_pModel;
    CPresenter *m_pPresenter;
    CController *m_pController;

    double m_dModelTime;

    void GameOver();
};