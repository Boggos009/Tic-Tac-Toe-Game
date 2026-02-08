#pragma once
#include "grid.h"
#include <raylib.h>
#include <iostream>
#include <cmath>
class Game
{
private:
    Grid grid;
    int xValue;
    int oValue;
    bool player;
    Texture2D xImage; 
    Texture2D oImage;
    bool gameOver;
    bool computerMoved;
    bool Update(int row , int column);
    void Press();
    void GameReset();
    Sound winner;
    Sound tie;
    Sound lose;
public:
    Game();
    ~Game();
    void Draw();
    void ActualGame();
};