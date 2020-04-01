#include <iostream>
#include <SFML/Graphics.hpp>
#include "OpenWindow.h"
#include "optionsScreen.h"
#include "LoadScreen.h"
#include "CreditsScreen.h"
#include "Level_System.h"

#ifndef SCREENS_HPP_INCLUDED
#define SCREENS_HPP_INCLUDED
#include "cScreen.h"
#include "Level_System.h"
#include "OpenWindow.h"
#include "optionsScreen.h"
#include "LoadScreen.h"
#include "CreditsScreen.h"
#endif




int main()
{
	using namespace std;

	sf::RenderWindow app(sf::VideoMode(1920, 1080), "Panda's Puzzles", sf::Style::Fullscreen);
	std::vector<cScreen*> Screens;
	int screen = 0;

	//this manages each main screen in the game
	//Play, load, options, and exit
	OpenWindow mainMenu;
	Screens.push_back(&mainMenu);
	Level_System playScreen;
	Screens.push_back(&playScreen);
	optionsScreen options;
	Screens.push_back(&options);
	LoadScreen load;
	Screens.push_back(&load);
	CreditsScreen credits;
	Screens.push_back(&credits);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(app);
	}
	return EXIT_SUCCESS;

}

