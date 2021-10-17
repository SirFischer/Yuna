#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace Yuna
{
	namespace Core
	{
		class ResourceManager
		{
		private:
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>>	mTextures;
			std::unordered_map<std::string, std::shared_ptr<sf::Font>>		mFonts;

		public:
			ResourceManager(/* args */);
			~ResourceManager();

			std::shared_ptr<sf::Texture>		LoadTexture(std::string tPath);
			std::shared_ptr<sf::Font>			LoadFont(std::string tPath);
		};
	} // namespace Core
	
} // namespace Yuna


