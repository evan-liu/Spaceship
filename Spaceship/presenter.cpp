#include "StdAfx.h"
#include "Presenter.h"
#include <iostream>
#include "Model.h"

CPresenter::CPresenter(CModel *pModel) {
    m_pModel = pModel;
}

CPresenter::~CPresenter() {
}

void CPresenter::ClearScreen() {
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
    system("CLS");
#else
    system("clear");
#endif
}

void CPresenter::Update() {
    ClearScreen();

    BorderLine();
    for (int y = 0; y < m_pModel->GetRowCount(); y++) {
        std::cout << "  |";
        for (int x = 0; x < m_pModel->GetColumnCount(); ++x) {
            std::cout << m_pModel->GetCharAt(x, y);
        }
        std::cout << '|';
        std::cout << std::endl;
    }
    BorderLine();

    std::cout << "!: " << m_pModel->GetBulletCount();
    std::cout << "  ";
    std::cout << "@: " << m_pModel->GetBombCount();
    std::cout << "    ";
    std::cout << "SCORE: " << m_pModel->GetScore();
    std::cout << std::endl;
}

void CPresenter::BorderLine() {
    for (int i = 0; i < m_pModel->GetColumnCount(); ++i) {
        std::cout << "~ ";
    }
    std::cout << std::endl;
}