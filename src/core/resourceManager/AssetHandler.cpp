#include "AssetHandler.hpp"

namespace Yuna
{
	namespace Core
	{
		
		template<typename AssetT> AssetHandler<AssetT>::AssetHandler(/* args */)
		{

		}
		
		template<typename AssetT> AssetHandler<AssetT>::~AssetHandler()
		{

		}

		template<typename AssetT> std::shared_ptr<AssetT>	AssetHandler<AssetT>::Load(std::string tPath, std::shared_ptr<AssetT> tAsset)
		{
			if (mAssets.find(tPath) == mAssets.end())
				mAssets[tPath] = tAsset;
			return (mAssets[tPath]);
		}

	} // namespace Core	
} // namespace Yuna
