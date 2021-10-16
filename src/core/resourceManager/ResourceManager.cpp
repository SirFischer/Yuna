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
			if ((ptr = mTextures.Load(tPath, std::shared_ptr<sf::Texture>(nullptr))))
				return (ptr);
			//Loads texture
			ptr = std::make_shared<sf::Texture>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return (mTextures.Load(tPath, ptr));
		}

		std::shared_ptr<sf::Font>			ResourceManager::LoadFont(std::string tPath)
		{
			std::shared_ptr<sf::Font>	ptr;
			if ((ptr = mFonts.Load(tPath, std::shared_ptr<sf::Font>(nullptr))))
				return (ptr);
			ptr = std::make_shared<sf::Font>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return (mFonts.Load(tPath, ptr));
		}


	} // namespace Core
	
} // namespace Yuna
