#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyRenderWindow.h"

extern sf::Font systemFont;
extern sf::Vector2f screenSize;

class Resource : public sf::RectangleShape {
	int* value = 0;
	sf::Text t;
	sf::Vector2f startingPosition;
	friend class MyRenderWindow;
public:
	Resource() {};
	Resource(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size) {
		t.setFont(systemFont);
		t.setString(std::to_string(100));
		startingPosition = position;
		setPosition(startingPosition);
		t.setFillColor(sf::Color::Magenta);
		t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
		t.setPosition(startingPosition.x + size.x / 2.0, startingPosition.y + size.y / 2.0);
	}
};


float approx_linear(float input[2], float output[2], float value);

class GUI : public sf::RectangleShape {
	friend class MyRenderWindow;
	Resource* resources;
	const float resourceCount = 4;
public:
	GUI(sf::FloatRect rect) : sf::RectangleShape({rect.width, rect.height}) {
		float width = rect.width, height = rect.height;
		resources = new Resource[(int)resourceCount];
		for (int i = 0; i < resourceCount; i++) {
			resources[i] = Resource(
				{ width / resourceCount, height }, 
				{ rect.left + i * width / resourceCount, rect.top }
			);

			if(i % 2 == 0)
				resources[i].setFillColor(sf::Color::Yellow);
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
	MainCard(sf::FloatRect s) : sf::Sprite() {
		setOrigin(s.width / 2.0, s.height / 2.0);
		starting = s;
		setPosition(screenSize.x / 2.0, screenSize.y / 2.0+100.0f);
	}
	bool getDragging();
	void dragHorizontally(sf::Vector2f position);
	void restartDrag();
	void setDragging(bool n);
};

class NextCard : public sf::Sprite {
public:
	NextCard() : sf::Sprite() {
		setOrigin(250.0 / 2.0, 250.0 / 2.0);
	}
};

class PlayableArea : public sf::RectangleShape {
	GUI gui;
	MainCard card;
	NextCard next;
	float guiOffset = 150;
	sf::RectangleShape yesZone, noZone;
	friend class Game;
	friend class MyRenderWindow;
	sf::Texture texture;
	sf::Texture personTexture;
public:
	//PlayableArea(sf::FloatRect rect) :
	PlayableArea(float width, float guiOffset) :
		sf::RectangleShape({ width, screenSize.y - guiOffset }),
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }),
		card({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 250, 250 })
	{
		sf::FloatRect rect = { screenSize.x / 2.0f - width / 2.0f, 0, width, screenSize.y };
		sf::Vector2f size = getSize();
		gui.setPosition(rect.left, 0);
	
		next.setPosition(screenSize.x / 2.0, screenSize.y / 2.0+100.0f);
		//next.setFillColor(sf::Color::Magenta);
		
		texture.loadFromFile("./assets/backCard250x250.png");
		personTexture.loadFromFile("./assets/captainRed.png");
		next.setTexture(texture);
		card.setTexture(personTexture);

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

// Wszystkie decyzje
class AllDecisions {
	std::shared_ptr<Decision> current;
	
	
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
