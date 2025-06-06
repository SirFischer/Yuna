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
			sf::Texture			mTexture;
			sf::Sprite			mSprite;

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
			void			Draw(sf::Drawable &tDrawable, const sf::RenderStates &tStates);
			void			Draw(sf::Vertex *tVertex, size_t tSize, sf::PrimitiveType tType);
			void			Clear();
			void			Clear(const sf::Color &tColor);
			void			Display();
			void			Display(sf::Shader *tShader);

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
			void			SetCursorVisibility(const bool &tVisibility);

			/**
			 * Getters
			 **/
			sf::Vector2u		GetSize(){return (mWindow.getSize());}
			sf::Vector2i		GetRelativeMousePos(){return (sf::Mouse::getPosition(mWindow));}
			sf::Vector2f		GetViewMousePos(){return (mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));}
			sf::RenderWindow*	GetRenderWindow(){return (&mWindow);}
			uint16_t			GetMaxFPS(){return (mFPS);}
			bool				IsFullscreen(){return (mFullscreen);}
			bool				IsVSync(){return (mVSync);}

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


