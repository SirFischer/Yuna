/*
 * File: PathFinding.cpp
 * Project: Extermination
 * File Created: Sunday, 29th May 2022 9:13:22 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 4th June 2022 8:00:15 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "PathFinding.hpp"

#include "Math.hpp"

#include <iostream>

namespace Yuna
{
	namespace AI
	{

		std::vector<PathNode>		getPath(PathNode *pStart, PathNode *pEnd)
		{
			std::vector<PathNode>	targets;
			PathNode				*current = pEnd;
			targets.push_back(*pEnd);

			while (current != pStart)
			{
				PathNode newPath = PathNode();
				newPath.mPosition = current->mPosition;
				newPath.mIsBreakable = current->mIsBreakable;
				newPath.mParentObject = current->mParentObject;
				
				targets.push_back(newPath);
				PathNode *next = current->mParent;
				current->mParent = nullptr;
				current = next;
			}
			return (targets);
		}

		std::vector<PathNode>		createPath(PathNode *pStart, PathNode *pEnd)
		{
			std::list<PathNode *>	open; 
			std::list<PathNode *>	closed;

			pStart->mG = 0.f;
			pStart->mH = Math::Distance(pStart->mPosition, pEnd->mPosition);
			pStart->mF = pStart->mG + pStart->mH;
			pStart->mParent = nullptr;

			open.push_back(pStart);

			while (open.size())
			{
				PathNode *current = open.front();

				for (auto &i : open)
				{
					if (i->mF < current->mF || (i->mF == current->mF && i->mH < current->mH))
						current = i;
				}

				open.remove(current);

				closed.push_back(current);

				if (current == pEnd)
				{
					//return list
					return (getPath(pStart, pEnd));
				}

				for (auto &subsequent : current->mConnectedPaths)
				{
					float g = current->mG + subsequent.cost;
					float h = Math::Distance(subsequent.mTarget->mPosition, pEnd->mPosition);

					if (std::find(closed.begin(), closed.end(), subsequent.mTarget.get()) != closed.end())
						continue;
					if (std::find(open.begin(), open.end(), subsequent.mTarget.get()) == open.end() || subsequent.mTarget->mG > g)
					{
						subsequent.mTarget->mG = g;
						subsequent.mTarget->mH = h;
						subsequent.mTarget->mF = g + h;
						subsequent.mTarget->mParent = current;

						if (std::find(open.begin(), open.end(), subsequent.mTarget.get()) == open.end())
							open.push_back(subsequent.mTarget.get());

					}
				}
			}
			return (std::vector<PathNode>());
		}
	} // namespace AI
	
} // namespace Yuna
