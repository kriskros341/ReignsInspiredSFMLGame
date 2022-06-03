#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MyRenderWindow.h"

extern sf::Font systemFont;
extern sf::Vector2f screenSize;

//class Resource : public sf::RectangleShape {
//	int value; // please do not edit here
//	sf::Text t;
//	sf::Vector2f startingPosition;
//	friend class MyRenderWindow;
//public:
//	Resource()  {};
//	Resource(sf::Vector2f size, sf::Vector2f position, int v) : sf::RectangleShape(size), value(v) {
//
//		/*t.setFont(systemFont);
//		t.setString(std::to_string(v));*/
//		startingPosition = position;
//		setPosition(startingPosition);
//		t.setFillColor(sf::Color::Magenta);
//		t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
//		t.setPosition(startingPosition.x + size.x / 2.0, startingPosition.y + size.y / 2.0);
//	}
//	void setValue(int newval) {
//		value = newval;
//		t.setString(std::to_string(value));
//
//	};
//	int getValue() {
//		return value;
//	};
//};

class ResourceCover : public sf::Sprite {
	sf::Texture texture;
	friend class MyRenderWindow;
public:
	ResourceCover() {};
	ResourceCover(std::string texturePath, float nthChild) : sf::Sprite() {
		texture.loadFromFile(texturePath);
		setTexture(texture);
		setPosition(212.5f + 100.0f * (nthChild - 1), 0);
	}
};

class Resource : public sf::RectangleShape {
	int value;
	friend class MyRenderWindow;
	friend class ResourceCover;
public:
	Resource() {};
	Resource(sf::Vector2f size, sf::Vector2f position, int v, int nthChild) : sf::RectangleShape(size), value(v)
	{
		setSize({60, 130});
		setPosition(212.5f + 100.0f * (nthChild), 0);
		setFillColor(sf::Color::Green);
	}
	void setValue(int newval) {
		value = newval;
	};
	int getValue() {
		return value;
	};
};

float approx_linear(float input[2], float output[2], float value);

class GUI : public sf::RectangleShape {
	friend class MyRenderWindow;
	Resource* resources;
	const int resourceCount = 4;
public:
	GUI(sf::FloatRect rect, DecisionStats& stats) : sf::RectangleShape({rect.width, rect.height}) {
		float width = rect.width, height = rect.height;
		resources = new Resource[resourceCount];
		for (int i = 0; i < resourceCount; i++) {
			resources[i] = Resource(
				{ width / resourceCount, height }, 
				{ rect.left + i * width / resourceCount, rect.top },
				stats[i],
				i
			);
		}
		
	};
	void updateBars(DecisionStats& s) {
		for (int i{}; i < 4; i++) {
			resources[i].setValue(s[i]);
		}
	}
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
	sf::Texture texture;
public:
	NextCard(sf::FloatRect s, std::string texturePath) : sf::Sprite() {
		setOrigin(s.width / 2.0, s.height / 2.0);
		setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f);
		texture.loadFromFile(texturePath);
		setTexture(texture);
	}
};

// Wszystkie decyzje
class AllDecisions {
public:
	std::shared_ptr<Decision> currentDecision;
	std::vector<std::shared_ptr<Decision>> decisionPool;
	void moveThroughConnector(bool route) {
		if (route) {
			currentDecision = currentDecision->getYesDecision()->getNextDecision();
		}
		else {
			currentDecision = currentDecision->getNoDecision()->getNextDecision();
		}
		if (currentDecision == nullptr) {
			currentDecision = decisionPool[rand() % decisionPool.size()];
		}
	};
};

class PlayableArea : public sf::RectangleShape {
	DecisionStats stats{100, 100, 100, 100};
	AllDecisions decision;
	GUI gui;
	MainCard card;
	NextCard next;
	ResourceCover flora, human, money, rocket;
	float guiOffset = 150, guiOffsetY = 800;
	sf::RectangleShape yesZone, noZone, bottomTextZone;
	friend class Game;
	friend class MyRenderWindow;
public:
	std::shared_ptr<Decision> getCurrentDecision() {
		return decision.currentDecision;
	}
	void makeDecision(bool whichOption) {
		if (!decision.currentDecision) {
			std::cout << "NO DECISION TO BE MADE" << std::endl;
			return;
		}
		stats.apply(whichOption ? 
			getCurrentDecision()->getYesDecision()->getChangeParameters() :
			getCurrentDecision()->getNoDecision()->getChangeParameters()
		);
		decision.moveThroughConnector(whichOption);
		stats.cout();
		updateGUI();
		std::cout << decision.currentDecision->getText() << std::endl;
	}
	void updateGUI() {
		gui.updateBars(stats);
		//gui.
	}
	//PlayableArea(sf::FloatRect rect) :
	PlayableArea(float width, float guiOffset) :
		sf::RectangleShape({ width, screenSize.y - guiOffset }),
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }, stats),
		next({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 300, 300 }, "./assets/backCard300x300.png"),
		flora("./assets/flora.png", 1),
		human("./assets/human.png", 2),
		money("./assets/money.png", 3),
		rocket("./assets/rocket.png", 4),
		card({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 300, 300 }, "./assets/captainRed300x300.png")
	{
		sf::FloatRect rect = { screenSize.x / 2.0f - width / 2.0f, 0, width, screenSize.y };
		gui.setFillColor(sf::Color{ 27, 24, 22 });
		sf::Vector2f size = getSize();
		gui.setPosition(rect.left, 0);

		//CENTER
		setPosition(rect.left, guiOffset);

		bottomTextZone.setSize({ 500, 100 });
		bottomTextZone.setPosition(guiOffset, guiOffsetY-100);
		bottomTextZone.setFillColor(sf::Color{ 27, 24, 22 });

		yesZone.setSize({ 100, screenSize.y });
		noZone.setSize({ 100, screenSize.y });

		yesZone.setPosition(rect.left + rect.width, 0);
		noZone.setPosition(rect.left - 100, 0);
		yesZone.setFillColor(sf::Color{ 48, 42, 39 });
		noZone.setFillColor(sf::Color{ 48, 42, 39 });
		setFillColor(sf::Color{160, 148, 133});
	}

};

//Obiekt z którym gracz wchodzi w kontakt
class Game {
	PlayableArea area;
	friend class MyRenderWindow;
public:
	Game() : area(500, 150) {};
	
	bool doesIntersectWithMainCard(sf::FloatRect position);
	bool doesIntersectWithMainCard(sf::Vector2f position);
	void setDragging(bool n);
	void restartDrag();
	bool getDragging();
	void dragCard(sf::Vector2f position);
	void makeChoice();
	void setStartingDecision(std::shared_ptr<Decision>& o) {
		area.decision.currentDecision = o;
		std::cout << area.decision.currentDecision->getText() << std::endl;
	}
	void setDecisionPool(std::vector<std::shared_ptr<Decision>>& o) {
		area.decision.decisionPool = o;
	}
};
