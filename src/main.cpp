#include <raylib.h>
#include <iostream>
#include "game.h"
using namespace std;

Color white = {255,255,145,255};

int main() 
{
    InitWindow(480,480,"Tic-Tac-Toe");
    InitAudioDevice();
    SetTargetFPS(30);
    Game game= Game();
    
    while (WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(white);
        game.ActualGame();
        game.Draw();
        

        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}