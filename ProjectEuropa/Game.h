#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MyRenderWindow.h"

extern sf::Font systemFont;
extern sf::Vector2f screenSize;

enum class gameFlag {
	New = 1,
	Load
};
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

class Indicator : public sf::CircleShape {
};

class Resource : public sf::RectangleShape {
	int value;
	friend class MyRenderWindow;
	friend class ResourceCover;
	Indicator up, down;
public:
	Resource() {};
	Resource(sf::Vector2f size, sf::Vector2f position, int v, int nthChild) : sf::RectangleShape(size), value(v)
	{
		setSize({60, 130});
		setPosition(212.5f + 100.0f * (nthChild), 0);
		setFillColor(sf::Color{210, 205, 199, 255});

		up.setRadius(5);
		up.setOrigin(5, 5);
		up.setPosition(212.5f + getSize().x/2 + 100.0f * (nthChild), getSize().y/2 - 25);
		down.setOrigin(5, 5);
		down.setRadius(5);
		down.setPosition(212.5f + getSize().x/2 + 100.0f * (nthChild), getSize().y/2 + 50);
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
class MyRenderWindow;

class MainCard : public sf::Sprite {
	bool isDragging = false;
	sf::FloatRect rect;
	sf::FloatRect starting;
	sf::Texture texture;
public:
	float getAngle();
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
void splitTo(std::string str, const char seperator, std::vector<std::string>& cont);
// Wszystkie decyzje
class AllDecisions {
public:
	std::shared_ptr<Decision> starting;
	std::shared_ptr<Decision> currentDecision;
	std::vector<std::shared_ptr<Decision>> decisionPool;
	int decisionId = -1;
	DecisionStats stats{50, 50, 50, 50};
	void loadFromFile(const std::string path = "./saved.txt") {
		std::ifstream file(path);
		std::stringstream content;
		std::vector<std::string> data;
		content << file.rdbuf();
		splitTo(content.str(), ' ', data);
		for (int i{}; i < 4; i++) {
			stats[i] = std::atoi(data[i].c_str());
		}
		int idx = std::atoi(data[4].c_str());
		loadDecisionByIndex(idx);
		std::cout << "LOADED WITH STATS ";
		stats.cout();

	};
	std::string serializeData() {
		std::stringstream data;
		data << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << " " << decisionId;
		return data.str();
	}
	void loadDecisionByIndex(int i) {
		if (i > 0 && i < decisionPool.size()) {
			currentDecision = decisionPool[i];
			decisionId = i;
			return;
		}
		std::cout << "DECISION PICK OUT OF RANGE. CHOOSING STARTING" << std::endl;
		currentDecision = starting;

	}
	void moveThroughConnector(bool route) {
		if (route) {
			currentDecision = currentDecision->getYesDecision()->getNextDecision();
		}
		else {
			currentDecision = currentDecision->getNoDecision()->getNextDecision();
		}
		if (currentDecision == nullptr) {
			decisionId = rand() % decisionPool.size();
			currentDecision = decisionPool[decisionId];
			saveProgress();
		}
	};
	void saveProgress() {
		std::ofstream file{ "./saved.txt" };
		file << serializeData();
	}
};

class PlayableArea : public sf::RectangleShape {
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
	void loadFromFile(const std::string path) {
		decision.loadFromFile(path);
	}
	void makeDecision(const bool whichOption) {
		if (!decision.currentDecision) {
			std::cout << "NO DECISION TO BE MADE" << std::endl;
			return;
		}
		decision.stats.apply(whichOption ? 
			getCurrentDecision()->getYesDecision()->getChangeParameters() :
			getCurrentDecision()->getNoDecision()->getChangeParameters()
		);
		decision.moveThroughConnector(whichOption);
		decision.stats.cout();
		updateGUI();
		std::cout << decision.currentDecision->getText() << std::endl;
	}
	void updateGUI() {
		gui.updateBars(decision.stats);
		//gui.
	}
	//PlayableArea(sf::FloatRect rect) :
	PlayableArea(float width, float guiOffset) :
		sf::RectangleShape({ width, screenSize.y - guiOffset }),
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }, decision.stats),
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
	float getAngle() {
		return card.getAngle();
	}

};


//Obiekt z którym gracz wchodzi w kontakt
class Game {
	PlayableArea area;
	friend class MyRenderWindow;
public:
	Game(std::shared_ptr<Decision> current, std::vector<std::shared_ptr<Decision>> ListOfTrees, gameFlag flag = gameFlag::New) : area(500, 150) {
		area.decision.currentDecision = current;
		area.decision.decisionPool = ListOfTrees;
		if (flag == gameFlag::Load) {
			area.loadFromFile("./saved.txt");
		}
	};
	
	bool doesIntersectWithMainCard(sf::FloatRect position);
	bool doesIntersectWithMainCard(sf::Vector2f position);
	void setDragging(bool n);
	void restartDrag();
	bool getDragging();
	void dragCard(sf::Vector2f position);
	void makeChoice();
	void coutAngle() {
		std::cout << area.getAngle() << std::endl;
	}

	int notificationTreshold = 3;
	void updateNotifiers() {
		if (area.getAngle() < 0 && area.getAngle() > -180 + notificationTreshold) {
			std::cout << "-" << std::endl;
		}
		if (area.getAngle() > 0 && area.getAngle() < 180 - notificationTreshold) {
			std::cout << "+" << std::endl;
		}
	}
	void setStartingDecision(std::shared_ptr<Decision>& o) {
		area.decision.currentDecision = o;
		std::cout << area.decision.currentDecision->getText() << std::endl;
		area.decision.starting = o;
	}
	void setDecisionPool(std::vector<std::shared_ptr<Decision>>& o) {
		area.decision.decisionPool = o;
	}
};
