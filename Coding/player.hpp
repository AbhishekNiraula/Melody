#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "error.hpp"
#include "popup.hpp"
#include "slider.hpp"

using namespace std;
using namespace sf;

enum class PlayMode {
    RepeatOn,
    RepeatOff,
    Shuffle
};

int player(string username = "Listener")
{
    
    ContextSettings settings;
    settings.antialiasingLevel = 10;

    RenderWindow window(VideoMode(700, 600), "Melody Tunes", Style::Default, settings);
    
    Color color(0x071952FF);
    Color color2(0xFD3A69FF);
    Color color3(0x6F6F6FFF);

    Music music;
    if (!music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Co2.wav"))
    {
        error("Error Loading Music File.");
        return 1;
    }
    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }

    Texture background, musicSprite;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Melody.png"))
    {
        error("Error Loading Background File.");
        return 1;
    }
    if (!musicSprite.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/co2.jpg"))
    {
        musicSprite.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/error-musician.jpg");
        showPopup(window, "Error Loading Music Image", Vector2f(400, 60), "Error");
    }
    musicSprite.setSmooth(true);
    Texture playTexture, pauseTexture, playBackTexture, playForwardTexture, playNextTexture, playPrevTexture, repeatTexture, nonRepeatTexture, shuffleTexture, heartFillTexture, heartStrokeTexture;
    if (!playTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/play.png") || !pauseTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/pause.png") || !playBackTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-left.png") || !playForwardTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-right.png") || !playPrevTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/previous.png") || !playNextTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/next.png") || !repeatTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Repeat.png") || !nonRepeatTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Non-Repeat.png") || !shuffleTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Shuffle.png") || !heartFillTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/heart-fill.png") || !heartStrokeTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/heart-stroke.png"))
    {
        error("Error Loading Icons.");
        return 1;
    }

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    Sprite backgroundSprite(background);
    Vector2u textureSize = background.getSize(); 
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);


    music.pause();

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }
    
    string welcomeText = "Hey, " + username;

    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);

    Text musicName("CO2", font, 30);
    musicName.setStyle(Text::Bold);
    musicName.setFillColor(color);
    musicName.setPosition(window.getSize().x / 2 - musicName.getGlobalBounds().width / 2, 330);
    
    Text musician("Prateek Kuhad", font, 20);
    musician.setStyle(Text::Regular);
    musician.setFillColor(color3);
    musician.setPosition(window.getSize().x / 2 - musician.getGlobalBounds().width / 2, 380);

    const int numBars = 5;
    RectangleShape bars[numBars];

    float barWidth = 7.0f;
    float spacing = 5.0f;
    for (int i = 0; i < numBars; ++i)
    {
        bars[i].setSize(Vector2f(barWidth, 50));
        bars[i].setPosition(i * (barWidth + spacing) + 318, (window.getSize().y / 2) + 140);
        bars[i].setFillColor(color2);
    }
    Clock clock;

    Sprite playSprite(playTexture);
    Sprite pauseSprite(pauseTexture);
    Sprite repeatSprite(repeatTexture);
    Sprite nonRepeatSprite(nonRepeatTexture);
    Sprite shuffleSprite(shuffleTexture);
    Sprite heartFillSprite(heartFillTexture);
    Sprite heartStrokeSprite(heartStrokeTexture);

    
    CircleShape musicImage(75);
    musicImage.setTexture(&musicSprite);
    musicImage.setTextureRect(IntRect(0, 0, musicSprite.getSize().x, musicSprite.getSize().y));
    musicImage.setPosition(window.getSize().x / 2 - musicImage.getRadius(), 145);

    musicImage.setOutlineColor(color);
    musicImage.setOutlineThickness(2);

    Vector2f iconSize(70.f, 70.f);
    playSprite.setScale(iconSize.x / playTexture.getSize().x, iconSize.y / playTexture.getSize().y);
    pauseSprite.setScale(iconSize.x / pauseTexture.getSize().x, iconSize.y / pauseTexture.getSize().y);

    playSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2 + 240);
    pauseSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2 + 240);

    Sprite playBack(playBackTexture);
    Sprite playForward(playForwardTexture);
    Vector2f iconSize2(40.f, 40.f);
    Vector2f iconSize3(30.f, 30.f);
    playBack.setPosition((windowSize.x / 2 - iconSize2.x / 2) - 70, windowSize.y/2 - iconSize2.y / 2 + 240);
    playForward.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 70, windowSize.y/2 - iconSize2.y / 2 + 240);


    repeatSprite.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 200, windowSize.y/2 - iconSize2.y / 2 + 244);
    nonRepeatSprite.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 200, windowSize.y/2 - iconSize2.y / 2 + 244);
    shuffleSprite.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 200, windowSize.y/2 - iconSize2.y / 2 + 242);

    heartFillSprite.setPosition((windowSize.x / 2 - iconSize3.x / 2) - 200, (windowSize.y/2 - iconSize3.y / 2) + 240);
    heartStrokeSprite.setPosition((windowSize.x / 2 - iconSize3.x / 2) - 200, (windowSize.y/2 - iconSize3.y / 2) + 240);
    

    Sprite playNext(playNextTexture);
    Sprite playPrev(playPrevTexture);


    playNext.setPosition((windowSize.x / 2 - iconSize3.x / 2) + 130, (windowSize.y/2 - iconSize3.y / 2) + 240);
    playPrev.setPosition((windowSize.x / 2 - iconSize3.x / 2) - 130, (windowSize.y/2 - iconSize3.y / 2) + 240);

    Slider playerSlider(Vector2f(100, 483), Vector2f(500, 10));
    playerSlider.setTotalDuration(music.getDuration().asSeconds());
    playerSlider.setThumbPosition(0);


    bool isPlaying = false;
    bool shuffleOn = false;

    PlayMode currentMode = PlayMode::RepeatOff;



    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                if (music.getStatus() == Music::Playing)
                {
                    music.pause();
                    isPlaying = false;
                }
                else
                {
                    music.play();
                    isPlaying = true;
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                if (currentMode == PlayMode::RepeatOn) {
                    music.setLoop(false);
                    showPopup(window, "Shuffle On", Vector2f(400, 60));
                    currentMode = PlayMode::Shuffle;
                } 
                else if (currentMode == PlayMode::Shuffle) {
                    music.setLoop(false);
                    showPopup(window, "Repeat Off", Vector2f(400, 60));
                    currentMode = PlayMode::RepeatOff;
                } 
                else if (currentMode == PlayMode::RepeatOff) {
                    showPopup(window, "Repeat On", Vector2f(400, 60));
                    music.setLoop(true);
                    currentMode = PlayMode::RepeatOn;
                }
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (playSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) ||
                    pauseSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (music.getStatus() == Music::Playing)
                    {
                        music.pause();
                        isPlaying = false;
                    }
                    else
                    {
                        music.play();
                        isPlaying = true;
                    }
                }
                if (playForward.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
                if (playBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
                if (playerSlider.onTrackClick(Vector2f(event.mouseButton.x, event.mouseButton.y)) == 2)
                {
                    float ratio = (event.mouseButton.x - playerSlider.getTrackPosition()) / playerSlider.getTrackWidth();
                    float newTime = ratio * 100;
                    playerSlider.setThumbPosition(newTime);
                    music.setPlayingOffset(seconds(newTime * music.getDuration().asSeconds() / 100));
                }
                if (playNext.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav");
                    music.play();
                    isPlaying = true;
                }
                if (playPrev.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav");
                    music.play();
                    isPlaying = true;
                }
                if (repeatSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || nonRepeatSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || shuffleSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                    if (currentMode == PlayMode::RepeatOn) {
                        music.setLoop(false);
                        showPopup(window, "Shuffle On", Vector2f(400, 60));
                        currentMode = PlayMode::Shuffle;
                    } 
                    else if (currentMode == PlayMode::Shuffle) {
                        music.setLoop(false);
                        showPopup(window, "Repeat Off", Vector2f(400, 60));
                        currentMode = PlayMode::RepeatOff;
                    } 
                    else if (currentMode == PlayMode::RepeatOff) {
                        showPopup(window, "Repeat On", Vector2f(400, 60));
                        music.setLoop(true);
                        currentMode = PlayMode::RepeatOn;
                    }
                }
            }
        }


        float currentValue = playerSlider.getThumbPosition();
        Time currentTime = music.getPlayingOffset();
        Time duration = music.getDuration();
        playerSlider.setCurrentDuration(currentTime.asSeconds());
        currentValue = (currentTime.asSeconds() / duration.asSeconds()) * 100;
        playerSlider.setThumbPosition(currentValue);

        float time = clock.getElapsedTime().asSeconds();
        if (music.getStatus() == Music::Playing)
        {
            for (int i = 0; i < numBars; ++i)
            {
                float amplitude = 15.0f * std::sin(time * 4 + i);
                bars[i].setSize(Vector2f(barWidth, amplitude + 20));
                bars[i].setPosition(bars[i].getPosition().x, (window.getSize().y / 2 + 140) - amplitude / 2);
            }
        }
        else {
            for (int i = 0; i < numBars; ++i)
            {
                bars[i].setSize(Vector2f(barWidth, 10));
                bars[i].setPosition(bars[i].getPosition().x, window.getSize().y / 2 + 140);
            }
        }

        if (music.getStatus() == Music::Stopped && !music.getLoop())
        {
            isPlaying = false;
        }

        window.clear(Color::White);
        window.draw(backgroundSprite);
        window.draw(text);
        window.draw(musicImage);
        for (int i = 0; i < numBars; i++)
        {
            window.draw(bars[i]);
        }
        window.draw(playBack);
        window.draw(playForward);
        window.draw(playPrev);
        window.draw(musicName);
        window.draw(musician);
        window.draw(playNext);
        if (isPlaying)
            window.draw(pauseSprite);
        else
            window.draw(playSprite);
        if (currentMode == PlayMode::RepeatOn) {
            window.draw(repeatSprite);
        } 
        else if (currentMode == PlayMode::RepeatOff) {
            window.draw(nonRepeatSprite);
        } 
        else if (currentMode == PlayMode::Shuffle) {
            window.draw(shuffleSprite);
        }
        window.draw(heartStrokeSprite);
        playerSlider.draw(window);
        window.display();
    }

    return 0;
}
