#include "grid.h"

Grid::Grid()
{
    cellCount = 9;
    cellSize = 160;
    Initialize();
    
}

void Grid::Draw()
{
    for(int row =0;row<3;row++)
    {
        for(int column = 0; column<3; column++)
        {
            DrawRectangleLinesEx({column*cellSize , row*cellSize , cellSize , cellSize} , 2 , BLACK );
        }
    }
}

void Grid::Initialize()
{
    for(int row = 0; row<3;row++)
    {
        for(int column=0; column<3; column++ )
        {
            grid[row][column] =0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row<3;row++)
    {
        for(int column=0; column<3; column++ )
        {
            std::cout<<grid[row][column]<<' ';
        }
        std::cout<<'\n';
    }
}


bool Grid::CheckSimilarityH(int row)
{
    int first = grid[row][0];
    if(first==0) return false;
    for(int column=1 ; column<3; column++)
    {
        if(grid[row][column]!=first)
        {
            return false;
        }
    }
    return true;
}

bool Grid::CheckSimilarityV(int column)
{
    int first = grid[0][column];
    if(first==0) return false;
    for(int row=1; row<3;row++)
    {
        if(grid[row][column]!=first) return false;
    }
    return true;
}

bool Grid::CheckSimilarityD()
{
    // Check main diagonal (top-left to bottom-right)
    int first = grid[0][0];
    if(first!=0)
    {
        bool mainDiagMatch = true;
        for(int i=0 , j=0; i<3&&j<3; i++,j++)
        {
            if(grid[i][j]!=first) 
            {
                mainDiagMatch = false;
                break;
            }
        }
        if(mainDiagMatch) return true;
    }

    // Check anti-diagonal (top-right to bottom-left)
    first = grid[0][2];
    if(first!=0)
    {
        bool antiDiagMatch = true;
        for(int i=0 , j=2; i<3&&j>=0; i++,j--)
        {
            if(grid[i][j]!=first) 
            {
                antiDiagMatch = false;
                break;
            }
        }
        if(antiDiagMatch) return true;
    }

    return false;
}



bool Grid::CheckForWin()
{
    for(int row =0; row<3; row++)
    {
        if(CheckSimilarityH(row))
        {
            return true;
        }
    }

    for(int column=0; column<3; column++)
    {
        if(CheckSimilarityV(column)) return true;
    }

    if(CheckSimilarityD()) return true;
    else return false;
}

bool Grid::CheckForDraw()
{
    for(int row = 0; row<3; row++)
    {
        for(int column = 0; column<3; column++)
        {
            if(grid[row][column] == 0) return false;
        }
    }
    return true;
}

bool Grid::CheckH(int row , int &xpos , bool &win)
{
    int xtimes =0 , otimes=0 , zerotimes= 0;
    for(int column = 0; column<3; column++)
    {
        if(grid[row][column]==0)
        {
            zerotimes++;
            xpos = column;
        }
        else if (grid[row][column] ==1) xtimes++;
        else otimes++;
    }
    if(otimes==2&&zerotimes==1)
    {
        win = true;
        return true;
    } 
    if(xtimes==2 && zerotimes==1) return true;
    

    return false;
}

bool Grid::CheckV(int column , int &ypos , bool &win)
{
    int xtimes =0 , otimes=0 , zerotimes= 0;
    for(int row = 0; row<3; row++)
    {
        if(grid[row][column]==0)
        {
            zerotimes++;
            ypos = row;
        }
        else if (grid[row][column] ==1) xtimes++;
        else otimes++;
    }
    if(otimes==2&&zerotimes==1)
    {
        win = true;
        return true;
    } 
    if(xtimes==2 && zerotimes==1) return true;
    
    return false;
}


Vector2 Grid::onesPos()
{
    bool winH = false , winV= false;
    int xpos = 0 , ypos=0;
    
    // Priority 1: Check horizontal for winning move or block
    for(int row=0; row<3; row++)
    {
        if(CheckH(row ,xpos , winH))
        {
            return Vector2{(float)row, (float)xpos};
        }
    }
    
    // Priority 2: Check vertical for winning move or block
    for(int column =0; column<3; column++)
    {
        if(CheckV(column , ypos , winV))
        {
            return Vector2{(float)ypos, (float)column};
        }
    }
    
    // Priority 3: Check diagonal 1 (top-left to bottom-right)
    int xD = 0 , oD=0 , zD=0;
    Vector2 emptyDiag1 = {0,0};
    for(int i=0 , j=0; i<3 &&j<3; i++,j++)
    {
        if(grid[i][j]==0)
        {
            zD++;
            emptyDiag1 = {(float)i, (float)j};
        }
        else if(grid[i][j]==1)
        {
            xD++;
        }
        else oD++;
    }
    if(oD==2&&zD==1) return emptyDiag1;
    if(xD==2 &&zD==1) return emptyDiag1;
    
    // Priority 4: Check diagonal 2 (top-right to bottom-left)
    xD=0; oD=0; zD=0;
    Vector2 emptyDiag2 = {0,0};
    for(int i=0 , j=2 ; i<3 &&j>=0; i++ , j--)
    {
        if(grid[i][j]==0)
        {
            zD++;
            emptyDiag2 = {(float)i, (float)j};
        }
        else if (grid[i][j]==1)
        {
            xD++;
        }
        else oD++;
    }
    if(oD==2&&zD==1) return emptyDiag2;
    if(xD==2 &&zD==1) return emptyDiag2;
    
    // Priority 5: Find any empty cell
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(grid[i][j] == 0)
            {
                return Vector2{(float)i, (float)j};
            }
        }
    }
    
    return Vector2{0, 0};
}

bool Grid::AllCellsAreTaken()
{
    for(int row=0; row<3; row++)
    {
        for(int column =0; column<3; column++)
        {
            if(grid[row][column] ==0)
            {
                return false;
            }
        }
    }
    return true;
}
