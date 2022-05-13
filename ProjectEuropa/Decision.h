#pragma once
#include <string>
#include <SFML/Graphics.hpp>

int getNextId();

class Decision {
public:
	std::string uuid = std::to_string(getNextId());
	Decision* yes = 0;
	int changeYes[4]{};
	Decision* no = 0;
	int changeNo[4]{};
	std::string text;
	std::string imagePath;
	Decision(const std::string& t) {
		text = t;
		imagePath = "dodo";
	}
};


class Connector : public sf::CircleShape {
	bool connected = false;
	sf::Vector2f position;
public:
	Connector(sf::Vector2f position) : sf::CircleShape(5, 5) {
		setOrigin(5, 5);
		setPosition(position);
	};

	bool getConnected();
	void setConnected(bool c);
};

class DecisionBox;

class DecisionConnector : public Connector {
	Connector* target = 0;
	bool isYes = false;
	bool selected = false;
public:
	sf::VertexArray line;
	DecisionConnector(sf::Vector2f p, bool f) : Connector(p) {
		isYes = f;
		line = sf::VertexArray(sf::Lines, 2);
		setFillColor(isYes ? sf::Color::Green : sf::Color::Red);
	}
	void setSelected(bool s);
	bool getSelected();
	void updateOutline();
	void onSelect();
	void setConnection(DecisionBox& b);
};

class DecisionBox : public sf::CircleShape {
public:
	float radius = 25;
	sf::Text textField;
	Decision decision;
	DecisionConnector yesFrom;
	DecisionConnector noFrom;
	Connector socket;
	bool selected = false;
	DecisionBox(sf::Vector2f position = { 400, 600 }) :
		decision("default"),
		sf::CircleShape(25, 25),
		yesFrom(position + sf::Vector2f(radius, 0), true),
		noFrom(position + sf::Vector2f(-radius, 0), false),
		socket(position + sf::Vector2f(0, radius))
	{
		setOrigin(25, 25);
		setPosition(position);
	}

	void updateOutline();
	void toggleSelected();
	void setSelected(bool k);
	bool getSelected();
	bool checkForClick(sf::Vector2i mousePosition);
};

class DecisionBoxSelector {
	DecisionBox* selected;
};
