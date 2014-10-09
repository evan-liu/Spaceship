#pragma once

#include <time.h>

//==============================================================================
// ClockTarget
//==============================================================================
class IClockTarget {

public:
    virtual void Tick(double seconds) = 0;

};

//==============================================================================
// Clock
//==============================================================================
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
static const double CLOCK_UNIT_TO_SECOND = 1000.0;
#else
static const double CLOCK_UNIT_TO_SECOND = 1000000.0;
#endif

class CClock {
public:
    CClock(IClockTarget *target);

    virtual ~CClock();

    void Start();

    void End();

    bool IsRunning();

private:
    double m_dLastTime;
    bool m_bIsRunning;

    IClockTarget *m_pTarget;
};

