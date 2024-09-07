#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <limits> // for std::numeric_limits
#include <cctype> // for std::isalnum
#include <cstdlib>

class User
{
protected:
	std::string username, password, role;

public:
	User(const std::string &usrnm = "", const std::string &pass = "", const std::string &role = "")
		: username(usrnm), password(pass), role(role) {}

	// Check if the username is valid (alphanumeric)
	bool isValidUsername(const std::string &username)
	{
		for (std::size_t i = 0; i < username.length(); ++i)
		{
			if (!std::isalnum(username[i])) // Check if the character is not alphanumeric
			{
				return false;
			}
		}
		return true;
	}

	// Encrypt the password
	std::string encryptPassword(const std::string &password, int shift)
	{
		std::string encryptedPassword = password;
		for (std::size_t i = 0; i < password.length(); ++i)
		{
			if (std::isalpha(password[i]))
			{
				char base = std::islower(password[i]) ? 'a' : 'A';
				encryptedPassword[i] = (password[i] - base + shift) % 26 + base;
			}
			else if (std::isdigit(password[i]))
			{
				encryptedPassword[i] = (password[i] - '0' + shift) % 10 + '0';
			}
		}
		return encryptedPassword;
	}

	// Register a new user
	bool UserRegister(sf::RenderWindow &window, std::string &username, std::string &password, std::string &role)
	{
		bool validUsername = false;
		do
		{
			if (isValidUsername(username))
			{
				std::ifstream in("users.txt");
				std::string fileUsername;
				bool usernameExists = false;

				while (in >> fileUsername)
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (fileUsername == username)
					{
						usernameExists = true;
						break;
					}
				}
				in.close();

				if (usernameExists)
				{
					showPopup(window, "Username already exists!", sf::Vector2f(500, 60), "Error");
					return false;
				}
				else
				{
					validUsername = true;
				}
			}
			else
			{
				showPopup(window, "Invalid Username! Only alphabets and numbers are allowed.", sf::Vector2f(500, 60), "Error");
			}
		} while (!validUsername);

		int roleChoice;
		bool validRole = false;

		while (!validRole)
		{
			if (role == "Listener" || role == "Musician")
			{
				validRole = true;
			}
			else
			{
				showPopup(window, "Invalid Role!", sf::Vector2f(500, 60), "Error");
				return false;
			}
		}

		std::string encryptedPassword = encryptPassword(password, 7);

		std::ofstream out("users.txt", std::ios::app); // Only std::ios::app is needed for appending
		if (!out)
		{
			error("Error opening file for writing.");
			return false;
		}
		out << username << " " << encryptedPassword << " " << role << std::endl;
		out.close();

		std::cout << "Registration successful! You are a " << role << "." << std::endl;
		return true;
	}

	// Login an existing user
	bool UserLogin(sf::RenderWindow &window, std::string &username, std::string &password)
	{
		std::ifstream in("users.txt");
		if (!in)
		{
			error("Error opening file for reading.");
			return false;
		}
		bool validUsername = false;
		do
		{
			if (isValidUsername(username))
			{
				validUsername = true;
			}
			else
			{
				showPopup(window, "Invalid Username!", sf::Vector2f(500, 60), "Error");
				return false;
			}
		} while (!validUsername);

		std::string encryptedPassword = encryptPassword(password, 7);

		std::string fileUsername, filePassword, fileRole, role;
		bool loginSuccess = false;

		while (in >> fileUsername >> filePassword >> fileRole)
		{
			if (fileUsername == username && filePassword == encryptedPassword)
			{
				role = fileRole;
				loginSuccess = true;
				break;
			}
		}

		in.close();

		if (loginSuccess)
		{
			std::cout << "Login successful! Welcome " << username << "." << std::endl;
			return true;
		}
		else
		{
			showPopup(window, "Invalid username or password.", sf::Vector2f(500, 60), "Error");
			return false;
		}
		return false;
	}

	// Getter methods
	std::string getUsername() const { return username; }
	std::string getPassword() const { return password; }
	std::string getRole() const { return role; }
};

#endif
