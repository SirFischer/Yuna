/*
 * File: PathFinding.hpp
 * Project: Extermination
 * File Created: Sunday, 29th May 2022 12:16:47 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 2nd June 2022 6:42:37 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <stack>
#include <memory>

namespace Yuna
{
	namespace AI
	{
		struct PathNode;

		struct Path
		{
			std::shared_ptr<PathNode>	mTarget;
			float cost = 0.f;
		};

		struct PathNode
		{
			bool				mIsBreakable = false;
			//distance from start node
			float				mG = 0.f;
			//distance from end node
			float				mH = 0.f;
			//sum of mG and mH
			float				mF = 0.f;
			sf::Vector2f		mPosition;
			std::list<Path>		mConnectedPaths = std::list<Path>();
			PathNode			*mParent = nullptr;
		};

		std::vector<PathNode>	createPath(PathNode *pStart, PathNode *pEnd);

	} // namespace AI
	
} // namespace name
