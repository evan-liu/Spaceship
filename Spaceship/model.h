#pragma once

//==============================================================================
// Model
//==============================================================================
static const int COLUMN_COUNT = 10;
static const int ROW_COUNT = 20;
static const char EMPTY = ' ';
static const char BLOCK = '#';
static const char PLANE = '^';
static const char BULLET = '!';
static const char BOMB = '@';
static const char CRASH = '*';

class CModel {

public:
    CModel();

    virtual ~CModel();

    bool GetIsGameOver();

    int GetColumnCount();

    int GetRowCount();

    char GetCharAt(int x, int y);

    double GetUpdateDelay();

    int GetLevel();

    int GetScore();

    int GetBulletCount();

    int GetBombCount();

    bool GetIsChanged();

    void SetIsChanged(bool p_isChanged);

    void Update();

    void MoveLeft();

    void MoveRight();

    void MoveUp();

    void MoveDown();

    void NewGame();

    void FireBullet();

    void FireBomb();

private:
    bool m_bIsGameOver;

    int m_iColumnCount;
    int m_iRowCount;
    double m_dUpdateDelay;

    int m_iLevel;
    int m_iScore;

    char m_map[ROW_COUNT][COLUMN_COUNT];

    int m_iBlankLineLeft;
    int m_iBlankLineCount;
    int m_iBlockCount;

    int m_iPlaneRow;
    int m_iPlaneColumn;

    int m_iBulletCount;
    int m_iBombCount;

    bool m_bIsChanged;

    void CreateRow(int rowIndex);

    void CreateBlankRow(int rowIndex);

    bool NeedUpdateDelay();

    bool NeedUpdateBlockCount();

    void UpdatePlane();

    void MovePlaneTo(int row, int column);

    int RowFromScreenY(int y);

    int ScreenYFromRow(int row);
};
