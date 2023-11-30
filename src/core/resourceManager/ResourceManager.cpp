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
			if (mTextures.count(tPath))
				return (mTextures[tPath]);
			ptr = std::make_shared<sf::Texture>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return ((mTextures[tPath] = ptr));
		}

		std::shared_ptr<sf::Image>			ResourceManager::LoadImage(std::string tPath)
		{
			std::shared_ptr<sf::Image>	ptr;
			if (mImages.count(tPath))
				return (mImages[tPath]);
			ptr = std::make_shared<sf::Image>();
			if (!ptr->loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			return ((mImages[tPath] = ptr));
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

		std::shared_ptr<sf::Shader>			ResourceManager::LoadShader(std::string tPath)
		{
			std::shared_ptr<sf::Shader>	ptr;
			if (mShaders.count(tPath))
				return (mShaders[tPath]);
			ptr = std::make_shared<sf::Shader>();
			if (!ptr->loadFromFile(tPath, sf::Shader::Fragment))
				throw std::runtime_error("Failed to load " + tPath);
			return ((mShaders[tPath] = ptr));
		}


		sf::Sound							ResourceManager::LoadSound(std::string tPath)
		{
			sf::SoundBuffer	buffer;
			if (mSounds.count(tPath))
			{
				return (sf::Sound(mSounds[tPath]));
			}
			if (!buffer.loadFromFile(tPath))
				throw std::runtime_error("Failed to load " + tPath);
			mSounds[tPath] = buffer;
			return (sf::Sound(mSounds[tPath]));
		}


	} // namespace Core
	
} // namespace Yuna
