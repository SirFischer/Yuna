#pragma once
#include "Yuna.hpp"

class SplashState : public Yuna::Core::State
{
private:
	
public:
	SplashState(Yuna::Core::Window* tWindow);
	~SplashState();

	void	HandleEvents();
	void	Update();
	void	Render();
};

