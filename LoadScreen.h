#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "cScreen.h"

class LoadScreen : public cScreen
{
public:
	LoadScreen();
	~LoadScreen();

	virtual int Run(sf::RenderWindow &App);

private:
	sf::Text level_1;
	sf::Text back; //back to previous screen

	sf::Vector2i mousePos = sf::Mouse::getPosition();
};

LoadScreen::LoadScreen()
{
}


LoadScreen::~LoadScreen()
{
}

int LoadScreen::Run(sf::RenderWindow &App)
{
	bool Running = true;
	bool backPressed = false;
	sf::Event event;
	//Load the background image and display
	sf::Texture textureBackground;
	textureBackground.loadFromFile("capAssets/UI/Full_Background_Pixel.png");

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	sf::Font menuFont;
	menuFont.loadFromFile("capAssets/Fonts/_bitmap_font____romulus_by_pix3m-d6aokem.ttf");

	level_1.setFont(menuFont);
	level_1.setCharacterSize(96);
	level_1.setString("Level: ");
	level_1.setPosition({ 720.f, 200.f });
	level_1.setFillColor(sf::Color::Black);

	back.setFont(menuFont);
	back.setCharacterSize(48);
	back.setString("Back");
	back.setFillColor(sf::Color::Black);
	back.setPosition({ 200.f, 700 });

	//create bounds for mouse funcitonality
	float backWidth = back.getLocalBounds().width;
	float backHeight = back.getLocalBounds().height;

	while (Running)
	{
		while (App.pollEvent(event)) {


			if (event.type == sf::Event::Closed) {
				return -1;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				//back
				if (event.mouseButton.button == sf::Mouse::Left && back.getGlobalBounds().contains(mousePosF))
				{
					return (0);
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return (0);
				}
			}
			App.clear();
			App.draw(spriteBackground);
			App.draw(level_1);
			App.draw(back);
			App.display();

		}
	}
}
