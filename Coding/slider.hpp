#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "error.hpp"

using namespace sf;
using namespace std;

class Slider
{
private:
	RectangleShape track;
	RectangleShape overlayTrack;
	CircleShape thumb;
	Text currentDuration;
	Text totalDuration;
	Font font;
	float minValue, maxValue;
	float currentValue;

public:
	Slider(Vector2f position, Vector2f size, float minValue = 0, float maxValue = 100) : minValue(minValue), maxValue(maxValue), currentValue(minValue)
	{
		Color color(0x071952FF);
		Color color2(0xFD3A69FF);

		track.setSize(size);
		track.setFillColor(Color(0, 0, 0, 100));
		track.setPosition(position);

		overlayTrack.setPosition(position);
		overlayTrack.setSize(Vector2f(0, size.y));
		overlayTrack.setFillColor(color);

		thumb.setRadius(size.y - 2);
		thumb.setFillColor(Color(255, 255, 255));
		thumb.setOutlineThickness(2);
		thumb.setOutlineColor(color);
		thumb.setPosition(position.x, (track.getPosition().y - (thumb.getRadius() / 2)));

		if (!font.loadFromFile("Coding/static/Poppins-Medium.ttf"))
		{
			error("Error Loading Font File.");
			return;
		}

		currentDuration.setFont(font);
		currentDuration.setCharacterSize(18);
		currentDuration.setFillColor(color2);
		currentDuration.setPosition(position.x, position.y - 30);
		currentDuration.setStyle(Text::Bold);

		totalDuration.setFont(font);
		totalDuration.setCharacterSize(18);
		totalDuration.setFillColor(color2);
		totalDuration.setPosition(position.x + size.x - 42, position.y - 30);
		;
		totalDuration.setStyle(Text::Bold);
	}
	void setTotalDuration(int seconds)
	{
		int minutes = seconds / 60;
		int remainingSeconds = seconds % 60;
		string message = to_string(minutes) + ":" + (remainingSeconds < 10 ? "0" : "") + to_string(remainingSeconds);
		totalDuration.Bold;
		totalDuration.setString(message);
	}
	void setCurrentDuration(int seconds)
	{
		int minutes = seconds / 60;
		int remainingSeconds = seconds % 60;
		string message = to_string(minutes) + ":" + (remainingSeconds < 10 ? "0" : "") + to_string(remainingSeconds);
		currentDuration.Bold;
		currentDuration.setString(message);
	}
	void setThumbPosition(float value)
	{
		Color color(0x071952FF);
		currentValue = value;
		float ratio = (value - minValue) / (maxValue - minValue);
		thumb.setPosition(track.getPosition().x + ratio * track.getSize().x - thumb.getRadius(), track.getPosition().y - (thumb.getRadius() / 2));
		overlayTrack.setPosition(track.getPosition().x, track.getPosition().y);
		if (value == minValue)
			overlayTrack.setSize(Vector2f(0, track.getSize().y));
		else
		{
			if (value == maxValue)
				overlayTrack.setSize(track.getSize());
			else
				overlayTrack.setSize(Vector2f(ratio * track.getSize().x, track.getSize().y));
		}
		overlayTrack.setFillColor(color);
	}
	float getTrackPosition()
	{
		return track.getPosition().x;
	}
	float getTrackWidth()
	{
		return track.getSize().x;
	}
	float getThumbPosition()
	{
		return currentValue;
	}
	int onTrackClick(Vector2f position)
	{
		if (thumb.getGlobalBounds().contains(position))
			return 1;
		else if (track.getGlobalBounds().contains(position))
			return 2;
		return 0;
	}

	void draw(RenderWindow &window)
	{
		window.draw(track);
		window.draw(overlayTrack);
		window.draw(thumb);
		window.draw(currentDuration);
		window.draw(totalDuration);
	}
};

#endif