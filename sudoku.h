#ifndef SUDOKU_H
#define SUDOKU_H 

#include <iostream>
#include <fstream>
using namespace std; 

#define GPU 1
#define CPU 0

class Sudoku
{
private:
    int* grid;
    int size;
    int boxSize;

public:
void initializeGrid(int type = 0)
{
        grid = new int[size * size];
//    else
        //cudaMalloc(&grid, size * size * sizeof(int)); 
}

void clearGrid()
{
    for (int i = 0; i < size * size; i++)
    {
        grid[i] = 0; 
    }
}

Sudoku(int size = 9)
//int type = 0)
{
    this->size = size; 
    this->boxSize = 3; 
    initializeGrid(); 
    clearGrid(); 
}
Sudoku(ifstream& fin, string filetype, int size = 9)
{
    this->size = size; 
    this->boxSize = 3; 
    initializeGrid(); 
    clearGrid(); 
    int row, col, value; 
    if(filetype.compare("list") == 0)
        while (!fin.eof())
        {
            fin >> row >> col >> value;
            insert(row, col, value);
        }
    else if (filetype.compare("matrix") ==0)
    {
        int counter = 0; 
        int temp; 
        while (!fin.eof())
        {
            fin >>  temp; 
            grid[counter] = temp; 
            counter++; 
        }
    }
}
~Sudoku()
{
    delete grid; 
}

bool insert(int row, int col, int value)
{
    if (grid[row * size + col] == 0)
    {
        grid[row * size + col] = value; 
        return true; 
    }
    return false; 
    
}

bool checkRow(int row, int value) 
{
    for (int i = 0; i < size; i++)
    {
        if (grid[row * size + i] == value)
            return false; 
    }
    return true; 
}
bool checkCol(int col, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (grid[i * size + col] == value)
            return false; 
    }
    return true; 
}
bool checkBox(int row, int col, int value)
{
    int x_0 = (col / boxSize) * boxSize; 
    int y_0 = (row / boxSize) * boxSize; 
    for(int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
        {
            if (grid[(y_0 + i) * size + (x_0 + j)] == value)
                return false; 
        }
    }
    return true; 
}
bool isPossible(int pos, int value)
{
    int col = pos % size; 
    int row = pos / size; 
    return checkBox(row, col, value) && checkRow(row, value) && checkCol(col, value); 
}

bool __solve(int pos, int depth)
{
    //cout << "depth: " << ++depth << endl; 
    if (pos >= size * size)
    {
        cout << "finished\n"; 
//        cout << *this << endl; 
        return true; 
    }
    if (grid[pos] != 0)
    {
        //cout << "skipping " << pos << endl; 
        return __solve(pos + 1, depth); 
    }
    if (grid[pos] == 0)
    {
        for (int i = 1; i <= size; i++)
        {
            if (isPossible(pos, i))
            {
                grid[pos] = i;
                //cout << *this << endl;
                if (__solve(pos + 1, depth))
                    return true;
                else
                    grid[pos] = 0;
            }
        }
        return false; 
    }
}

bool solve()
{
    return __solve(0, 0); 
}

void print(ostream& out)
{
    for (int i = 0; i < size; i++)
    {
        cout << i; 
        for (int j = 0; j < size; j++)
        {
            out << this->grid[i * size + j] << " ";
        }
        out << endl; 
    }
}

friend ostream& operator<<(ostream& out, const Sudoku& S); 
};

ostream& operator<<(ostream& out, const Sudoku& S)
{
    for (int i = 0; i < S.size; i++)
    {
        for (int j = 0; j < S.size; j++)
        {
            out << S.grid[i * S.size + j] << " ";
        }
        out << endl; 
    }
    return out; 
}

#endif
