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
			bool			HandleEvent(sf::Event &tEvent);

			/**
			 * Setters
			 **/
			void			SetSize(const sf::Vector2i &tSize);
			void			SetTitle(const std::string &tTitle);
		};
	} // namespace core
} // namespace Yuna


