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
			mTexture.create(mSize.x, mSize.y);
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
			mWindow.draw(tDrawable);
		}

		void	Window::Draw(sf::Drawable &tDrawable, const sf::RenderStates &tStates)
		{
			mWindow.draw(tDrawable, tStates);
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

		void	Window::Render(sf::Shader *tShader)
		{
			mTexture.update(mWindow);
			mSprite.setTexture(mTexture);
			mSprite.setPosition(0, 0);
			mWindow.clear();
			tShader->setUniform("texture", sf::Shader::CurrentTexture);
			mWindow.draw(mSprite, tShader);
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

		void	Window::SetCursorVisibility(const bool &tVisibility)
		{
			mWindow.setMouseCursorVisible(tVisibility);
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

