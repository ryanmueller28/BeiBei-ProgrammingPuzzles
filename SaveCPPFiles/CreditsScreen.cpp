#include "CreditsScreen.h"


CreditsScreen::CreditsScreen()
{
}


CreditsScreen::~CreditsScreen()
{
}

int CreditsScreen::Run(sf::RenderWindow &App)
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

	credits_1.setFont(menuFont);
	credits_1.setCharacterSize(96);
	credits_1.setString("Credits");
	credits_1.setPosition({ 740.f, 25.f });
	credits_1.setFillColor(sf::Color::Black);

	credits_2.setFont(menuFont);
	credits_2.setCharacterSize(48);
	credits_2.setPosition({ 50.f, 150.f });
	credits_2.setFillColor(sf::Color::Black);
	credits_2.setString("Project Advisors: Dr. Mark Meysenburg and Dr. Alec Engebretson");

	credits_3.setFont(menuFont);
	credits_3.setCharacterSize(48);
	credits_3.setPosition({ 50.f, 220.f });
	credits_3.setFillColor(sf::Color::Black);
	credits_3.setString("Education Field Advisors: Dr. Linda Kalbach");

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

				//play
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
			App.draw(credits_1);
			App.draw(credits_2);
			App.draw(credits_3);
			App.draw(back);
			App.display();

		}
	}
}
