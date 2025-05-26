#pragma once  
#include "SiaRift/Core/Base.h"  
//#include <Windows.h> For us to use Win32 API functions and types
// Windows.h and our Window.h are complete different files.
// However Windows.h is BLOATED AS FUCK!!!, we'll import our custom DEBLOATED Windows.h
#include "SiaRift/Window/WindowsDebloated.h"
#include "SiaRift/Math/SiaMath.h"

namespace SiaRift
{
	class Window :
		public Base
	{

	public:
		Window();
		virtual ~Window() override;
		static std::optional<int> ProcessMessage();
		HWND hwnd;
		SiaRect windowSiaRect;


	public:
		class WindowClass
		{
		public:
			static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
//			static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
			static LPCWSTR getName();
			static HINSTANCE getInstance();
		private:
			WindowClass();
			~WindowClass();
			// Singleton pattern
			WindowClass(const WindowClass&) = delete; // no copy constructor
			WindowClass(WindowClass&&) = delete;      // no move constructor
			WindowClass& operator=(const WindowClass&) = delete; // no copy assignment operator
			WindowClass& operator=(WindowClass&&) = delete; // no move assignment operator
			static WindowClass wndClass; // Static instance of WindowClass
			HINSTANCE hinstance;
			LPCWSTR name;
		};

	};
}

