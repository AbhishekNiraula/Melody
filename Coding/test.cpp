#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"
#include "listener.hpp"
#include "User.hpp"

using namespace sf;
using namespace std;

int login();
int loadFavorites(string);
int loadUpload(string);


Color color(0x071952FF);
Color color2(0xFD3A69FF);
Color color3(0x6F6F6FFF);

int home(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png") ||
        !uploadButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/upload.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }

    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Sprite homeSprite(homeButton);
    Sprite favouritesSprite(favouritesButton);
    Sprite logoutSprite(logoutButton);
    Sprite uploadSprite(uploadButton);

    string welcomeText = "Hey, " + username;

    Text homeText("Home", font, 25);
    homeText.setStyle(Text::Bold);
    homeText.setFillColor(color);
    homeText.setPosition(150, 100);

    Text welcomeTextObj(welcomeText, font, 19);
    welcomeTextObj.setStyle(Text::Bold);
    welcomeTextObj.setFillColor(color);
    welcomeTextObj.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    favouritesSprite.setPosition(10, 200);
    uploadSprite.setPosition(10, 250);
    logoutSprite.setPosition(10, 570);

    listener userListener(username);
    userListener.loadFromFile();
    vector<Song> songs = userListener.getCollection();
    vector<Sprite> songSprites;

    for (const auto& song : songs) {
        Texture songTexture;
        if (!songTexture.loadFromFile(song.getImagePath())) {
            showPopup(window, "Failed to load image: " + song.getImagePath(), Vector2f(400, 60), "Error");
            continue;
        }
        Sprite songSprite(songTexture);
        songSprites.push_back(songSprite);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mouseCoords = window.mapPixelToCoords(Mouse::getPosition(window));

                if (homeSprite.getGlobalBounds().contains(mouseCoords))
                {
                    return home(username); 
                }
                if (favouritesSprite.getGlobalBounds().contains(mouseCoords))
                {
                    return loadFavorites(username); 
                }
                if (uploadSprite.getGlobalBounds().contains(mouseCoords))
                {
                    return loadUpload(username); 
                }
                if (logoutSprite.getGlobalBounds().contains(mouseCoords))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                for (size_t i = 0; i < songSprites.size(); ++i) {
                    if (songSprites[i].getGlobalBounds().contains(mouseCoords)) {
                        window.close();
                        return player(username, songs[i].getFilePath(), songs[i].getImagePath(), songs[i].getSongName(), songs[i].getMusicianName());
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(welcomeTextObj);
        window.draw(homeText);
        window.draw(homeSprite);
        window.draw(favouritesSprite);
        window.draw(uploadSprite);
        window.draw(logoutSprite);

        // Draw the songs
        for (size_t i = 0; i < songSprites.size(); ++i) {
            float scaleX = 80.0f / songSprites[i].getLocalBounds().width;
            float scaleY = 80.0f / songSprites[i].getLocalBounds().height;
            songSprites[i].setScale(scaleX, scaleY);
            songSprites[i].setPosition(150, 150 + i * 200);

            Texture song2Texture;
            if (!song2Texture.loadFromFile(songs[i].getImagePath()))
            {
                cout << "Failed to load image: "  << songs[i].getImagePath() << endl;
            }
            song2Texture.setSmooth(true);
            Sprite song2Sprite(song2Texture);
            float scaleX2 = 80.0f / song2Sprite.getLocalBounds().width;
            float scaleY2 = 80.0f / song2Sprite.getLocalBounds().height;
            song2Sprite.setScale(scaleX2, scaleY2);
            song2Sprite.setPosition(150, 150 + i * 200);

            Text songNameText(songs[i].getSongName(), font, 20);
            songNameText.setFillColor(color);
            songNameText.setPosition(250, 170 + i * 100);

            Text musicianNameText("by " + songs[i].getMusicianName(), font, 12);
            musicianNameText.setFillColor(color3);
            musicianNameText.setPosition(250, 195 + i * 100);

            window.draw(songSprites[i]);
            window.draw(song2Sprite);
            window.draw(songNameText);
            window.draw(musicianNameText);
        }

        window.display();
    }
    return 0;
}


int loadFavorites(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png") ||
        !uploadButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/upload.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }


    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite s(background);
    Sprite homeSprite(homeButton);
    Sprite favourites(favouritesButton);
    Sprite logout(logoutButton);
    Sprite upload(uploadButton);

    Text text2("Favourites", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(color);
    text2.setPosition(150, 100);

    string welcomeText = "Hey, " + username;
    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    favourites.setPosition(10, 200);
    upload.setPosition(10, 250);
    logout.setPosition(10, 570);

    
    listener userListener(username);
    userListener.loadFromFile();
    vector<Song> favourites = userListener.getFavorites();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (homeSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    home(username);
                    return 1;
                }
                if (favourites.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadFavorites(username);
                    return 1;
                }
                if (upload.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadUpload(username);
                    return 1;
                }
                if (logout.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }
            }
        }
        window.draw(s);
        window.draw(homeSprite);
        window.draw(favourites);
        window.draw(upload);
        window.draw(logout);
        window.draw(text);
        window.draw(text2);
        window.display();
    }
    return 0;
}

int loadUpload(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton, uploadMusic;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png") ||
        !uploadButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/upload.png") ||
        !uploadMusic.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/uploadMusic.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }


    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite s(background);
    Sprite homeSprite(homeButton);
    Sprite favourites(favouritesButton);
    Sprite logout(logoutButton);
    Sprite upload(uploadButton);
    Sprite uploadMusicSprite(uploadMusic);

    listener listener(username);
    listener.loadFromFile();

    string welcomeText = "Hey, " + username;
    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    favourites.setPosition(10, 200);
    upload.setPosition(10, 250);
    logout.setPosition(10, 570);

    bool isHomePage = true;
    bool isFavourites = false;
    bool isUpload = false;

    Text text2("Upload", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(color);
    text2.setPosition(150, 100);

    Texture submitTexture;
    if (!submitTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Submit.png")) {
        error("Error Loading Submit Button.");
        return 1;
    }

    Sprite submitButton(submitTexture);
    submitButton.setPosition(300, 450);

    Text songNameText("Song Name:", font, 20);
    songNameText.setPosition(175, 155);
    songNameText.setFillColor(color);

    Text musicianNameText("Musician Name:", font, 20);
    musicianNameText.setPosition(175, 225);
    musicianNameText.setFillColor(color);

    Text filePathText("File Path:", font, 20);
    filePathText.setPosition(175, 295);
    filePathText.setFillColor(color);

    Text imagePathText("Image Path: ", font, 20);
    imagePathText.setPosition(175, 365);
    imagePathText.setFillColor(color);

    RectangleShape inputBox1(Vector2f(250, 40));
    inputBox1.setPosition(340, 150);
    inputBox1.setOutlineThickness(2);
    inputBox1.setOutlineColor(color);
    inputBox1.setFillColor(Color::White);

    RectangleShape inputBox2(Vector2f(250, 40));
    inputBox2.setPosition(340, 220);
    inputBox2.setOutlineThickness(2);
    inputBox2.setOutlineColor(color);
    inputBox2.setFillColor(Color::White);

    uploadMusicSprite.setPosition(340, 290);
    RectangleShape inputBox3(Vector2f(250, 40));
    inputBox3.setPosition(340, 290);
    inputBox3.setOutlineThickness(2);
    inputBox3.setOutlineColor(color);
    inputBox3.setFillColor(Color::White);

    RectangleShape inputBox4(Vector2f(250, 40));
    inputBox4.setPosition(340, 360);
    inputBox4.setOutlineThickness(2);
    inputBox4.setOutlineColor(color);
    inputBox4.setFillColor(Color::White);

    string songName = "";
    string musicianName = "";
    string filePath = "";
    string imagePath = "";

    bool inputActive[4] = {false, false, false, false};
    bool pushedInput = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                inputActive[0] = inputBox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                inputActive[1] = inputBox2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                inputActive[2] = inputBox3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                inputActive[3] = inputBox4.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);

                inputBox1.setOutlineColor(inputActive[0] ? color2 : color);
                inputBox2.setOutlineColor(inputActive[1] ? color2 : color);
                inputBox3.setOutlineColor(inputActive[2] ? color2 : color);
                inputBox4.setOutlineColor(inputActive[3] ? color2 : color);

                if (homeSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    home(username);
                    return 1;
                }
                if (favourites.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadFavorites(username);
                    return 1;
                }
                if (upload.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadUpload(username);
                    return 1;
                }
                // }
                // if (uploadMusicSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                // {

                //     filePath = dialog(); // Open file dialog to select file
                //     if (filePath.empty()) {
                //         showPopup(window, "No valid file selected. Exiting...", Vector2f(400, 60), "Error");
                //         loadUpload(username);
                //     }
                // }
                if (logout.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                if (submitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && !songName.empty() && !musicianName.empty() && !filePath.empty() && !imagePath.empty())
                {
                    listener.addSong(Song(songName, musicianName, filePath, imagePath));
                    listener.saveToFile();
                    showPopup(window, "Song Uploaded Successfully!", Vector2f(400, 60), "Success");
                    window.close();
                    home(username);
                    return 1; 
                }
            }

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if (inputActive[0] && !songName.empty()) songName.pop_back();
                    if (inputActive[1] && !musicianName.empty()) musicianName.pop_back();
                    if (inputActive[2] && !filePath.empty()) filePath.pop_back();
                    if (inputActive[3] && !imagePath.empty()) imagePath.pop_back();
                }
                else if (event.text.unicode < 128)
                {
                    if (inputActive[0]) songName += static_cast<char>(event.text.unicode);
                    if (inputActive[1]) musicianName += static_cast<char>(event.text.unicode);
                    if (inputActive[2]) filePath += static_cast<char>(event.text.unicode);
                    if (inputActive[3]) imagePath += static_cast<char>(event.text.unicode);
                }
            }
        }
        Text songNameInput(songName, font, 20);
        songNameInput.setPosition(350, 155);
        songNameInput.setFillColor(color);

        Text musicianNameInput(musicianName, font, 20);
        musicianNameInput.setPosition(350, 225);
        musicianNameInput.setFillColor(color);

        Text filePathInput(filePath, font, 10);
        filePathInput.setPosition(350, 295);
        filePathInput.setFillColor(color);

        Text imagePathInput(imagePath, font, 10);
        imagePathInput.setPosition(350, 365);
        imagePathInput.setFillColor(color);

        window.draw(s);
        window.draw(homeSprite);
        window.draw(favourites);
        window.draw(upload);
        window.draw(logout);
        window.draw(text);

        window.draw(text2);
        window.draw(songNameText);
        window.draw(musicianNameText);
        window.draw(filePathText);
        window.draw(imagePathText);
        window.draw(inputBox1);
        window.draw(inputBox2);
        window.draw(inputBox3);
        window.draw(inputBox4);
        // window.draw(uploadMusicSprite);
        window.draw(songNameInput);
        window.draw(filePathInput);
        window.draw(musicianNameInput);
        window.draw(imagePathInput);
        window.draw(submitButton);
        window.display();
    }
    return 0;
}