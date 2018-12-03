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
const char GRAPH_SYM = '*';		//This char will be used to plot the scatter
const char VERT_SYM = '|';		//This char will be used to create vertical lines (y-axis && outline)
const char HORZ_SYM = '-';		//This char will be used to create horizontal lines (x-axis && outline)

//define functions
int* GetCoefficients(int&,int);			//Get information about the equation from the user
int GetPolyDegree(void);			//Get the degree of the polynominal from the user
void PrintGraphBorder(void);		//function will print the border outline of the graph
void GotoXY(int, int);				//set console cursor to specific location
void ResizeConsole(void);			//reset size of console
void PrintGraphHeader(string&);		//this function will print the header above the graph
int XCrossY(int&);					//function to determine where X should cross the Y axis (auto-scale)
int YCrossX(int&);					//function to determine where Y should cross the X axis (auto-scale)
int* XBound(int&);					//function to determine the bounds of the x-axis (auto-scale)
int* YBound(int&);					//function to determine the bounds of the y-axis (auto-scale)
void PrintAxes(void);				//function to print the x-y axes
void PrintPoly(int&,int);			//function to print polynomial


/*
	Function: PrintPoly
	Input: pointer int, in
	Return: void -- Print graph to the console

	Description: prints the graph out to the console
*/
void PrintPoly(int *equ, int deg) {
	static const int yDefault = 10;			//Set the graph to offset 20 lines down on console
	static const int xDefault = 5;			//Set graph to offset 5 chars to the right on console
	const int xBound = 60; 					//origin plus/minus bound
	const int yBound = 30;					//origin plus/minus bound
	int xOrigin = X_RES / 2 + xDefault;		//x origin to be in center of graph border
	int yOrigin = Y_RES / 4 + yDefault;		//y origin to be in center of graph border
	float yData[120] = {};
	float y = 0.0;

	//first thing we need to do is load up our graphData with the polynomial
	//load y values
	for (int j = 0; j < 120; j++) {
		switch (deg) {
			case 1:
				yData[j] = equ[1] * (j - xBound) + equ[0];
				break;
			case 2:
				yData[j] = equ[2] * pow((j - xBound),2) + equ[1] * (j - xBound) + equ[0];
				break;
			case 3:
				yData[j] = equ[3] * pow((j - xBound), 3) + equ[2] * pow((j - xBound), 2) + equ[1] * (j - xBound) + equ[0];
				break;
		}
	}
	//now we need to print the info on the graph
	for (int i = 0; i < 120; i+=2) {
		if (abs(yData[i]/2) < yBound) {
			GotoXY(xOrigin - xBound + i, yOrigin - yData[i] / 2);
			cout << GRAPH_SYM;
		}
	}
}
/*
	Function: PrintAxes
	Input: pointer
	Return: void -- Print axes to the console

	Description: Uses the X_RES and Y_RES values to print a border of where the graph will sit
*/
void PrintAxes() {
	static const int yDefault = 10;			//Set the graph to offset 20 lines down on console
	static const int xDefault = 5;			//Set graph to offset 5 chars to the right on console

	int xOrigin = X_RES/2 + xDefault,		//x origin to be in center of graph border
		yOrigin = Y_RES/4 + yDefault,		//y origin to be in center of graph border
		xBound = 60,						//origin plus/minus bound
		yBound = 30;						//origin plus/minus bound

	int scale;
	
	//print x axis first
	for (int i = 0; i <= (xBound * 2); i++) {
		GotoXY(xOrigin - xBound + i, yOrigin);
		cout << HORZ_SYM;
	}

	//print y axis next
	for (int i = 0; i <= (yBound * 2); i++) {
		GotoXY(xOrigin, yOrigin - yBound + i);
		cout << VERT_SYM;
	}

	//print out x scale
	for (int i = 0; i <= xBound * 2; i += 10) {
		GotoXY(xOrigin - xBound + i, yOrigin + 1);
		scale = -1 * xBound + i;
		if (scale != 0) {
			cout << scale;
		}
	}

	//print out y scale
	for (int i = 0; i <= yBound * 4; i += 10) {
		GotoXY(xOrigin + 1, yOrigin - yBound + i/2);
		scale = -1 * yBound * 2 + i;
		if (scale != 0) {
			cout << scale;
		}
	}

}

/*
	Function: PrintGraphBorder
	Input: void
	Return: void -- Printout to the console

	Description: Uses the X_RES and Y_RES values to print a border of where the graph will sit
*/
void PrintGraphBorder(void) {
	static const int yDefault = 10;		//Set the graph to offset 20 lines down on console
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
	for (int i = 1; i < (Y_RES/2 - 1); i++) {
		GotoXY(xDefault, yDefault + yOffset);	//Go to print location
		cout << VERT_SYM;						//Print the vertical symbol			
		yOffset--;								//decrease offset to go to next position
	}
	GotoXY(0, 0);		//put back to default position
}

/*
	Function: PrintGraphHeadder
	Input: String -- value to be used as header
	Return: void

	Description: Uses the X_RES and Y_RES values to print a border of where the graph will sit
*/
void PrintGraphHeader(string s) {
	int xPos;
	
	xPos = (X_RES/2) - (s.length()/2) + 5;

	GotoXY(xPos, 9);
	cout << s;
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

/*
	Function: Get Coefficients
	Input: deference int, int
	Return: int ptr

	Description: accepts pointer to first location of array, loads and returns array via ptr
*/
int* GetCoefficients(int* _coeff, int degree) {


	if (degree > MAX_POLY_SIZE) {
		cout << "Polynominal must be degree of " << MAX_POLY_SIZE << " or less..." << endl << endl;
		return 0;		//end program
	}
	else if (degree < 0) {
		cout << "Bro, polynominals can't be negative.. " << endl << endl;
		return 0;		//end program
	}
	else if (degree == 0) {
		cout << "No point in graphing a constant value of 0..." << endl << endl;
		return 0;		//end program
	}

	cout << endl << "Enter the coeff separated by spaces (start w/ lowest degree): ";
	for (int i = 0; i < degree + 1; i++) {
		cin >> _coeff[i];
	}
	cout << endl << "Your polynominal is y = ";
	for (int i = degree; i >= 0; i--) {
		if (!i) {
			cout << _coeff[i] << endl;
		}
		else {
			cout << _coeff[i] << "x^" << i << " + ";
		}
	}
	return _coeff;
}

/*
	Function: Get Degree of Polynomial
	Input: void
	Return: int 

	Description: asks user for poly degree and returns degree #
*/
int GetPolyDegree(void) {
	int polyDegree;

	//Get info from user
	cout << "Please Enter Degree of Polynominal: ";
	cin >> polyDegree;

	return polyDegree;
}

int main(void)
{
	//define variables for main
	int polyDegree;
	int coeff[MAX_POLY_SIZE+1];		//needs to be size of polynominal degree + constant

	//init console size
	ResizeConsole();
	//Get polynominal degree from user
	polyDegree = GetPolyDegree();
	//Get coeff from user
	GetCoefficients(&coeff[0], polyDegree);
	//Print the border of the graph
	PrintGraphBorder();
	//Print the header of the graph
	PrintGraphHeader("Polynomial Graph: X vs. Y");
	//Print graph axes
	PrintAxes();
	//Print the polynomial on the graph
	PrintPoly(&coeff[0],polyDegree);


	GotoXY(0,Y_RES/2 + 20);
	system("pause");
	return 0;
}
