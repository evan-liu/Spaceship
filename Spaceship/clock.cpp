#include "StdAfx.h"
#include "Clock.h"

CClock::CClock(IClockTarget *target) {
    m_pTarget = target;
}

CClock::~CClock() {
}

void CClock::Start() {
    m_bIsRunning = true;
    m_dLastTime = -1;
    while (m_bIsRunning) {
        double now = (double) clock() / CLOCK_UNIT_TO_SECOND;
        if (m_dLastTime < 0) {
            m_dLastTime = now;
            continue;
        }
        double seconds = now - m_dLastTime;
        if (seconds >= 0.01) {
            m_dLastTime = now;
            m_pTarget->Tick(seconds);
        }
    };
}

void CClock::End() {
    m_bIsRunning = false;
}

bool CClock::IsRunning() {
    return m_bIsRunning;
}