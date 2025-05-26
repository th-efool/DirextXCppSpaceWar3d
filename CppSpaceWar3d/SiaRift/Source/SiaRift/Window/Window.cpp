#include "Window.h"
#include "SiaRift/Window/Window.h"
using namespace SiaRift;

SiaRift::Window::WindowClass::WindowClass()
{
	// Constructor implementation
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc; // Default window procedure
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"SiaRiftWindowClass";
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName = nullptr;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		// Handle error if registration fails
		throw std::runtime_error("Failed to register window class");
	}

}

SiaRift::Window::WindowClass::~WindowClass()
{
	// Destructor implementation
	UnregisterClass(L"SiaRiftWindowClass", GetModuleHandle(nullptr));
}

SiaRift::Window::Window()
{
	RECT rect{ 0,0, 800, 600 }; // Default window size


	// Constructor implementation
	hwnd = CreateWindowEx(
		0, // Optional window styles
		L"SiaRiftWindowClass", // Window class
		L"SiaRift Application", // Window text
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT, CW_USEDEFAULT, // don't use rect.left that doesn't represent position, use CW_USEDEFAULT instead
		rect.right-rect.left, rect.bottom - rect.top, //  size 
		nullptr, // Parent window
		nullptr, // Menu
		GetModuleHandle(nullptr), // Instance handle
		this // Additional application data
	);
	if (!hwnd)
	{
		throw std::runtime_error("Failed to create window");
	}
	ShowWindow(hwnd, SW_SHOWDEFAULT);
}