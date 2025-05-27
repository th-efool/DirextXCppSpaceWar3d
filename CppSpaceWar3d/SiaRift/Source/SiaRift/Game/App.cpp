#include "SiaRift/Game/App.h"

using namespace SiaRift;

SiaRift::App::App() : window() // Initialize the Window member
{
	// Constructor implementation
}
SiaRift::App::~App()
{
	// Destructor implementation
}

int SiaRift::App::Run()
{
	// Main application loop
	while (true)
	{
		if (const auto returnvalue = Window::ProcessMessage()) {
			if (returnvalue == 0) {}
			else {
				return returnvalue
					;
			};
		}
		DoFrame();
	}
	return 0; // Return an exit code
}

void SiaRift::App::DoFrame()
{
	// Frame processing logic
	// This could include updating game state, rendering, etc.
}