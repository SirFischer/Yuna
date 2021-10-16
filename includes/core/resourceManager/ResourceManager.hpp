#pragma once

#include "AssetHandler.hpp"
#include <SFML/Graphics.hpp>

namespace Yuna
{
	namespace Core
	{
		class ResourceManager
		{
		private:
			AssetHandler<sf::Texture>	mTextures;
			AssetHandler<sf::Font>		mFonts;

		public:
			ResourceManager(/* args */);
			~ResourceManager();

			std::shared_ptr<sf::Texture>		LoadTexture(std::string tPath);
			std::shared_ptr<sf::Font>			LoadFont(std::string tPath);
		};
	} // namespace Core
	
} // namespace Yuna


