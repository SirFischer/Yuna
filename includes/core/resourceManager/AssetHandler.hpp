#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace Yuna
{
	namespace Core
	{
		template <typename AssetT>
		class AssetHandler
		{
		private:
			AssetHandler(/* args */);
			~AssetHandler();

			std::unordered_map<std::string, std::shared_ptr<AssetT>>		mAssets;
		public:
			//Allow the ResourceManager to instatiate assethandlers
			friend class ResourceManager;

			std::shared_ptr<AssetT>		Load(std::string tPath, std::shared_ptr<AssetT> tAsset);

		};
		
	} // namespace Core
} // namespace Yuna
