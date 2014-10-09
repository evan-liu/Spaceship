#include "StdAfx.h"
#include "Model.h"
#include <random>

CModel::CModel() {
    m_iColumnCount = COLUMN_COUNT;
    m_iRowCount = ROW_COUNT;
    NewGame();
}

CModel::~CModel() {

}

bool CModel::GetIsGameOver() {
    return m_bIsGameOver;
}

int CModel::GetColumnCount() {
    return m_iColumnCount;
}

int CModel::GetRowCount() {
    return m_iRowCount;
}

char CModel::GetCharAt(int x, int y) {
    return m_map[RowFromScreenY(y)][x];
}

double CModel::GetUpdateDelay() {
    return m_dUpdateDelay;
}

int CModel::GetLevel() {
    return m_iLevel;
}

int CModel::GetScore() {
    return m_iScore;
}

int CModel::GetBulletCount() {
    return m_iBulletCount;
}

int CModel::GetBombCount() {
    return m_iBombCount;
}

bool CModel::GetIsChanged() {
    return m_bIsChanged;
}

void CModel::SetIsChanged(bool p_isChanged) {
    m_bIsChanged = p_isChanged;
}

void CModel::Update() {
    CreateRow(m_iLevel % ROW_COUNT);
    m_iLevel++;

    MovePlaneTo((m_iPlaneRow + 1) % ROW_COUNT, m_iPlaneColumn);
    if (m_bIsGameOver) {
        return;
    }

    if (NeedUpdateDelay()) {
        m_dUpdateDelay *= .9;
    }
    if (NeedUpdateBlockCount()) {
        m_iBlockCount++;
    }

    m_iScore++;
}

void CModel::MoveLeft() {
    if (m_iPlaneColumn > 0) {
        MovePlaneTo(m_iPlaneRow, m_iPlaneColumn - 1);
    }
}

void CModel::MoveRight() {
    if (m_iPlaneColumn < COLUMN_COUNT - 1) {
        MovePlaneTo(m_iPlaneRow, m_iPlaneColumn + 1);
    }
}

void CModel::MoveUp() {
    if (ScreenYFromRow(m_iPlaneRow) > 0) {
        MovePlaneTo((m_iPlaneRow + 1) % ROW_COUNT, m_iPlaneColumn);
    }
}

void CModel::MoveDown() {
    if (ScreenYFromRow(m_iPlaneRow) < ROW_COUNT - 1) {
        MovePlaneTo((ROW_COUNT + m_iPlaneRow - 1) % ROW_COUNT, m_iPlaneColumn);
    }
}

void CModel::MovePlaneTo(int row, int column) {
    m_map[m_iPlaneRow][m_iPlaneColumn] = EMPTY;

    if (m_map[row][column] == BLOCK) {
        m_map[row][column] = CRASH;
        m_bIsGameOver = true;
    } else {
        if (m_map[row][column] == BULLET) {
            m_iBulletCount++;
        } else if (m_map[row][column] == BOMB) {
            m_iBombCount++;
        }
        m_iPlaneRow = row;
        m_iPlaneColumn = column;
        UpdatePlane();
    }

    m_bIsChanged = true;
}

void CModel::UpdatePlane() {
    m_map[m_iPlaneRow][m_iPlaneColumn] = PLANE;
}

void CModel::CreateRow(int rowIndex) {
    bool isBlankLine = m_iBlankLineLeft > 0;
    if (--m_iBlankLineLeft < 0) {
        m_iBlankLineLeft = m_iBlankLineCount;
    }

    if (isBlankLine) {
        CreateBlankRow(rowIndex);
        return;
    }

    int blockLeft = m_iBlockCount;
    int bulletLeft = 1;
    int bombLeft = 1;

    // Left to right | right to left
    int start = 0;
    int end = COLUMN_COUNT;
    int delta = 1;
    if (rand() % 2 > 0) {
        start = COLUMN_COUNT - 1;
        end = -1;
        delta = -1;
    }
    for (int i = start; i != end; i += delta) {
        if (blockLeft > 0 && rand() % 2 > 0) {
            m_map[rowIndex][i] = BLOCK;
            blockLeft--;
        } else {
            if (bulletLeft > 0 && rand() % 50 == 0) {
                m_map[rowIndex][i] = BULLET;
                bulletLeft--;
            } else if (bombLeft > 0 && rand() % 200 == 0) {
                m_map[rowIndex][i] = BOMB;
                bombLeft--;
            } else {
                m_map[rowIndex][i] = EMPTY;
            }
        }
    }
}

void CModel::CreateBlankRow(int rowIndex) {
    for (int i = 0; i < COLUMN_COUNT; i++) {
        m_map[rowIndex][i] = EMPTY;
    }
}

bool CModel::NeedUpdateDelay() {
    if (m_iLevel < 10) {
        return true;
    }
    if (m_iLevel < 100) {
        return m_iLevel % 10 == 0;
    }
    if (m_iLevel < 200) {
        return m_iLevel % 20 == 0;
    }
    if (m_iLevel < 300) {
        return m_iLevel % 50 == 0;
    }
    return m_iLevel % 100 == 0;
}

bool CModel::NeedUpdateBlockCount() {
    if (m_iBlankLineCount == COLUMN_COUNT - 1) {
        return false;
    }
    if (m_iLevel == 10) {
        return true;
    }
    if (m_iLevel == 50) {
        return true;
    }
    return m_iLevel % 100 == 0;
}

void CModel::NewGame() {
    m_bIsGameOver = false;

    m_iLevel = 0;
    m_iScore = 0;
    m_dUpdateDelay = 1.0;

    m_iBulletCount = 3;
    m_iBombCount = 1;

    m_iBlankLineCount = 3;
    m_iBlankLineLeft = m_iBlankLineCount;
    m_iBlockCount = 3;

    for (int i = 0; i < ROW_COUNT; ++i) {
        CreateRow(i);
    }

    m_iPlaneRow = 0;
    m_iPlaneColumn = 0;
    UpdatePlane();
}

void CModel::FireBullet() {
    if (m_iBulletCount == 0) return;
    m_iBulletCount--;

    for (int i = 0; i < ScreenYFromRow(m_iPlaneRow); i++) {
        int row = (m_iPlaneRow + i) % ROW_COUNT;
        if (m_map[row][m_iPlaneColumn] == BLOCK) {
            m_map[row][m_iPlaneColumn] = EMPTY;
            m_bIsChanged = true;
            return;
        }
    }
}

void CModel::FireBomb() {
    if (m_iBombCount == 0) return;
    m_iBombCount--;

    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COLUMN_COUNT; j++) {
            m_map[i][j] = EMPTY;
        }
    }
    UpdatePlane();
}

int CModel::RowFromScreenY(int y) {
    return (ROW_COUNT - 1 - y + m_iLevel) % ROW_COUNT;
}

int CModel::ScreenYFromRow(int row) {
    return (ROW_COUNT - 1 - (row - m_iLevel % ROW_COUNT)) % ROW_COUNT;
}