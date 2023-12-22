#include "MenuState.hpp"

MenuState::MenuState(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	std::cout << "Instantiated the menu state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mf::GUI::ClearWidgets();
	bool *active = &mActive;
	mf::GUI::AddWidget(mf::Button::Create()->SetClickEvent([active](){
		*active = false;
	})->SetPositionPercentage(true, false)->SetPosition(sf::Vector2f(45, 200))->SetBackground(sf::Color::Green));
}

MenuState::~MenuState()
{
	std::cout << "Destroyed the menu state" << std::endl;
}

void	MenuState::Init()
{
	
}

void	MenuState::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
	}
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
