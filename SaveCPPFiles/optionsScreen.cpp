#include "optionsScreen.h"


optionsScreen::optionsScreen()
{
}


optionsScreen::~optionsScreen()
{
}

int optionsScreen::Run(sf::RenderWindow &App)
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

	//load the font assets and set strings and character sizes 
	sf::Font menuFont;
	menuFont.loadFromFile("capAssets/Fonts/_bitmap_font____romulus_by_pix3m-d6aokem.ttf");

	volText.setFont(menuFont);
	volText.setCharacterSize(48);
	volText.setString("Volume");
	volText.setPosition({ 720.f, 200.f });
	volText.setFillColor(sf::Color::Black);

	greyScale.setFont(menuFont);
	greyScale.setCharacterSize(48);
	greyScale.setString("Grey Scale");
	greyScale.setFillColor(sf::Color::Black);
	greyScale.setPosition({ 720.f, 500.f });

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

			if (event.type == sf::Event::MouseMoved)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				//play
				if (event.mouseButton.button == sf::Mouse::Left && back.getGlobalBounds().contains(mousePosF))
				{
					return (0);
				}
			}

			if (event.type == sf::Event::Closed) {
				return (-1);
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return (0);
				}
			}

			//to do, add interactive buttons and sliders for options
			App.clear();
			App.draw(spriteBackground);
			App.draw(volText);
			App.draw(greyScale);
			App.draw(back);
			App.display();
		}


	}

	return -1;
}
