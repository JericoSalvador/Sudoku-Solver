
#include<iostream> 
#include<fstream> 
#include "sudoku.h"

using namespace std;

int main()
{
	try 
	{
		ifstream fin("matrix2.txt"); 
		Sudoku S(fin, "matrix"); 
		cout << S << endl; 
		cout << "solve: " << S.solve() << endl;
		cout << S << endl; 
		
	}
	catch (exception e)
	{
		cerr << e.what(); 
	}
}
