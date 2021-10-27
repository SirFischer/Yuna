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
			bool				mFullscreen = false;

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

			/**
			 * Camera
			 **/
			void			SetView(sf::View tView);
			void			GetView();
			void			SetDefaultView();
			bool			IsOpen(){return (mWindow.isOpen());}
			void			ResetView(bool tResize);
		};
	} // namespace core
} // namespace Yuna


