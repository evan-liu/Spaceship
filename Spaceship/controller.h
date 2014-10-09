#pragma once

#include "Clock.h"

class CModel;

//==============================================================================
// KeyboardChecker
//==============================================================================
class CKeyboardChecker : public IClockTarget {

public:
    CKeyboardChecker(int key);

    virtual ~CKeyboardChecker();

    virtual void Tick(double seconds) override;

    bool GetIsPressed();

    void Reset();

private:
    int m_iKey;
    double m_dLastTriggerTime;
    bool m_bIsHolding;
    bool m_bIsPressed;

};


//==============================================================================
// Controller
//==============================================================================
class CController {

public:
    CController(CModel *model);

    virtual ~CController();

    void Tick(double seconds);

    bool AskPlayAgain();

    void Reset();

private:
    CModel *m_pModel;

    CKeyboardChecker *m_pLeftChecker;
    CKeyboardChecker *m_pUpChecker;
    CKeyboardChecker *m_pRightChecker;
    CKeyboardChecker *m_pDownChecker;
    CKeyboardChecker *m_pBulletChecker;
    CKeyboardChecker *m_pBombChecker;

};