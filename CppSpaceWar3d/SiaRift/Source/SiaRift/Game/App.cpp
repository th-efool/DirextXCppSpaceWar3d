#include "Game.h"
using namespace SiaRift;

SiaRift::Game::App()
{
	// Constructor implementation
}
SiaRift::Game::~App()
{
	// Destructor implementation
}

int SiaRift::Game::App::Run()
{
	// Main application loop
	while (true)
	{

		DoFrame();
	}
	return 0; // Return an exit code
}

void SiaRift::Game::App::DoFrame()
{
	// Frame processing logic
	// This could include updating game state, rendering, etc.
}