#include "game.h"


Game::Game() : grid()
{
    gameOver = false;
    computerMoved = false;
    xValue = 1;
    oValue= 2;
    player = true;
    Image xx   = LoadImage("x_1.png");
    ImageResize(&xx , 180 , 180);
    xImage = LoadTextureFromImage(xx);
    UnloadImage(xx);

    
    Image oo   = LoadImage("o_1.png");
    ImageResize(&oo , 180 , 180);
    oImage = LoadTextureFromImage(oo);
    UnloadImage(oo);

    winner = LoadSound("win.mp3");
    tie = LoadSound("Tie.mp3");
    lose = LoadSound("Lose.mp3");
}

Game::~Game()
{
    UnloadTexture(xImage);
    UnloadTexture(oImage);
    UnloadSound(winner);
    UnloadSound(tie);
    UnloadSound(lose);
}

void Game::Draw()
{
    grid.Draw();
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            if (grid.grid[row][column] == xValue)
            {
                DrawTexture(xImage, -20 + column * 160, -20 + row * 160, WHITE);
            }
            else if (grid.grid[row][column] == oValue)
            {
                DrawTexture(oImage, -20 + column * 160, 15+row * 160, WHITE);
            }
        }
    }
}

bool Game::Update(int rowx , int columny)
{
    for(int row= 0; row<3; row++)
    {
        for(int column = 0; column<3; column++)
        {
            if(row==rowx && column==columny)
            {
                if(grid.grid[row][column]==0 )
                {
                    if(player)
                    {
                        grid.grid[row][column] = xValue;
                        if(grid.CheckForWin())
                        {
                            PlaySound(winner);
                            gameOver = true;
                        }
                        else grid.Print();
                    }
                    else
                    {
                        grid.grid[row][column] = oValue;
                        if(grid.CheckForWin())
                        {
                            PlaySound(lose);
                            gameOver = true;
                        }
                        
                        else grid.Print();
                    }
                    player = !player;
                }
                else return false;
            }
        }
    }
    return true;
}



void Game::Press()
{
    Vector2 mousePosition =GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if(mousePressed && !gameOver)
    {
        int column = (mousePosition.x/160);
        int row = (mousePosition.y/160);
        bool lol = Update(std::min(row,2) ,std::min(column , 2) );
        while(!lol)
        {
            mousePosition = GetMousePosition();
            mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            column = (mousePosition.x/160);
            row= (mousePosition.y/160);
            lol = Update(std::min(row,2) ,std::min(column , 2) );
        }
    }
    
}

void Game::GameReset()
{
    grid.Initialize();
    gameOver = false;
    computerMoved = false;
    player = true;
}

void Game::ActualGame()
{
    if(!gameOver)
    {
        if(grid.AllCellsAreTaken())
        {
            PlaySound(tie);
            gameOver= true;
            GameReset();
        }
        if(player)
        {
            computerMoved = false;
            Press();
        }
        else
        {
            if(!computerMoved)
            {
                Vector2 pos = grid.onesPos();
                Update(pos.x , pos.y);
                computerMoved = true;
            }
        }    
    }
    else
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GameReset();
        }
    }
}