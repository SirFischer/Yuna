#pragma once

#include "core/Window.hpp"
#include "core/stateManager/StateManager.hpp"
#include "core/console/Console.hpp"

namespace Yuna
{
	class Application
	{
	protected:
		Core::Window		mWindow;
		Core::StateManager	mStateManager;
		
	public:
		Application();
		~Application();

		void	Run();
	};
} // namespace Yuna


