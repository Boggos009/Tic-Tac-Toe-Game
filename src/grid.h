#pragma once
#include <raylib.h>
#include <iostream>

class Grid
{
private:
    float cellSize;
    int cellCount;
    bool CheckSimilarityH(int row);
    bool CheckSimilarityV(int column);
    bool CheckSimilarityD();
    bool CheckH(int row , int &xpos , bool &in);
    bool CheckV(int column, int &xpos , bool &win);

public:
    Grid();
    void Draw();
    void Initialize();
    int grid[3][3];
    void Print();
    bool CheckForWin();
    bool CheckForDraw();
    Vector2 onesPos();
    bool AllCellsAreTaken();
};