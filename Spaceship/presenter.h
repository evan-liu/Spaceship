#pragma once

class CModel;

//==============================================================================
// Presenter
//==============================================================================
class CPresenter {

public:
    CPresenter(CModel *pModel);

    virtual ~CPresenter();

    void ClearScreen();

    void Update();

private:
    CModel *m_pModel;

    void BorderLine();
};