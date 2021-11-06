#include "Window.hpp"

namespace Yuna
{
	namespace Core
	{
		Window::Window(/* args */)
		{
		}

		Window::~Window()
		{
		}


		/**
		 * Creation and destruction of window
		 **/
		void	Window::Create()
		{
			auto isFullscreen = (mFullscreen) ? sf::Style::Fullscreen : sf::Style::Default;
			sf::VideoMode	mode(mSize.x, mSize.y);
			mWindow.create(mode, mTitle, isFullscreen);
			mf::GUI::Init(&mWindow);
		}

		void	Window::Destroy()
		{
			mWindow.close();
		}


		/**
		 * Drawing Utilities
		 **/
		void	Window::Draw(sf::Drawable &tDrawable)
		{
			mWindow.draw(tDrawable);
		}

		void	Window::Draw(sf::Vertex *tVertex, size_t tSize, sf::PrimitiveType tType)
		{
			mWindow.draw(tVertex, tSize, tType);
		}


		void	Window::Clear()
		{
			Clear(sf::Color::Black);
		}

		void	Window::Clear(const sf::Color &tColor)
		{
			mWindow.clear(tColor);
		}

		void	Window::Render()
		{
			mWindow.display();
		}


		/**
		 * Events
		 **/
		bool	Window::PollEvent(sf::Event &tEvent)
		{
			bool res = mWindow.pollEvent(tEvent);
			if (tEvent.type == sf::Event::Resized)
				ResetView(true);
			return (res);
		}

		/**
		 * Setters
		 **/
		void	Window::SetSize(const sf::Vector2i &tSize)
		{
			mSize = tSize;
		}

		void	Window::SetTitle(const std::string &tTitle)
		{
			mTitle = tTitle;
		}

		void	Window::SetView(sf::View tView)
		{
			mWindow.setView(tView);	
		}

		sf::View	Window::GetView()
		{
			return(mWindow.getView());
		}

		void	Window::SetDefaultView()
		{
			sf::View	defaultView;
			defaultView = mWindow.getDefaultView();
			mWindow.setView(defaultView);	
		}

		void	Window::ResetView(bool tResize)
		{
			if (tResize)
				mWindow.setView(sf::View(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / 2), sf::Vector2f(mWindow.getSize())));
			else
				mWindow.setView(mWindow.getDefaultView());
		}
	} // namespace core
	
} // namespace Yuna

