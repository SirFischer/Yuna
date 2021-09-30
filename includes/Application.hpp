#pragma once

#include "Window.hpp"

namespace Yuna
{
	class Application
	{
	protected:
		Core::Window	mWindow;
		
	public:
		Application();
		~Application();

		void	Run();
	};
} // namespace Yuna


