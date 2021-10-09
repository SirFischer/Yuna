#pragma once
#include "Yuna.hpp"

class MenuState : public Yuna::Core::State
{
private:
	/* data */
public:
	MenuState(Yuna::Core::Window* tWindow);
	~MenuState();

	void	Init();
	void	HandleEvents();
	void	Update();
	void	Render();
};
