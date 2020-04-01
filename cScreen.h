#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class cScreen
{
public:
	virtual int Run(sf::RenderWindow &App) = 0;
};
