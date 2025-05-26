#include "Window.h"
#include "SiaRift/Window/Window.h"
using namespace SiaRift;

SiaRift::Window::WindowClass SiaRift::Window::WindowClass::wndClass; // Static instance of WindowClass



HINSTANCE SiaRift::Window::WindowClass::getInstance()  
{  
   return wndClass.hinstance; // Access the static instance to retrieve hinstance  
}

SiaRift::Window::WindowClass::WindowClass() : hinstance(GetModuleHandle(nullptr))
{
	// Constructor implementation
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc; // Default window procedure
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = name;
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
	windowSiaRect = SiaRift::SiaRect(800, 600); // Default window size
	RECT rect{ windowSiaRect.left,windowSiaRect.top, windowSiaRect.right(), windowSiaRect.bottom()}; // Default window size
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); // Adjust the window rectangle to account for the window style

	// Constructor implementation
	hwnd = CreateWindowEx(
		0, // Optional window styles
		getName(), // Window class
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
SiaRift::Window::~Window()
{
	// Destructor implementation
	if (hwnd)
	{
		DestroyWindow(hwnd);
		hwnd = nullptr;
	}
}


std::optional<int> SiaRift::Window::WindowClass::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam; // Return the exit code
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {}; // No message processed
}

