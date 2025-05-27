#pragma once
#include "SiaRift/Core/Base.h"
#include "SiaRift/Window/Window.h"



namespace SiaRift
{
	class App :
		public Base
	{
	public:
		int Run();
	private:
		void DoFrame();

	public:
		App();
		virtual ~App() override;
		Window window;
	};
}


