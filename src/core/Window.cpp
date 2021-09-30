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
		bool	Window::HandleEvent(sf::Event &tEvent)
		{
			return (mWindow.pollEvent(tEvent));
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
	} // namespace core
	
} // namespace Yuna

