// ConsolePolynominalGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"			//VS 2017 needs to compile
#include <iostream>			//cin/cout
#include <string>			//used for string operations
#include <cmath>			//for math operations
#include <windows.h>		//used for console cursor manipulation


//For ease of syntax
using namespace std;

//Preprocessor Directive
#define X_RES 128			//define graph size of X direction
#define Y_RES 128			//define graph size of Y direction
#define MAX_POLY_SIZE 3		//define max size of polynominal

//Define char's used for creating graph and
const char GRPAH_SYM = '*';		//This char will be used to plot the scatter
const char VERT_SYM = '|';		//This char will be used to create vertical lines (y-axis && outline)
const char HORZ_SYM = '-';		//This char will be used to create horizontal lines (x-axis && outline)

//define functions
void PrintGraphBorder(void);		//function will print the border outline of the graph
void GotoXY(int, int);				//set console cursor to specific location
void ResizeConsole(void);			//reset size of console
void PrintGraphHeader(string&);		//this function will print the header above the graph
int XCrossY(int&);					//function to determine where X should cross the Y axis (auto-scale)
int YCrossX(int&);					//function to determine where Y should cross the X axis (auto-scale)
int* XBound(int&);					//function to determine the bounds of the x-axis (auto-scale)
int* YBound(int&);					//function to determine the bounds of the y-axis (auto-scale)

/*
	Function: PrintGraphBorder
	Input: void
	Return: void -- Printout to the console

	Description: Uses the X_RES and Y_RES values to print a border of where the graph will sit
*/
void PrintGraphBorder(void) {
	static const int yDefault = 20;		//Set the graph to offset 20 lines down on console
	static const int xDefault = 5;		//Set graph to offset 5 chars to the right on console
	static int xOffset = 0;				//X offset
	static int yOffset = 0;				//Y offset

	//Print the top of the border
	for (int i = 0; i < (X_RES - 1); i++) {
		GotoXY(xDefault + xOffset, yDefault);	//Go to print location
		cout << HORZ_SYM;						//Print the horizontal symbol
		xOffset++;								//Increase offset to go to next position
	}
	//Print the right side of the border
	xOffset--;
	for (int i = 0; i < (Y_RES/2 - 1); i++) {
		GotoXY(xDefault + xOffset, yDefault + yOffset + 1);	//Go to print location
		cout << VERT_SYM;								//Print the vertical symbol
		yOffset++;										//Increase the y offset to go to next position
	}
	//Print the bottom of the border
	for (int i = 0; i < (X_RES - 1); i++) {
		GotoXY(xDefault + xOffset, yDefault + yOffset);	//Go to print location
		cout << HORZ_SYM;								//Print the horizontal symbol
		xOffset--;										//decrease offset to go to next position
	}
	yOffset--;
	//Print the left side of the border
	for (int i = 0; i < (Y_RES/2 - 1); i++) {
		GotoXY(xDefault, yDefault + yOffset);	//Go to print location
		cout << VERT_SYM;						//Print the vertical symbol			
		yOffset--;								//decrease offset to go to next position
	}
	GotoXY(0, 0);		//put back to default position
}

/*
	Function: GotoXY
	Input: int x, int y
	Return: void -- Set Cursor Location

	Description: Uses the X_RES and Y_RES values to print a border of where the graph will sit
*/
void GotoXY(int x, int y)
{
	COORD coord;		//create instance of COORD class
	coord.X = x;		//define x cursor position
	coord.Y = y;		//define y cursor position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	//set cursor location
}

/*
	Function: Resize Console
	Input: void
	Return: void

	Description: Resizes the console when executing program
*/
void ResizeConsole(void)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1200, 1000, TRUE); // 1200 width, 1000 height
}

int main(void)
{
	//define variables for main
	unsigned short int polyDegree;
	int coeff[MAX_POLY_SIZE];

	//init console size
	ResizeConsole();
	
	//Get info from user
	std::cout << "Please Enter Degree of Polynominal: "; 
	cin >> polyDegree;
	
	if (polyDegree > MAX_POLY_SIZE) {
		cout << "Polynominal must be degree of " << MAX_POLY_SIZE << " or less..." << endl << endl;
		return 0;		//end program
	}
	else if (polyDegree < 0) {
		cout << "Bro, polynominals can't be negative.. " << endl << endl;
		return 0;		//end program
	}
	else if (polyDegree == 0) {
		cout << "No point in graphing a constant value of 0..." << endl << endl;
		return 0;		//end program
	}
	
	cout << endl << "Enter the coeff separated by spaces (start w/ lowest degree): ";
	for (int i = 0; i < polyDegree; i++) {
		cin >> coeff[i];
	}
	cout << endl << "Your polynominal is y = ";
	for (int i = polyDegree-1; i >=0; i++) {
		cout << coeff[i] << "x^" << i + 1 << " ";
	}
	

	PrintGraphBorder();

	system("pause");
	return 0;
}
