#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"
#include "User.hpp"

using namespace std;
using namespace sf;

int login();
int player(string);
int home(string);

int registerUser()
{
	User user;
	RenderWindow window(VideoMode(700, 600), "Register Form");

	Font font;
	if (!font.loadFromFile("Coding/static/Poppins-Medium.ttf"))
	{
		error("Error Loading Font File.");
		return 1;
	}
	Texture background, listenerTexture, background2;
	if (!background.loadFromFile("Coding/static/register.png") || !listenerTexture.loadFromFile("Coding/static/Listener.png") || !background2.loadFromFile("Coding/static/register-2.png"))
	{
		error("Error Loading Image File.");
		return 1;
	}

	Sprite s(background);
	Sprite s2(background2);
	Sprite listenerSprite(listenerTexture);

	Image icon;
	if (!icon.loadFromFile("Coding/static/icon.png"))
	{
		error("Error Loading Icon File.");
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Color color(0x071952FF);
	Color color2(0xFD3A69FF);

	Text text("Register", font, 30);
	text.setStyle(Text::Bold);
	text.setPosition(window.getSize().x / 2 - text.getCharacterSize() / 2 - 50, 140);
	text.setFillColor(color);

	Text text2("Who are you?", font, 20);
	text2.setStyle(Text::Bold);
	text2.setPosition(window.getSize().x / 2 - text2.getCharacterSize() / 2 - 50, 440);
	text2.setFillColor(color);

	Text text3("Already Have an Account?", font, 20);
	text3.setPosition(window.getSize().x / 2 - text3.getCharacterSize() / 2 - 150, 565);
	text3.setFillColor(color);

	Text text4("Login", font, 20);
	text4.setStyle(Text::Bold);
	text4.setPosition(text3.getPosition().x + 280, text3.getPosition().y);
	text4.setFillColor(color2);

	listenerSprite.setPosition(window.getSize().x / 2 - listenerSprite.getGlobalBounds().width / 2 + 10, 480);

	Text usernameText("Username:", font, 20);
	usernameText.setPosition(175, 280);
	usernameText.setFillColor(color);

	Text passwordText("Password:", font, 20);
	passwordText.setPosition(175, 370);
	passwordText.setFillColor(color);

	RectangleShape inputBox1(Vector2f(250, 50));
	inputBox1.setPosition(300, 270);
	inputBox1.setOutlineThickness(2);
	inputBox1.setOutlineColor(color);
	inputBox1.setFillColor(Color::White);

	RectangleShape inputBox2(Vector2f(250, 50));
	inputBox2.setPosition(300, 358);
	inputBox2.setOutlineColor(color);
	inputBox2.setOutlineThickness(2);
	inputBox2.setFillColor(Color::White);

	Text usernameInput("", font, 20);
	usernameInput.setPosition(310, 280);
	usernameInput.setFillColor(color);

	Text passwordInput("", font, 20);
	passwordInput.setPosition(310, 373);
	passwordInput.setFillColor(color);

	Texture submitTexture;
	if (!submitTexture.loadFromFile("Coding/static/Submit.png"))
	{
		error("Error Loading Submit Button.");
		return 1;
	}

	Sprite submitButton(submitTexture);
	submitButton.setPosition(300, 450);
	string username = "";
	string password = "";
	bool typingUsername = true;
	bool userChoice = false;
	string userType = "Listener";

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (inputBox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					typingUsername = true;
					inputBox1.setOutlineThickness(5);
					inputBox2.setOutlineThickness(2);
				}
				else if (inputBox2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					typingUsername = false;
					inputBox1.setOutlineThickness(2);
					inputBox2.setOutlineThickness(5);
				}
				if (text4.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					window.close();
					login();
					return 1;
				}
				if (listenerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					userChoice = true;
					userType = "Listener";
				}
			}

			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == '\b')
				{
					if (typingUsername)
					{
						if (!username.empty())
							username.pop_back();
					}
					else
					{
						if (!password.empty())
							password.pop_back();
					}
				}
				else if (event.text.unicode == '\r')
				{
					typingUsername = !typingUsername;
				}
				else if (event.text.unicode < 128)
				{
					if (typingUsername)
					{
						inputBox1.setOutlineThickness(5);
						inputBox2.setOutlineThickness(2);
						username += static_cast<char>(event.text.unicode);
					}
					else
					{
						inputBox2.setOutlineThickness(5);
						inputBox1.setOutlineThickness(2);
						password += static_cast<char>(event.text.unicode);
					}
				}
				else if (event.text.unicode >= 128)
				{
					showPopup(window, "Invalid character input.");
					return 1;
				}
			}

			if (event.type == Event::MouseButtonPressed && password != "" && username != "")
			{
				if (submitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					if (user.UserRegister(window, username, password, userType))
					{
						string message = "Welcome to Melody Tunes, " + username;
						showPopup(window, message, Vector2f(500, 60), "Success");
						window.close();
						if (userType == "Listener")
							return home(username);
						else
							showPopup(window, "You are a Musician. Please login to continue.", Vector2f(500, 60), "Success");
					}
					else
					{
						window.close();
						registerUser();
					}
				}
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && password != "" && username != "")
			{
				if (user.UserRegister(window, username, password, userType))
				{
					string message = "Welcome to Melody Tunes, " + username;
					showPopup(window, message, Vector2f(500, 60), "Success");
					window.close();
					return home(username);
				}
				else
				{
					window.close();
					registerUser();
				}
			}
		}
		usernameInput.setString(username);
		passwordInput.setString(string(password.length(), '*'));

		window.clear(Color::White);

		if (!userChoice)
		{
			window.draw(s);
			window.draw(text);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(listenerSprite);
			window.display();
		}
		else
		{
			window.draw(s2);
			window.draw(text);
			window.draw(text3);
			window.draw(text4);
			window.draw(inputBox1);
			window.draw(inputBox2);
			window.draw(usernameText);
			window.draw(passwordText);
			window.draw(usernameInput);
			window.draw(passwordInput);
			window.draw(submitButton);
			window.display();
		}
	}
	return 0;
}
