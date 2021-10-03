#include "Game.hpp"

std::unique_ptr<Yuna::Core::State>	stateFactory(uint8_t tID)
{
	switch (tID)
	{
		case 0:
			return (std::make_unique<MenuState>());
		break;
		case 1:
			return (std::make_unique<SplashState>());
		break;
		default:
		break;
	}
	return (nullptr);
}

Game::Game(/* args */)
{

	mWindow.SetTitle("Sandbox");
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(1);
}

Game::~Game()
{
}