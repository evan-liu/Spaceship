#include "StdAfx.h"
#include "Game.h"
#include "Model.h"
#include "Presenter.h"
#include "Controller.h"

CGame::CGame() {
    m_pClock = new CClock(this);
    m_pModel = new CModel;
    m_pPresenter = new CPresenter(m_pModel);
    m_pController = new CController(m_pModel);
}

CGame::~CGame() {
    delete m_pClock;
    delete m_pController;
    delete m_pPresenter;
    delete m_pModel;
}

void CGame::Start() {
    m_pPresenter->Update();

    m_dModelTime = 0;
    m_pClock->Start();
}

void CGame::Tick(double seconds) {
    m_pModel->SetIsChanged(false);

    //-- Controller
    m_pController->Tick(seconds);
    if (m_pModel->GetIsGameOver()) {
        GameOver();
        return;
    }

    //-- Model
    m_dModelTime += seconds;
    if (m_dModelTime >= m_pModel->GetUpdateDelay()) {
        m_dModelTime -= m_pModel->GetUpdateDelay();
        m_pModel->Update();
        if (m_pModel->GetIsGameOver()) {
            GameOver();
            return;
        }
    }

    //-- View
    if (m_pModel->GetIsChanged()) {
        m_pPresenter->Update();
    }
}

void CGame::GameOver() {
    m_pPresenter->Update();
    m_pClock->End();

    if (m_pController->AskPlayAgain()) {
        m_pController->Reset();

        m_pModel->NewGame();
        m_pPresenter->Update();

        m_dModelTime = 0;
        m_pClock->Start();
    }
}