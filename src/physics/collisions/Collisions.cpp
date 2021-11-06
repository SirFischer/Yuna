/*
 * File: Collisions.cpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:58:27 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 12:51:58 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Collisions.hpp"
namespace Yuna
{
	namespace Physics
	{
		bool	AABBCollision(const sf::FloatRect &pRect1, const sf::FloatRect &pRect2)
		{
			return (pRect1.left < pRect2.left + pRect2.width &&
					pRect1.left + pRect1.width > pRect2.left &&
					pRect1.top < pRect2.top + pRect2.height &&
					pRect1.top + pRect1.height > pRect2.top);
		}

		bool	LineLineCollision(const sf::Vector2f &pLine1Start, const sf::Vector2f &pLine1End, const sf::Vector2f &pLine2Start, const sf::Vector2f &pLine2End)
		{
			float uA = ((pLine2End.x - pLine2Start.x) * (pLine1Start.y - pLine2Start.y) - (pLine2End.y - pLine2Start.y) * (pLine1Start.x - pLine2Start.x)) /
				((pLine2End.y - pLine2Start.y) * (pLine1End.x - pLine1Start.x) - (pLine2End.x - pLine2Start.x) * (pLine1End.y - pLine1Start.y));
			float uB = ((pLine1End.x - pLine1Start.x) * (pLine1Start.y - pLine2Start.y) - (pLine1End.y - pLine1Start.y) * (pLine1Start.x - pLine2Start.x)) /
				((pLine2End.y - pLine2Start.y) * (pLine1End.x - pLine1Start.x) - (pLine2End.x - pLine2Start.x) * (pLine1End.y - pLine1Start.y));
			if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
				return true;
			return (false);
		}

		bool	LineRectCollision(const sf::Vector2f &pLineStart, const sf::Vector2f &pLineEnd, const sf::FloatRect &pRect)
		{
			bool	left = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top), sf::Vector2f(pRect.left, pRect.top + pRect.height));
			bool	right = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left + pRect.width, pRect.top), sf::Vector2f(pRect.left + pRect.width, pRect.top + pRect.height));
			bool	top = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top), sf::Vector2f(pRect.left + pRect.width, pRect.top));
			bool	bottom = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top + pRect.height), sf::Vector2f(pRect.left + pRect.width, pRect.top + pRect.height));

			return (left || right || top || bottom);
		}

		bool	RayRectCollision(const sf::Vector2f &pRayStart, const sf::Vector2f &pRayDir, const sf::FloatRect &pRect, sf::Vector2f &pContactPoint, sf::Vector2f &pContactNormal, float &pNearTime)
		{
			sf::Vector2f	near = sf::Vector2f((pRect.left - pRayStart.x) / pRayDir.x, (pRect.top - pRayStart.y) / pRayDir.y);
			sf::Vector2f	far = sf::Vector2f((pRect.left + pRect.width - pRayStart.x) / pRayDir.x, (pRect.top + pRect.height - pRayStart.y) / pRayDir.y);

			if (std::isnan(far.y) || std::isnan(far.x))
				return (false);
			if (std::isnan(near.y) || std::isnan(near.x))
				return (false);

			if (near.x > far.x)
				std::swap(near.x, far.x);
			if (near.y > far.y)
				std::swap(near.y, far.y);

			if (near.x > far.y || near.y > far.x)
				return (false);

			pNearTime = std::max(near.x, near.y);
			float pFarTime = std::min(far.x, far.y);

			if (pFarTime < 0)
				return (false);

			pContactPoint = sf::Vector2f(pRayStart.x + (pNearTime * pRayDir.x), pRayStart.y + (pNearTime * pRayDir.y));
			if (near.x > near.y)
			{
				if ((1.f / pRayDir.x) < 0)
					pContactNormal = sf::Vector2f(1.f, 0.f);
				else
					pContactNormal = sf::Vector2f(-1.f, 0.f);
			}
			else if (near.x < near.y)
			{
				if ((1.f / pRayDir.y) < 0)
					pContactNormal = sf::Vector2f(0.f, 1.f);
				else
					pContactNormal = sf::Vector2f(0.f, -1.f);
			}
			return (true);
		}

		bool	DynamicRectCollision(const sf::FloatRect &pRect1, const sf::Vector2f &pVelocity, const sf::FloatRect &pRect2, sf::Vector2f &pContactPoint, sf::Vector2f &pContactNormal, float &pNearTime)
		{
			if (pVelocity.x == 0.f && pVelocity.y == 0.f)
				return (false);
			sf::FloatRect expanded;
			expanded.left = pRect2.left - (pRect1.width / 2.f);
			expanded.top = pRect2.top - (pRect1.height / 2.f);
			expanded.width = pRect2.width + pRect1.width;
			expanded.height = pRect2.height + pRect1.height;

			if (RayRectCollision(sf::Vector2f(pRect1.left + pRect1.width / 2.f, pRect1.top + pRect1.height / 2.f), pVelocity, expanded, pContactPoint, pContactNormal, pNearTime))
				return (pNearTime >= 0.f && pNearTime < 1.f);
			return (false);
		}
	} // namespace Physics
} // namespace Yuna