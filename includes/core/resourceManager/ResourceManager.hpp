#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Yuna
{
	namespace Core
	{
		class ResourceManager
		{
		private:
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>>		mTextures;
			std::unordered_map<std::string, std::shared_ptr<sf::Image>>			mImages;
			std::unordered_map<std::string, std::shared_ptr<sf::Font>>			mFonts;
			std::unordered_map<std::string, std::shared_ptr<sf::Shader>>		mShaders;
			std::unordered_map<std::string, sf::SoundBuffer>					mSounds;

		public:
			ResourceManager(/* args */);
			~ResourceManager();

			std::shared_ptr<sf::Texture>		LoadTexture(std::string tPath);
			std::shared_ptr<sf::Image>			LoadImage(std::string tPath);
			std::shared_ptr<sf::Font>			LoadFont(std::string tPath);
			std::shared_ptr<sf::Shader>			LoadShader(std::string tPath);
			sf::Sound							LoadSound(std::string tPath);
		};
	} // namespace Core
	
} // namespace Yuna


