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
//-----------IKONKI ZASOBÓW----------------
class ResourceCover : public sf::Sprite {
	sf::Texture texture;
	friend class Resource;
	friend class MyRenderWindow;
public:
	ResourceCover() {};
	ResourceCover(std::string texturePath, float nthChild) : sf::Sprite() {
		texture.loadFromFile(texturePath);
		setTexture(texture);
		setPosition(212.5f + 100.0f * (nthChild - 1), 0);
	}
	
};
//---------ZNACZNIKI ZWIÊKSZANIA/ZMNIEJSZANIA SIÊ STATÓW----------
class Indicator : public sf::CircleShape {
public:
	Indicator()
	{
		setFillColor(sf::Color{ 160, 148, 133 });
		setRadius(5);
		setOrigin(5, 5);
	}
};
//------------POLE ZWIÊKSZAJ¥CE/ZMNIEJSZAJ¥CE SIÊ POD WP£YWEM DECYZJI----------
class Resource : public sf::RectangleShape {
	int value;
	int currentSize = 100;
	friend class MyRenderWindow;
	friend class ResourceCover;
	Indicator up;
	sf::RectangleShape underlayingCover;
public:
	Resource() {};
	Resource(sf::Vector2f size, sf::Vector2f position, int v, int nthChild) : sf::RectangleShape(size), value(v)
	{
		//setFillColor(sf::Color{210, 205, 199, 255});
		setSize({60, 130});
		setPosition(212.5f + 100.0f * (nthChild), 0);
		setFillColor(sf::Color::Red);
		
		underlayingCover.setFillColor(sf::Color{210, 205, 199, 255});
		//underlayingCover.setFillColor(sf::Color::Red);
		underlayingCover.setSize({60, 130});
		underlayingCover.setPosition(212.5f + 100.0f * (nthChild), 0);
		up.setPosition(212.5f + getSize().x / 2 + 100.0f * (nthChild)+1.0f, getSize().y / 2 - 30);
	}
	void setValue(int newval) {
		value = newval;
	};
	int getValue() {
		return value;
	};
	void changeHeight(int val)
	{
		underlayingCover.setSize({ 60.0f, 130.0f - 130.0f / 100.0f * value });
	};
};

float approx_linear(float input[2], float output[2], float value);
//--------------------------------STATY----------------------------------
class GUI : public sf::RectangleShape {
	friend class MyRenderWindow;
	Resource* resources;
	const int resourceCount = 4;
	ResourceCover flora, human, money, rocket;
public:
	GUI(sf::FloatRect rect, DecisionStats& stats) : sf::RectangleShape({ rect.width, rect.height }),
		flora("./assets/flora.png", 1),
		human("./assets/human.png", 2),
		money("./assets/money.png", 3),
		rocket("./assets/rocket.png", 4)
	{
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
	Resource* getResources(int a) {
		if (a >= 0 && a <= 3)
			return resources + a - 1;
		else std::cout << "Couldn't get resource" << std::endl;
	}
	void updateBars(DecisionStats& s) {
		for (int i{}; i < 4; i++) {
			resources[i].setValue(s[i]);
			resources[i].changeHeight(s[i]);
		}
	}
};

float getAngleBetween(sf::Vector2f origin, sf::Vector2f theOther);
class MyRenderWindow;
//----------------------KARTA G£ÓWNA-------------------
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
	void setImage(const std::string& path) {
		texture.loadFromFile(path);
		setTexture(texture);
	};
	bool getDragging();
	void dragHorizontally(sf::Vector2f position);
	void restartDrag();
	void setDragging(bool n);
};
//--------------NASTÊPNA KARTA----------------------
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
//-------------PRZYCISK POWROTU DO MENU--------------
class Button : public sf::Sprite {
private:
	sf::Texture buttonTex;
public:
	Button() : sf::Sprite()
	{
		buttonTex.loadFromFile("./assets/exit-to-menu-button.png");
		setTexture(buttonTex);
		setPosition(100.0, 10.0);
	}
};
void splitTo(std::string str, const char seperator, std::vector<std::string>& cont);
//------------------------------DECYZJE-------------------------------
class AllDecisions {
public:
	std::shared_ptr<Decision> starting;
	std::shared_ptr<Decision> currentDecision;
	std::vector<std::shared_ptr<Decision>> decisionPool;
	std::shared_ptr<Decision> deathDecisions[4] = { decisionFactory(
		"Your food banks has been depleted\n and soon you will all die of hunger.\n Game Over.",
		connectionFactory("Nooooooooooooooooo!!!", { 0, 0, 0, 0 }, nullptr),
		connectionFactory("Oh shi--!", { 0, 0, 0, 0 }, nullptr)
		, "./assets/dead-card-1.png"
	),
		decisionFactory(
		"Because of your harsh management, the crew \ndecided to riot against you and throw \nyou out of the airlock in your sleep.\n Game Over.",
		connectionFactory("Nooooooooooooooooo!!!", { 0, 0, 0, 0 }, nullptr),
		connectionFactory("Oh shi--!", { 0, 0, 0, 0 }, nullptr)
		, "./assets/dead-card-1.png" //teraz nie dzia³a
	),
		decisionFactory(
		"You have become broke and cannot pay \nspace taxes. Your ship was confiscated \nand you became stranded on the moon.\n Game Over.",
		connectionFactory("Nooooooooooooooooo!!!", { 0, 0, 0, 0 }, nullptr),
		connectionFactory("Oh shi--!", { 0, 0, 0, 0 }, nullptr)
		, "./assets/dead-card-1.png"
	),
		decisionFactory(
		"Because of the ship's drastic state,\n it exploded into millions of pieces, \nkilling you and the whole crew on the ship. \nGame Over.",
		connectionFactory("Nooooooooooooooooo!!!", { 0, 0, 0, 0 }, nullptr),
		connectionFactory("Oh shi--!", { 0, 0, 0, 0 }, nullptr)
		, "./assets/dead-card-1.png"
	) };
	bool deathEnabled = false;
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
			deathEnabled = true;
			do{
				decisionId = rand() % decisionPool.size();
				currentDecision = decisionPool[decisionId];
			} while (currentDecision->getToBeUsed()==false);
			
			saveProgress();
		}
	};
	void saveProgress() {
		std::ofstream file{ "./saved.txt" };
		file << serializeData();
	}
};

//--------------WSZYSTKO CO WIDZI GRACZ W EKRANIE GRY-------------

class PlayableArea : public sf::RectangleShape {
	AllDecisions decision;
	GUI gui;
	MainCard card;
	NextCard next;
	Button backButton;
	float guiOffset = 150, guiOffsetY = 800;
	sf::RectangleShape yesZone, noZone, bottomTextZone;
	sf::Text decisionText, yesText, noText;
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
		bool wasDied=false;
		for (int i = 0; i < 4; i++)
		{
			if (decision.stats[i] <= 0&&decision.deathEnabled)
			{
				decision.currentDecision = decision.deathDecisions[i];
				wasDied = true;
			}
			
		}
		if(!wasDied)
			decision.moveThroughConnector(whichOption);
		decision.stats.cout();
		card.setImage(decision.currentDecision->getImagePath());
		updateGUI();
		updateText();
		std::cout << decision.currentDecision->getText() << std::endl;
		
	}
	void updateGUI() {
		std::cout << decision.stats[0] << " " <<  decision.stats[1] << " "<< decision.stats[2] << " " << decision.stats[3] << " " <<std::endl;
		gui.updateBars(decision.stats);
		//gui.
	}
	int* getChoiceIndicators(bool choice) {
		//if (choice)
				//potrzebujê tu tablicy ze zmian¹ statów dla decyzji w prawo
		//potrzebujê tu tablicy ze zmian¹ statów dla decyzji w lewo

	}
	sf::Text* getChoiceText(bool choice) {
		if (choice)
			return &yesText;
		return &noText;
	}
	void updateText() {
		decisionText.setString(decision.currentDecision->getText());
		yesText.setString(decision.currentDecision->getYesDecision()->getConnectorText());
		noText.setString(decision.currentDecision->getNoDecision()->getConnectorText());

		decisionText.setFont(systemFont);
		decisionText.setOrigin(decisionText.getLocalBounds().width / 2.0f, decisionText.getLocalBounds().height / 2.0f);
		decisionText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f - 200.0f);
		decisionText.setCharacterSize(20);
		decisionText.setFillColor(sf::Color{ 27, 24, 22 });

		yesText.setFont(systemFont);
		yesText.setOrigin(yesText.getLocalBounds().width / 2.0f, yesText.getLocalBounds().height / 2.0f);
		yesText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 340.0f);
		yesText.setCharacterSize(20);
		yesText.setFillColor(sf::Color{ 160, 148, 133 });

		noText.setFont(systemFont);
		noText.setOrigin(noText.getLocalBounds().width / 2.0f, noText.getLocalBounds().height / 2.0f);
		noText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 340.0f);
		noText.setCharacterSize(20);
		noText.setFillColor(sf::Color{ 160, 148, 133 });
	}
	PlayableArea(float width, float guiOffset) :
		sf::RectangleShape({ width, screenSize.y - guiOffset }),
		gui({ screenSize.x / 2.0f - width / 2.0f, 0, width, guiOffset }, decision.stats),
		next({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 300, 300 }, "./assets/backCard300x300.png"),
		backButton(),
		card({ screenSize.x / 2.0f, screenSize.y / 2.0f + 100.0f, 300, 300 }, defaultImage) 
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
		setStartingDecision(current);
		setDecisionPool(ListOfTrees);
		area.decisionText.setOrigin(area.decisionText.getLocalBounds().width / 2.0f, area.decisionText.getLocalBounds().height / 2.0f);
		area.decisionText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f - 200.0f);
		area.yesText.setOrigin(area.yesText.getLocalBounds().width / 2.0f, area.yesText.getLocalBounds().height / 2.0f);
		area.yesText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 340.0f);
		area.noText.setOrigin(area.noText.getLocalBounds().width / 2.0f, area.noText.getLocalBounds().height / 2.0f);
		area.noText.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f + 340.0f);
		if (flag == gameFlag::Load) {
			area.loadFromFile("./saved.txt");
		}
	};
	
	bool doesIntersectWithMainCard(sf::FloatRect position);
	bool doesIntersectWithMainCard(sf::Vector2f position);
	void setDragging(bool n);
	void restartDrag();
	bool getDragging();
	PlayableArea* getArea() {
		return &area;
	};
	void dragCard(sf::Vector2f position);
	void makeChoice();
	void coutAngle() {
		std::cout << area.getAngle() << std::endl;
	}

	int notificationTreshold = 3;
	void updateNotifiers() {
		if (area.getAngle() < 0 && area.getAngle() > -180 + notificationTreshold) {
			//std::cout << "-" << std::endl;
			//dodaæ tu rysowanie siê kropki nad zasobem
			
		}
		if (area.getAngle() > 0 && area.getAngle() < 180 - notificationTreshold) {
			//std::cout << "+" << std::endl;
		}
	}
	int getSideNotifier() {
		if (area.getAngle() < 0 && area.getAngle() > -180 + notificationTreshold) {
			return -1;

		}
		if (area.getAngle() > 0 && area.getAngle() < 180 - notificationTreshold) {
			return 1;
		}
		return 0;
	}
	void setStartingDecision(std::shared_ptr<Decision>& o) {
		area.decision.currentDecision = o;
		area.card.setImage(o->getImagePath());
		std::cout << area.decision.currentDecision->getText() << std::endl;
		area.decision.starting = o;
		area.updateGUI();
		area.updateText();
	}
	void setDecisionPool(std::vector<std::shared_ptr<Decision>>& o) {
		std::cout << "Decision Tree set" << std::endl;
		area.decision.decisionPool = o;
	}
};
