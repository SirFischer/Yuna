#include "MenuState.hpp"

MenuState::MenuState(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	std::cout << "Instantiated the menu state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mf::GUI::ClearWidgets();
	bool *active = &mActive;
	auto button = mf::Button::Create();
	button->SetClickEvent([active](){
		*active = false;
		std::cout << "Button clicked, exiting menu state" << std::endl;
	});
	button->SetPositionPercentage(true, false);
	button->SetPosition(sf::Vector2f(45, 100));
	button->GetBackground()->SetBackground(sf::Color::Red);
	mf::GUI::AddWidget(button);
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
	mWindow->Display();
}
