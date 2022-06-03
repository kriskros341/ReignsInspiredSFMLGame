#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Logic.h"
#include "./MyRenderWindow.h"
#include "Game.h"
#include "Animation.h"

#pragma setLocale("utf-8");
#define papiez 2137420;

extern sf::Vector2f screenSize;
enum class IsIn {
	menu = 1,
	editor,
	game
};

std::vector<std::shared_ptr<Decision>> allTheDecisions() {
	std::vector<std::shared_ptr<Decision>> decisions;
	
	// Pojedyncza decyzja (losowana) ze wskaŸnikiem nullptr:
	std::shared_ptr<Decision> przykladowaPojedyncaDecyzja = decisionFactory(
		"drzewo",
		connectionFactory("wybor1", { 0, 0, 0, 0 }, nullptr), // najpierw tak
		connectionFactory("wybor2", { -50, -50, -50, -50 }, nullptr) // potem nie
	);
	decisions.push_back(przykladowaPojedyncaDecyzja);

	// Drzewo decyzji (event):
	std::shared_ptr<Decision> u1 = decisionFactory(
		"Drzewo1", 
		connectionFactory(
			"Drzewo1 L", {4, 4, 4, 4},
			decisionFactory(
				"Drzewo1 go L", 
				connectionFactory("Drzewo1 L go L", {4, 4, 4, 4}, nullptr),
				connectionFactory("Drzewo1 L go R", {4, 4, 4, 4}, nullptr)
				)),
		connectionFactory("Drzewo1 go R", {4, 4, 4, 4}, nullptr)
	);
	decisions.push_back(u1);


	std::shared_ptr<Decision> u2 = decisionFactory(
		"Drzewo2", 
		connectionFactory(
			"Drzewo2 go L", {4, 4, 4, 4},
			decisionFactory(
				"Drzewo2 L", 
				connectionFactory("Drzewo2 L go L", {4, 4, 4, 4}, nullptr),
				connectionFactory("Drzewo2 L go R", {4, 4, 4, 4}, nullptr)
				)),
		connectionFactory("Drzewo2 R", {4, 4, 4, 4}, nullptr)
	);
	decisions.push_back(u2);
	return decisions;
}

void game(MyRenderWindow& window) {
	std::shared_ptr<Decision> resChecks;
	std::shared_ptr<Decision> rescheck1;
	std::shared_ptr<Decision> rescheck2;
	std::shared_ptr<Decision> rescheck3;
	std::shared_ptr<Decision> rescheck4;
	std::shared_ptr<Decision> current = decisionFactory(
		"Tutorial 1",
		connectionFactory("Tutorial L", { -10, -6, -4, -1 }, nullptr),
		connectionFactory("Tutorial R", { 10, 6, 4, 1 }, nullptr)
	);
	rescheck1 = decisionFactory(
		"check 1",
		connectionFactory("check 1 L", { 10, 0, 0, 0 }, rescheck1),
		connectionFactory("check 1 R", { -10, 0, 0, 0 }, rescheck1)
	);
	rescheck2 = decisionFactory(
		"check 2",
		connectionFactory("check 2 L", { 0, 10, 0, 0 }, rescheck2),
		connectionFactory("check 2 R", { 0, -10, 0, 0 }, rescheck2)
	);
	rescheck3 = decisionFactory(
		"check 3",
		connectionFactory("check 3 L", { 0, 0, 10, 0 }, rescheck3),
		connectionFactory("check 3 R", { 0, 0, -10, 0 }, rescheck3)
	);
	rescheck4 = decisionFactory(
		"check 4",
		connectionFactory("check 4 L", { 0, 0, 0, 10 }, rescheck4),
		connectionFactory("check 4 R", { 0, 0, 0, -10 }, rescheck4)
	);

	resChecks = decisionFactory(
		"should enter 1?",
		connectionFactory("entering check 1", { 0, 0, 0, 0 }, rescheck1),
		connectionFactory("next check", { 0, 0, 0, 0 }, decisionFactory(
			"should enter 2?",
			connectionFactory("entering check 2", { 0, 0, 0, 0 }, rescheck2),
			connectionFactory("next check", { 0, 0, 0, 0 }, decisionFactory(
				"should enter 3?",
				connectionFactory("entering check 3", { 0, 0, 0, 0 }, rescheck3),
				connectionFactory("next check", { 0, 0, 0, 0 }, decisionFactory(
					"should enter 4?",
					connectionFactory("entering check 4", { 0, 0, 0, 0 }, rescheck4),
					connectionFactory("next check", { 0, 0, 0, 0 }, nullptr
					))
				))
			))
		)
	);
	std::vector<std::shared_ptr<Decision>> decisions = allTheDecisions();
	std::vector<std::shared_ptr<Decision>> checks = {resChecks};
	Game game;

	game.setStartingDecision(resChecks);
	game.setDecisionPool(checks);
	

	/*
	sf::CircleShape toCompare(4, 40);
	toCompare.setPosition(400, 400);
	sf::CircleShape* animationTest = new sf::CircleShape(4, 40);
	animationTest->setPosition(400, 400);
	animationTest->setFillColor(sf::Color::Black);
	float fadeRange[2] = { 0, 10 };
	FadeIn fade(animationTest, 0, fadeRange);
	*/

	float t{};
	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2i position = sf::Mouse::getPosition(window);
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::MouseButtonPressed: {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					game.setDragging(
						game.doesIntersectWithMainCard(sf::Vector2f(position))
					);
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				game.makeChoice();
				break;
			}
			case sf::Event::MouseMoved: {
				if (game.getDragging()) {
					game.dragCard(sf::Vector2f(position));
				}
				break;
			}
			}
		}

		//fade.animate((fadeRange[1] / 2.0) + (fadeRange[1] / 2.0) * std::sin(t));
		window.clear();
		window.draw(game);
		//window.draw(toCompare);
		//window.draw(fade);
		window.display();
		t += 0.05;
	}
}

void menu(MyRenderWindow& window, IsIn& state) {
	sf::Vector2f centerPoint(window.getSize().x / 2.0, window.getSize().y / 2.0);
	sf::RectangleShape start({ 200, 60 });
	sf::RectangleShape options({ 200, 60 });
	sf::RectangleShape exit({ 200, 60 });

	start.setPosition(centerPoint.x-(start.getSize().x/2.0), 220.0);
	options.setPosition(centerPoint.x-(options.getSize().x/2.0), 300.0);
	/*exit.setFillColor(sf::Color::Blue);*/
	exit.setPosition(centerPoint.x-(exit.getSize().x/2.0), 380.0);
	/*options.setFillColor(sf::Color::Blue);*/

	sf::Text startText;
	sf::Text optionsText;
	sf::Text exitText;


	startText.setString("Continue");
	sf::FloatRect startRect = startText.getLocalBounds();
	startText.setFont(systemFont);

	startText.setPosition(
		start.getPosition().x + start.getSize().x/2.0 - startText.getLocalBounds().width / 2.f, 
		start.getPosition().y + start.getSize().y/2.0 - startText.getLocalBounds().height / 1.f
	);
	startText.setFillColor(sf::Color::Black);

	
	optionsText.setString("Start a new");
	optionsText.setFont(systemFont);
	optionsText.setPosition(options.getPosition().x+(options.getSize().x/2.0)-optionsText.getLocalBounds().width / 2.f,options.getPosition().y+(options.getSize().y/2.0)-optionsText.getLocalBounds().height / 1.f);
	optionsText.setFillColor(sf::Color::Black);

	exitText.setString("Exit");
	exitText.setFont(systemFont);
	exitText.setPosition(exit.getPosition().x+(exit.getSize().x/2.0)-exitText.getLocalBounds().width / 2.f,exit.getPosition().y+(exit.getSize().y/2.0)-exitText.getLocalBounds().height / 1.f);
		/*start.getLocalBounds().left + start.getLocalBounds().width / 2) */
		;
	exitText.setFillColor(sf::Color::Black);
	
	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2i position = sf::Mouse::getPosition(window);

		while (window.pollEvent(event)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
					state = IsIn::game;
				}
			}
			case sf::Event::MouseButtonReleased: {
				if (event.key.code == sf::Mouse::Left) {
					if (start.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						state = IsIn::game;
					}
					if (options.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						state = IsIn::editor;
					}
				}
			}
			}
		}
		if (state != IsIn::menu)
			break;
		window.clear();
		// bg color: sf::Color{ 48, 42, 39 }
		window.draw(start);
		window.draw(options);
		window.draw(exit);
		window.draw(startText);
		window.draw(optionsText);
		window.draw(exitText);
		window.display();
	}
}


void working() {
	systemFont.loadFromFile("../Arial.ttf");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	MyRenderWindow window(sf::VideoMode((int)screenSize.x, (int)screenSize.y), "Space Explorers : The Game", settings);
	window.setFramerateLimit(60);
	IsIn state = IsIn::menu;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			}
			}
		}
		switch (state) {
		case IsIn::game: {
			game(window);
		};
		case IsIn::menu: {
			menu(window, state);
		};
		}

	}
}


void makeDecision(std::shared_ptr<Decision> currentDecision, bool switcher) {
	if (switcher == true)
	{
		currentDecision = std::move(currentDecision->getYesDecision()->getNextDecision());
	}
	else {
		currentDecision = std::move(currentDecision->getNoDecision()->getNextDecision());
	}

}
void prototype(std::shared_ptr<Decision> starterCard, std::vector<std::shared_ptr<Decision>> rands) {
	bool gameOn = true;
	std::shared_ptr<Decision> currentCard = starterCard;
	srand(time(NULL));
	while (gameOn) {
		std::cout << "Current card: " << currentCard->getText() << std::endl;
		std::cout << "Yes: " << currentCard->getYesDecision()->getConnectorText() << std::endl;
		std::cout << "No: " << currentCard->getNoDecision()->getConnectorText() << "\n(1 for true, anything else for false)";
		int a;
		std::cin >> a;
		std::cin.clear();
		if (currentCard == nullptr) {
			break;
		}
		if (a == 1) {
			currentCard = currentCard->getYesDecision()->getNextDecision();
		}
		else {
			currentCard = currentCard->getNoDecision()->getNextDecision();
		}
		if (currentCard == nullptr) {
			currentCard = rands[rand() % rands.size()];
		}
	}
}
;



int main() {
	std::cout << "Sprawdzamy gre? 1/cokolwiek innego" << std::endl;
	int in;
	std::cin >> in;
	if (in == 1) {
		working();
	}
	else {
		/*
		chcê mieæ
			Decision* d0 = DF(
				"Text", 
				CF("text", change, DF() | null), 
				CF("text", change, DF() | null)
			)
		*/
/*
		Decision* currentDecision;
		int change[4] = { 0,0,0,0 };
		Decision d0("Tutorial");
		Decision d1("Base Decision");
		Decision d2("Yes of Base");
		Decision d3("No of Base");
		Decision d4("Yes of First Yes");
		Decision d5("No of First Yes");
		Decision d6("Yes of First No");
		Decision d7("No of First No");
		Decision d8("Random Roll 1");
		Decision d9("Random Roll 2");
		std::vector<Decision*> randomDecisions = { &d1,&d8,&d9 };
		d0.setYes("Use this option to agree", change, &d1);
		d0.setNo("Use this option to disagree", change, &d1);
		d1.setYes("Go to base of Yes", change, &d2);
		d1.setNo("Go to base of No", change, &d3);
		d2.setYes("Go to Yes of first Yes", change, &d4);
		d2.setNo("Go to No of first Yes", change, &d5);
		d3.setYes("Go to Yes of first No", change, &d6);
		d3.setNo("Go to No of first No", change, &d7);
		d4.setYes("Route taken:Yes->Yes", change, nullptr);
		d4.setNo("Route taken:Yes->Yes", change, nullptr);
		d5.setYes("Route taken:Yes->No", change, nullptr);
		d5.setNo("Route taken:Yes->No", change, nullptr);
		d6.setYes("Route taken:No->Yes", change, nullptr);
		d6.setNo("Route taken:No->Yes", change, nullptr);
		d7.setYes("Route taken:No->No", change, nullptr);
		d7.setNo("Route taken:No->No", change, nullptr);
		d8.setYes("Go to base of Yes", change, &d2);
		d8.setNo("Go to base of No", change, &d3);
		d9.setYes("Go to base of Yes", change, &d2);
		d9.setNo("Go to base of No", change, &d3);
		prototype(&d0, randomDecisions);
*/
		/*Decision d("JDJDJDJ"); \\test 1
		Decision y("ggggg");
		const int changeD[4] = { 4, 1, 0, 1 };
		Decision n = Decision("neneenenennene");
		d.setYes("te", changeD, &y);
		d.setNo("sus", changeD, &n);
		std::cout << "oryginalna " << d.getText() << std::endl;
		currentDecision = &d;
		makeDecision(currentDecision, false);
		std::cout << "Zmieniona decyzja " << (currentDecision->getText()) << std::endl;*/
		/*if (currentDecision->getYesDecision() != nullptr) {
			std::cout << currentDecision->getYesDecision()->getConnectorText() << std::endl;
		std::cout << currentDecision->getNoDecision()->getConnectorText() << "\n";}*/
		/*}*/
	}
	return 1;
}
