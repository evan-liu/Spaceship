#include "StdAfx.h"
#include "Controller.h"
#include "Model.h"
#include <Windows.h>
#include <iostream>

//==============================================================================
// KeyboardChecker
//==============================================================================
static const double INTERVAL = 0.15;

CKeyboardChecker::CKeyboardChecker(int key) {
    m_iKey = key;
    m_bIsPressed = false;
    m_bIsHolding = false;
}

CKeyboardChecker::~CKeyboardChecker() {
}

bool CKeyboardChecker::GetIsPressed() {
    return m_bIsPressed;
}

void CKeyboardChecker::Tick(double seconds) {
    //-- Not Press
    if (!GetAsyncKeyState(m_iKey)) {
        m_bIsPressed = false;
        m_bIsHolding = false;
        return;
    }

    //-- New Press
    if (!m_bIsHolding) {
        m_bIsPressed = true;
        m_bIsHolding = true;
        m_dLastTriggerTime = clock() / CLOCK_UNIT_TO_SECOND;
        return;
    }

    //-- Holding
    double now = (double) clock() / CLOCK_UNIT_TO_SECOND;
    if (now - m_dLastTriggerTime >= INTERVAL) {
        m_bIsPressed = true;
        m_dLastTriggerTime = now;
    } else {
        m_bIsPressed = false;
    }
}

void CKeyboardChecker::Reset() {
    m_bIsPressed = false;
    m_bIsHolding = false;
}

//==============================================================================
// Controller
//==============================================================================
CController::CController(CModel *model) {
    m_pModel = model;
    m_pLeftChecker = new CKeyboardChecker(VK_LEFT);
    m_pUpChecker = new CKeyboardChecker(VK_UP);
    m_pRightChecker = new CKeyboardChecker(VK_RIGHT);
    m_pDownChecker = new CKeyboardChecker(VK_DOWN);
    m_pBulletChecker = new CKeyboardChecker(0x31);
    m_pBombChecker = new CKeyboardChecker(0x32);
}

CController::~CController() {
    delete m_pLeftChecker;
    delete m_pUpChecker;
    delete m_pRightChecker;
    delete m_pDownChecker;
}

void CController::Tick(double seconds) {
    m_pBulletChecker->Tick(seconds);
    if (m_pBulletChecker->GetIsPressed()) {
        m_pModel->FireBullet();
    }

    m_pBombChecker->Tick(seconds);
    if (m_pBombChecker->GetIsPressed()) {
        m_pModel->FireBomb();
    }

    m_pLeftChecker->Tick(seconds);
    if (m_pLeftChecker->GetIsPressed()) {
        m_pModel->MoveLeft();
        return;
    }

    m_pRightChecker->Tick(seconds);
    if (m_pRightChecker->GetIsPressed()) {
        m_pModel->MoveRight();
        return;
    }

    m_pUpChecker->Tick(seconds);
    if (m_pUpChecker->GetIsPressed()) {
        m_pModel->MoveUp();
        return;
    }

    m_pDownChecker->Tick(seconds);
    if (m_pDownChecker->GetIsPressed()) {
        m_pModel->MoveDown();
        return;
    }
}

bool CController::AskPlayAgain() {
    char i;
    while (true) {
        std::cout << "Game Over! Play again? (y/n)";
        std::cin >> i;
        if (i == 'y') return true;
        if (i == 'n') return false;
    };
}

void CController::Reset() {
    m_pLeftChecker->Reset();
    m_pUpChecker->Reset();
    m_pRightChecker->Reset();
    m_pDownChecker->Reset();
}