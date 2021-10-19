#include "SplashState.hpp"

SplashState::SplashState(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	std::cout << "Instantiated the splash state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::REPLACE_STATE;
	mNextState = 0;
}

SplashState::~SplashState()
{
	std::cout << "Destroyed the splash state" << std::endl;
}

void	SplashState::Init()
{
	
}

void	SplashState::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
	}
}

void	SplashState::Update()
{
	if (mDuration.getElapsedTime() > sf::seconds(5))
		mActive = false;
}

void	SplashState::Render()
{
	mWindow->Clear();
	mWindow->Render();
}
