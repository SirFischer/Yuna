#include "SplashState.hpp"

SplashState::SplashState(/* args */)
{
	std::cout << "Instantiated the splash state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
	mNextState = 0;
}

SplashState::~SplashState()
{
	std::cout << "Destroyed the splash state" << std::endl;
}