#pragma once

#include <SFML/Graphics.hpp>

#include "mfGUI.hpp"

namespace Yuna
{
	namespace Core
	{
		class Window
		{
		private:
			sf::RenderWindow	mWindow;

			std::string			mTitle = "Window title";
			sf::Vector2i		mSize = sf::Vector2i(1600, 900);
			uint16_t			mFPS = 0;
			bool				mFullscreen = false;
			bool				mVSync = false;

		public:
			Window(/* args */);
			~Window();

			/**
			 * Creation and destruction of window
			 **/
			void			Create();
			void			Destroy();

			/**
			 * Drawing Utilities
			 **/
			void			Draw(sf::Drawable &tDrawable);
			void			Draw(sf::Vertex *tVertex, size_t tSize, sf::PrimitiveType tType);
			void			Clear();
			void			Clear(const sf::Color &tColor);
			void			Render();

			/**
			 * Events
			 **/
			bool			PollEvent(sf::Event &tEvent);

			/**
			 * Setters
			 **/
			void			SetSize(const sf::Vector2i &tSize);
			void			SetTitle(const std::string &tTitle);
			void			SetFullscreen(const bool &tFullscreen);
			void			SetMaxFPS(uint16_t tFPS);
			void			SetVSync(const bool &tVSync);

			/**
			 * Getters
			 **/
			sf::Vector2u		GetSize(){return (mWindow.getSize());}
			sf::Vector2i		GetRelativeMousePos(){return (sf::Mouse::getPosition(mWindow));}
			sf::Vector2f		GetViewMousePos(){return (mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));}
			sf::RenderWindow*	GetRenderWindow(){return (&mWindow);}
			bool				IsFullscreen(){return (mFullscreen);}

			/**
			 * Camera
			 **/
			void			SetView(sf::View tView);
			sf::View		GetView();
			void			SetDefaultView();
			bool			IsOpen(){return (mWindow.isOpen());}
			void			ResetView(bool tResize);
		};
	} // namespace core
} // namespace Yuna


