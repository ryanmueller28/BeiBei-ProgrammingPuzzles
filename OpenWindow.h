#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "cScreen.h"
#include "optionsScreen.h"

class OpenWindow : public cScreen
{
public:
	int alpha_max;
	int alpha_div;
	bool playing;

	sf::RenderWindow mainWindow;
	OpenWindow();

private:
	//functions to animate the text options getting larger or smaller
	void animDown();
	void animUp();
	unsigned int menu = 0;
	virtual int Run(sf::RenderWindow &App);
	
	sf::Text playText;
	sf::Text titleText;
	sf::Text optionsText;
	sf::Text loadLevel;
	sf::Text creditsText;
	sf::Text exitText;

	sf::Vector2i mousePos = sf::Mouse::getPosition();
};



OpenWindow::OpenWindow()
{

}



int OpenWindow::Run(sf::RenderWindow &App) {

	bool Running = true;


	//Load the background image and display
	sf::Texture textureBackground;
	textureBackground.loadFromFile("capAssets/UI/Full_Background_Pixel.png");

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Load the title menu text. Each size needs a different asset instance
	sf::Font menuFont;
	menuFont.loadFromFile("capAssets/Fonts/_bitmap_font____romulus_by_pix3m-d6aokem.ttf");


	//Title text definitions
	titleText.setFont(menuFont);
	titleText.setString("Bei Bei's Programming Puzzles");
	titleText.setCharacterSize(96);
	titleText.setFillColor(sf::Color::Magenta);
	titleText.setPosition(375, 75);
	titleText.setStyle(sf::Text::Bold);

	//Menu text definitions

	//Play
	playText.setFont(menuFont);
	playText.setCharacterSize(72);
	playText.setFillColor(sf::Color::Blue);
	playText.setString("Play");
	playText.setPosition({ 280.f, 500.f });

	//create bounds for mouse funcitonality
	float playWidth = playText.getLocalBounds().width;
	float playHeight = playText.getLocalBounds().height;

	//options
	optionsText.setFont(menuFont);
	optionsText.setCharacterSize(36);
	optionsText.setFillColor(sf::Color::Blue);
	optionsText.setString("Options");
	optionsText.setPosition({ 280.f, 600.f });

	//create bounds for mouse funcitonality
	float optionsWidth = optionsText.getLocalBounds().width;
	float optionsHeight = optionsText.getLocalBounds().height;

	//Load
	loadLevel.setFont(menuFont);
	loadLevel.setCharacterSize(36);
	loadLevel.setFillColor(sf::Color::Blue);
	loadLevel.setString("Load");
	loadLevel.setPosition({ 280.f, 640.f });

	//create bounds for mouse funcitonality
	float loadWidth = loadLevel.getLocalBounds().width;
	float loadHeight = loadLevel.getLocalBounds().height;

	//credits
	creditsText.setFont(menuFont);
	creditsText.setCharacterSize(36);
	creditsText.setFillColor(sf::Color::Blue);
	creditsText.setString("Credits");
	creditsText.setPosition({ 280.f, 680.f });

	//create bounds for mouse funcitonality
	float creditsWidth = creditsText.getLocalBounds().width;
	float creditsHeight = creditsText.getLocalBounds().height;

	//exit
	exitText.setFont(menuFont);
	exitText.setCharacterSize(36);
	exitText.setFillColor(sf::Color::Blue);
	exitText.setString("Exit");
	exitText.setPosition({ 280.f, 720.f });

	//create bounds for mouse funcitonality
	float exitWidth = exitText.getLocalBounds().width;
	float exitHeight = exitText.getLocalBounds().height;

	//load the Panda sprite
	sf::Texture beiBeiText;
	beiBeiText.loadFromFile("capAssets/Panda/BeiBei.png");

	sf::Sprite BeiBei;
	BeiBei.setTexture(beiBeiText);

	BeiBei.setPosition(1200, 1080);

	while (Running) {

		//create a clock and a deltaTime
		sf::Time deltaT;
		sf::Time elapsedT;
		sf::Clock clock;
		
		sf::Vector2f BeiBeiPos = BeiBei.getPosition();

		elapsedT += clock.getElapsedTime();
		deltaT = clock.getElapsedTime();
		
		//check for all possible events
		sf::Event event;
		while (App.pollEvent(event)){
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}

			if (elapsedT.asMicroseconds() < 6) {

				
				BeiBei.setPosition(BeiBeiPos.x, BeiBeiPos.y - 10);

				if (BeiBeiPos.y < 550) {
					BeiBei.setPosition(BeiBeiPos.x, BeiBeiPos.y);
				}
			
	
			
				clock.restart();
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					animDown();
					break;
				case sf::Keyboard::S:
					animUp();
						break;

						case sf::Keyboard::Up:
							menu = menu - 1;
							animDown();
							break;
						case sf::Keyboard::Down:
							animUp();
							break;

					case sf::Keyboard::Return:
						if (menu == 0) {
							playing = true;
							return(1);
						}
						
						if (menu == 1) {
							playing = true;
							return(2);
						}
						if (menu == 2) {
							playing = true;
							return(3);
						}

						if (menu == 3)
						{
							playing = true;
							return(4);
						}

						else {
							return(-1);
						}
						break;
					default:
						break;
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			}
			/*
			* Below: read mouse functionality
			* for main menu. Return to new
			* cScreen Vector based on rect selected
			*/
			if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				//play
				if (event.mouseButton.button == sf::Mouse::Left && playText.getGlobalBounds().contains(mousePosF))
				{
					return (1);
				}

				//options
				if (event.mouseButton.button == sf::Mouse::Left && optionsText.getGlobalBounds().contains(mousePosF))
				{
					return (2);
				}

				//load
				if (event.mouseButton.button == sf::Mouse::Left && loadLevel.getGlobalBounds().contains(mousePosF))
				{
					return (3);
				}

				//credits
				if (event.mouseButton.button == sf::Mouse::Left && creditsText.getGlobalBounds().contains(mousePosF))
				{
					return (4);
				}

				//exit
				if (event.mouseButton.button == sf::Mouse::Left && exitText.getGlobalBounds().contains(mousePosF))
				{
					return (-1);
				}
			}

			App.clear();
			App.draw(spriteBackground);
			App.draw(titleText);
			App.draw(playText);
			App.draw(loadLevel);
			App.draw(optionsText);
			App.draw(creditsText);
			App.draw(exitText);
			App.draw(BeiBei);
			App.display();
		

		}
	}
	return -1;
}

void OpenWindow::animDown()
{
	menu = menu - 1;
	switch (menu) {
	case 0:
		//make the text bigger when something is selected

		//case 0 = play
		playText.setCharacterSize(96);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 1:
		//case 1 = load level
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(52);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 2:
		//case 3 = options
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(52);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 3:
		//case 3 = credits
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(52);
		exitText.setCharacterSize(36);
		break;
	case 4:
		//case 4 = exit
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(52);
		break;
	}

}

void OpenWindow::animUp()
{
	menu = menu + 1;
	switch (menu) {
	case 0:
		//make the text bigger when something is selected

		//case 0 = play
		playText.setCharacterSize(96);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 1:
		//case 1 = load level
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(52);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 2:
		//case 3 = options
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(52);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(36);
		break;
	case 3:
		//case 3 = credits
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(52);
		exitText.setCharacterSize(36);
		break;
	case 4:
		//case 4 = exit
		playText.setCharacterSize(72);
		loadLevel.setCharacterSize(36);
		optionsText.setCharacterSize(36);
		creditsText.setCharacterSize(36);
		exitText.setCharacterSize(52);
		break;
	}
}