#pragma once  
#include "SiaRift/Core/Base.h"  
//#include <Windows.h> For us to use Win32 API functions and types
// Windows.h and our Window.h are complete different files.
// However Windows.h is BLOATED AS FUCK!!!, we'll import our custom DEBLOATED Windows.h
#include "SiaRift/Window/WindowsDebloated.h"

namespace SiaRift
{
	class Window :
		public Base
	{
	public:
		class WindowClass
		{
		public:
			WindowClass();
			~WindowClass();
			// Singleton pattern
			WindowClass(const WindowClass&) = delete; // no copy constructor
			WindowClass(WindowClass&&) = delete;      // no move constructor
			WindowClass& operator=(const WindowClass&) = delete; // no copy assignment operator
			WindowClass& operator=(WindowClass&&) = delete; // no move assignment operator
		};
		static WindowClass wndClass; // Static instance of WindowClass
	public: 
		Window();
		virtual ~Window() override;
		HWND hwnd;
	
	};
}

