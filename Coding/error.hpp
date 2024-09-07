#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstring>
#include "popup.hpp"

int login();

using namespace std;
using namespace sf;

void error(string message)
{
	RenderWindow window(VideoMode(700, 600), "Error Encountered");
	Image icon;
	if (!icon.loadFromFile("Coding/static/icon.png"))
	{
		showPopup(window, "Error Loading Icon File.", Vector2f(400, 60), "Error");
		cout << "Error Loading Icon File." << endl
			 << "Proceeding Without Loading." << endl;
	}
	else
	{
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	Texture background;
	if (!background.loadFromFile("Coding/static/Melody-Error.png"))
	{
		showPopup(window, "Error Loading Image File", Vector2f(400, 60), "Error");
		cout << "Error Loading Error Image File." << endl
			 << "Proceeding Without Loading." << endl;
	}

	Font font;
	if (!font.loadFromFile("Coding/static/Poppins-Medium.ttf"))
	{
		showPopup(window, "Error Loading Font File.", Vector2f(400, 60), "Error");
		cout << "Error Loading Font File." << endl;
	}

	Sprite s(background);

	Texture backTexture;
	if (!backTexture.loadFromFile("Coding/static/exit.png"))
	{
		showPopup(window, "Error Loading Icons.", Vector2f(400, 60), "Error");
		cout << "Error Loading Icons." << endl;
		return;
	}

	Sprite backSprite(backTexture);
	backSprite.setPosition(window.getSize().x / 2 - backSprite.getGlobalBounds().width / 2, 500);

	string t_message = message + "\nPlease try restarting the program.";

	Text text(t_message, font, 20);
	Color color(0x071952FF);
	text.setFillColor(color);
	text.setPosition(225, 400);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if ((event.type == Event::MouseButtonPressed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				if (backSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					window.close();
					return;
				}
			}
		}

		window.clear(Color::White);
		window.draw(s);
		window.draw(text);
		window.draw(backSprite);
		window.display();
	}
}

#endif // ERROR_HPP