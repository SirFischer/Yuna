#include "Window.hpp"

namespace Yuna
{
	namespace Core
	{
		Window::Window(/* args */)
		{
			mf::GUI::Init(&mWindow);
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
			if (mFPS)
				mWindow.setFramerateLimit(mFPS);
			mWindow.setVerticalSyncEnabled(mVSync);
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
			mRenderTexture.draw(tDrawable);
		}

		void	Window::Draw(sf::Drawable &tDrawable, const sf::RenderStates &tStates)
		{
			mRenderTexture.draw(tDrawable, tStates);
		}

		void	Window::Draw(sf::Vertex *tVertex, size_t tSize, sf::PrimitiveType tType)
		{
			mRenderTexture.draw(tVertex, tSize, tType);
		}


		void	Window::Clear()
		{
			Clear(sf::Color::Black);
		}

		void	Window::Clear(const sf::Color &tColor)
		{
			mRenderTexture.clear(tColor);
		}

		void	Window::Render()
		{
			mRenderTexture.display();
			mWindow.draw(sf::Sprite(mRenderTexture.getTexture()));
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

		void	Window::SetFullscreen(const bool &tFullscreen)
		{
			mFullscreen = tFullscreen;
			Create();
		}

		void	Window::SetMaxFPS(uint16_t tFPS)
		{
			mFPS = tFPS;
			mWindow.setFramerateLimit(mFPS);
		}

		void	Window::SetVSync(const bool &tVSync)
		{
			mWindow.setVerticalSyncEnabled(tVSync);
			mVSync = tVSync;
		}


		void	Window::SetView(sf::View tView)
		{
			mRenderTexture.setView(tView);	
		}

		sf::View	Window::GetView()
		{
			return(mRenderTexture.getView());
		}

		void	Window::SetDefaultView()
		{
			sf::View	defaultView;
			defaultView = mRenderTexture.getDefaultView();
			mRenderTexture.setView(defaultView);	
		}

		void	Window::SetCursorVisibility(const bool &tVisibility)
		{
			mWindow.setMouseCursorVisible(tVisibility);
		}


		void	Window::ResetView(bool tResize)
		{
			if (tResize)
				mRenderTexture.setView(sf::View(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / 2), sf::Vector2f(mWindow.getSize())));
			else
				mRenderTexture.setView(mRenderTexture.getDefaultView());
		}
	} // namespace core
	
} // namespace Yuna

