#include "SiaRift/Game/App.h"
#include "SiaRift/Window/Window.h"

using namespace SiaRift;

SiaRift::App::App()
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
		if (std::optional<int> returnvalue = Window::ProcessMessage()) { return *returnvalue; }
		DoFrame();
	}
	return 0; // Return an exit code
}

void SiaRift::App::DoFrame()
{
	// Frame processing logic
	// This could include updating game state, rendering, etc.
}