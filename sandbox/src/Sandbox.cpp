#include "Sandbox.hpp"

std::unique_ptr<Yuna::Core::State>	stateFactory(uint8_t tID, Yuna::Core::Window* tWindow)
{
	switch (tID)
	{
		case 0:
			return (std::make_unique<MenuState>(tWindow));
		break;
		case 1:
			return (std::make_unique<SplashState>(tWindow));
		break;
		default:
		break;
	}
	return (nullptr);
}

Sandbox::Sandbox(/* args */)
{
	mWindow.SetTitle("Sandbox");
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(1);
}

Sandbox::~Sandbox()
{
}