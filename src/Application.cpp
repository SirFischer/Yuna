#include "Application.hpp"

namespace Yuna
{
	Application::Application(/* args */)
	:mStateManager(&mWindow)
	{
		
	}

	Application::~Application()
	{
		
	}

	void	Application::Run()
	{
		mWindow.Create();
		mStateManager.Run();
	}

} // namespace Yuna

