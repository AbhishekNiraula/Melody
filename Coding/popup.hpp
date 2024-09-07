#ifndef POPUP_HPP
#define POPUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "error.hpp"

using namespace std;
using namespace sf;

void showPopup(RenderWindow &window, string message, Vector2f popupSize = Vector2f(400, 60), string color = "Default")
{

	Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	Sprite background(texture);

	RectangleShape popupBox(popupSize);
	popupBox.setPosition(window.getSize().x / 2 - popupSize.x / 2, -popupSize.y);

	if (color == "Success")
	{
		Color successColor(0x66CDAAFF);
		popupBox.setFillColor(successColor);
	}
	else if (color == "Warning")
	{
		Color warningColor(0xFFD700FF);
		popupBox.setFillColor(warningColor);
	}
	else if (color == "Error")
	{
		Color errorColor(0xDC3545FF);
		popupBox.setFillColor(errorColor);
	}
	else
	{
		Color defaultColor(0x7CB9E8FF);
		popupBox.setFillColor(defaultColor);
	}

	Font font;

	if (!font.loadFromFile("Coding/static/Poppins-Medium.ttf"))
	{
		cout << "Error Loading Font File." << endl;
		return;
	}

	Text popupText(message, font, 20);
	popupText.setFillColor(Color::White);
	popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 15);

	float targetY = 50;
	float speed = 500.f;

	Clock clock;
	while (popupBox.getPosition().y < targetY)
	{
		float deltaTime = clock.restart().asSeconds();
		popupBox.move(0, speed * deltaTime);
		popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 15);

		window.clear();
		window.draw(background);

		window.draw(popupBox);
		window.draw(popupText);
		window.display();
	}

	sleep(seconds(1));

	while (popupBox.getPosition().y > -popupSize.y)
	{
		float deltaTime = clock.restart().asSeconds();
		popupBox.move(0, -speed * deltaTime);
		popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 15);

		window.clear();
		window.draw(background);

		window.draw(popupBox);
		window.draw(popupText);
		window.display();
	}
}

#endif
