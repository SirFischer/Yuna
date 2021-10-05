#include "MenuState.hpp"

MenuState::MenuState(/* args */)
{
	std::cout << "Instantiated the menu state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::EXIT;
}

MenuState::~MenuState()
{
	std::cout << "Destroyed the menu state" << std::endl;
}