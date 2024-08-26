#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"

using namespace std;
using namespace sf;


int player(string);
int registerUser();

int login()
{
    RenderWindow window(sf::VideoMode(700, 600), "Login Form");

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }
    Texture background;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/login.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Sprite s(background);

    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Color color(0x071952FF);
    Color color2(0xFD3A69FF);

    Text text("Login", font, 30);
    text.setStyle(Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getCharacterSize() / 2 - 30, 140);
    text.setFillColor(color);

    Text text3("Already Have an Account?", font, 20);
    text3.setPosition(window.getSize().x / 2 - text3.getCharacterSize() / 2 - 130, 520);
    text3.setFillColor(color);

    
    Text text4("Register", font, 20);
    text4.setStyle(Text::Bold);
    text4.setPosition(text3.getPosition().x + 280, text3.getPosition().y);
    text4.setFillColor(color2);

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
    if (!submitTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Submit.png"))
    {
        error("Error Loading Submit Button.");
        return 1;
    }

    Sprite submitButton(submitTexture);
    submitButton.setPosition(300, 450);
    string username = "";
    string password = "";
    bool typingUsername = true;

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
                    return registerUser();
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
                    string message = "Welcome Back, " + username;
                    showPopup(window, message);
                    player(username);
                    window.close();
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && password != "" && username != "")
            {
                string message = "Welcome Back, " + username;
                window.close();
                showPopup(window, message, Vector2f(400, 60), "Success");
                player(username);
            }
        }



        usernameInput.setString(username);
        passwordInput.setString(string(password.length(), '*'));

        window.clear(Color::White);

        window.draw(s);
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
    return 0;
}
