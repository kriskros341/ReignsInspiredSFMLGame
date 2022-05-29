#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MyRenderWindow.h"

extern sf::Font systemFont;
extern sf::Vector2f screenSize;

class Resource : public sf::RectangleShape {
	int* value = 0;
	sf::Text t;
	sf::Sprite s;
	sf::Vector2f startingPosition;
	sf::Texture resourceTexture;
	friend class MyRenderWindow;
public:
<<<<<<< Updated upstream
	Resource() {};
	Resource(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size) {
		t.setFont(systemFont);
		t.setString(std::to_string(100));
=======
	Resource()  {};
	Resource(sf::Vector2f size, sf::Vector2f position, int v, std::string texturePath) : sf::RectangleShape(size), value(v) {

		/*t.setFont(systemFont);
		t.setString(std::to_string(v));
		startingPosition = position;
		setPosition(startingPosition);

		t.setFillColor(sf::Color::Magenta);

		t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
		t.setPosition(startingPosition.x + size.x / 2.0, startingPosition.y + size.y / 2.0);*/
		
		/*resourceTexture.loadFromFile(texturePath);
		s.setTexture(resourceTexture);*/
		
		startingPosition = position;
		setPosition(startingPosition);
		s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
		s.setPosition(startingPosition.x + size.x / 2.0, startingPosition.y + size.y / 2.0);
	}
	void setValue(int newval) {
		value = newval;
		t.setString(std::to_string(value));
	};
	int getValue() {
		return value;
	};
>>>>>>> Stashed changes
};


float approx_linear(float input[2], float output[2], float value);

class GUI : public sf::RectangleShape {
	friend class MyRenderWindow;
	Resource* resources;
	const float resourceCount = 4;
public:
	GUI(sf::FloatRect rect, DecisionStats& stats) : sf::RectangleShape({rect.width, rect.height}) {
>>>>>>> Stashed changes
		float width = rect.width, height = rect.height;
		resources = new Resource[(int)resourceCount];
		for (int i = 0; i < resourceCount; i++) {
			resources[i] = Resource(
				{ width / resourceCount, height }, 
				{ rect.left + i * width / resourceCount, rect.top },
				stats[i]
			);

			/*if(i % 2 == 0)
				resources[i].setFillColor(sf::Color::Yellow);*/
		}
	};
};

float getAngleBetween(sf::Vector2f origin, sf::Vector2f theOther);

class MainCard : public sf::Sprite {
	bool isDragging = false;
	sf::FloatRect rect;
	sf::FloatRect starting;
	sf::Texture texture;
public:
	// width, height, left, top
	MainCard(sf::FloatRect s, std::string texturePath) : sf::Sprite() {
		setOrigin(s.width / 2.0, s.height / 2.0);
		starting = s;
		setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f);
		texture.loadFromFile(texturePath);
		setTexture(texture);
	}
	bool getDragging();
	void dragHorizontally(sf::Vector2f position);
	void restartDrag();
	void setDragging(bool n);
};

class NextCard : public sf::Sprite {
private:
	sf::Texture texture;
public:
	NextCard(sf::FloatRect s, std::string texturePath) : sf::Sprite() {
		setOrigin(s.width / 2.0, s.height / 2.0);
		setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f);
		texture.loadFromFile(texturePath);
		setTexture(texture);
	}
};

<<<<<<< Updated upstream
=======
// Wszystkie decyzje
class AllDecisions {
public:
	std::shared_ptr<Decision> currentDecision;
	std::vector<std::shared_ptr<Decision>> decisionPool;
};

>>>>>>> Stashed changes
class PlayableArea : public sf::RectangleShape {
	GUI gui;
	MainCard card;
	NextCard next;
	float guiOffset = 150;
	sf::RectangleShape yesZone, noZone;
	friend class Game;
	friend class MyRenderWindow;
public:
	//PlayableArea(sf::FloatRect rect) :
	PlayableArea(float width, float guiOffset) :
		sf::RectangleShape({ width, screenSize.y - guiOffset }),
<<<<<<< Updated upstream
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }),
		card({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 250, 250 })
=======
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }, stats),
		card({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 250, 250 })
	{
	sf::FloatRect rect = { screenSize.x / 2.0f - width / 2.0f, 0, width, screenSize.y };
	sf::Vector2f size = getSize();
	gui.setPosition(rect.left, 0);

	//CENTER
	setPosition(rect.left, guiOffset);

	yesZone.setSize({ 100, screenSize.y });
	noZone.setSize({ 100, screenSize.y });

	yesZone.setPosition(rect.left + rect.width, 0);
	noZone.setPosition(rect.left - 100, 0);
	yesZone.setFillColor(sf::Color{ 48, 42, 39 });
	noZone.setFillColor(sf::Color{ 48, 42, 39 });
	setFillColor(sf::Color{160, 148, 133});
	}

};

class Game {
	AllDecisions decision;
	PlayableArea area;
	friend class MyRenderWindow;
	DecisionStats statystyki{100, 100, 100, 100};
public:
	Game() : area(400, 150) {};
	
	bool doesIntersectWithMainCard(sf::FloatRect position);
	bool doesIntersectWithMainCard(sf::Vector2f position);
	void setDragging(bool n);
	void restartDrag();
	bool getDragging();
	void dragCard(sf::Vector2f position);
	void makeChoice();
};
