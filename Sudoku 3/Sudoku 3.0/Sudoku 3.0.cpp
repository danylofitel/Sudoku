// Sudoku 3.0.cpp : main project file.

#include "stdafx.h"
#include "Sudoku 3.0.h"

using namespace Sudoku_3_0;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew SudokuForm());
	return 0;
}
