#include "ResourceManager.hpp"

namespace Yuna
{
	namespace Core
	{
		ResourceManager::ResourceManager(/* args */)
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		std::shared_ptr<sf::Texture>		ResourceManager::LoadTexture(std::string tPath)
		{
			std::shared_ptr<sf::Texture>	ptr;
			//checks if already exists
			if (mTextures.count(tPath))
				return (mTextures[tPath]);
			//Loads texture
			ptr = std::make_shared<sf::Texture>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return ((mTextures[tPath] = ptr));
		}

		std::shared_ptr<sf::Font>			ResourceManager::LoadFont(std::string tPath)
		{
			std::shared_ptr<sf::Font>	ptr;
			if (mFonts.count(tPath))
				return (mFonts[tPath]);
			ptr = std::make_shared<sf::Font>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return ((mFonts[tPath] = ptr));
		}


	} // namespace Core
	
} // namespace Yuna
