#pragma once
#include "Yuna.hpp"

class SplashState : public Yuna::Core::State
{
private:
	sf::Clock	mDuration;
public:
	SplashState(Yuna::Core::Window* tWindow);
	~SplashState();

	void	Init();
	void	HandleEvents();
	void	Update();
	void	Render();
};

