/*
 * File: Collisions.hpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:57:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 30th October 2021 9:57:54 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>

bool	AABBCollision(const sf::FloatRect &pRect1, const sf::FloatRect &pRect2);