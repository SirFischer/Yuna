#pragma once

#include "core/Window.hpp"
#include "core/stateManager/StateManager.hpp"

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


