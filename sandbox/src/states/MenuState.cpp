#include "MenuState.hpp"

MenuState::MenuState(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	std::cout << "Instantiated the menu state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mf::GUI::ClearWidgets();
	bool *active = &mActive;
	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Green, sf::Color::Red)->SetClickEvent([active](){
		*active = false;
	})->SetPositionPercentage(true, false)->SetPosition(sf::Vector2f(45, 200)));
}

MenuState::~MenuState()
{
	std::cout << "Destroyed the menu state" << std::endl;
}

void	MenuState::HandleEvents()
{
	mEventHandler.HandleEvent();
}

void	MenuState::Update()
{

}

void	MenuState::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}
