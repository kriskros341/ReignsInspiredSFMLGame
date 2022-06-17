#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Logic.h"
#include "./MyRenderWindow.h"
#include "Game.h"
#include "Animation.h"

#pragma setLocale("utf-8");
#define papiez 2137420;

extern sf::Vector2f screenSize;
extern enum class gameFlag;
enum class IsIn {
	menu = 1,
	editor,
	game,
	gameL,
	exit
};

std::vector<std::shared_ptr<Decision>> allTheDecisions() {
	std::vector<std::shared_ptr<Decision>> decisions;
	std::shared_ptr<Decision> randomD1;
	std::shared_ptr<Decision> randomD2;
	std::shared_ptr<Decision> randomD3;
	std::shared_ptr<Decision> randomD4;
	std::shared_ptr<Decision> randomD5;
	std::shared_ptr<Decision> randomD6;
	std::shared_ptr<Decision> randomD7;
	std::shared_ptr<Decision> randomD8;
	std::shared_ptr<Decision> randomD9;
	std::shared_ptr<Decision> randomD10;
	std::shared_ptr<Decision> randomD11;
	randomD11 = decisionFactory(
		"Cap'n, automatic health checks' program\n was a success! The engine will\n run them automatically and keep itself working!",
		connectionFactory("Yay!!", { 0,0,0,25 }, nullptr),
		connectionFactory("Yay...", { 0,0,0,25 }, nullptr), false,
		"./assets/orange.png"
	);
	randomD10 = decisionFactory(
		"Cap'n, I screwed up, the program turns\n out to be a virus, it caused\n disarray in the greenhouses!!!",
		connectionFactory("Shut it down!!", { -20,0,0,0 }, nullptr),
		connectionFactory("IT people nowadays...", { -20,0,0,0 }, nullptr), false,
		"./assets/orange.png"
	);
	randomD9=decisionFactory(
		" Eureka! By the use of corpse fertilizer,\n our crops have doubled in amount,\n size and growth speed!",
		connectionFactory("Yay!!", {50,0,0,0}, nullptr),
		connectionFactory("Yay...", {50,0,0,0}, nullptr), false,
		"./assets/yellow.png"
	);
	randomD8 = decisionFactory(
		"Captain, we cannot allow to desecrate our fallen people,\n it will decrease our people's morale drastically!",
		connectionFactory("You are right, I will overturn my decision", { 0,20,0,0 }, nullptr),
		connectionFactory("No, we have to get more crops", {0,-20,0,0 }, randomD9), false,
		"./assets/pink.png"
	);
	randomD7 = decisionFactory(
		"I found out that there is a way\n to use corpses to make the crops\n grow faster and stronger. Do you\n give me permission to reuse the bodies of our fallen ones?",
		connectionFactory("Yes, whatever to have more food", { 0,-20,0,0 }, randomD8),
		connectionFactory("No, it is immoral", { 0,0,0,0 }, nullptr), true,
		"./assets/yellow.png"
	);
	randomD6 = decisionFactory(
		"I recently saw a program which \nallows automatic plant maintenance. Should we trust it?",
		connectionFactory("Yeah, let's use it!", { 0,0,0,0 }, randomD10),
		connectionFactory("It's kinda sus…", { 0,0,0,0 }, nullptr), true,
		"./assets/orange.png"
	);
	randomD5 = decisionFactory(
		"I have found a program for running automatic\n health checks for the engines. Can we use it? ",
		connectionFactory("Of course!", { 0,0,0,0 }, randomD11),
		connectionFactory("We can't be sure if it's safe", { 0,0,0,0 }, nullptr), true,
		"./assets/orange.png"
	);
	randomD4 = decisionFactory(
		"Our lamps and water sprinklers aren't working\n properly, we need more electricity!",
		connectionFactory("Divert more power to farms and greenhouses!", { 15,0,0,-20 }, nullptr),
		connectionFactory("Sorry, we cannot risk losing stability…", { -20,0,0,0 }, nullptr), true,
		"./assets/yellow.png"
	);
	randomD3 = decisionFactory(
		"Our plants haven't grown yet, we need a special fertilizer. ",
		connectionFactory("For sure, let's buy it", { 15,0,-15,0 }, nullptr),
		connectionFactory("Can't afford it…", { -15,0,0,0 }, nullptr), true,
		"./assets/yellow.png"
	);
	randomD2 = decisionFactory(
		"We need money for the engine \ncheck-up, it was making strange noises recently… ",
		connectionFactory("Yes, better be safe", { 0,0,-20,20 }, nullptr),
		connectionFactory("We can't afford it..", { 0,0,0,-20 }, nullptr), true,
		"./assets/blue.png"
	);
	randomD1 = decisionFactory(
		"People are rioting and demanding\n stress relieving. Let's throw a party!",
		connectionFactory("Yeah, let's do it!", { -10,30,-10,0 }, nullptr),
		connectionFactory("We are short on food…", { 0,-20,0,0 }, nullptr), true,
		"./assets/pink.png"
	);
	decisions.push_back(randomD1);
	decisions.push_back(randomD2);
	decisions.push_back(randomD3);
	decisions.push_back(randomD4);
	decisions.push_back(randomD5);
	decisions.push_back(randomD6);
	decisions.push_back(randomD7);
	decisions.push_back(randomD8);
	decisions.push_back(randomD9);
	decisions.push_back(randomD10);
	decisions.push_back(randomD11);

	// Drzewo decyzji (event):
	/*std::shared_ptr<Decision> u1 = decisionFactory(
		"My King...", 
		connectionFactory(
			"Yes?", {-4, -4, -4, -4},
			decisionFactory(
				"Please help me.\nI'm dying!!!", 
				connectionFactory("Of course", {-4, -4, -4, -4}, nullptr),
				connectionFactory("Die already!!!", {-4, -4, -4, -4}, nullptr)
				)),
		connectionFactory("Hello", {-4, -4, -4, -4}, nullptr),
		"./assets/purple.png"
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
	decisions.push_back(u2);*/
	return decisions;
}

void game(MyRenderWindow& window, gameFlag whetherToLoad) {
	std::shared_ptr<Decision> tutorialD1;
	std::shared_ptr<Decision> tutorialD2;
	std::shared_ptr<Decision> tutorialD3;
	std::shared_ptr<Decision> beginD1;
	std::shared_ptr<Decision> beginD2;
	std::shared_ptr<Decision> beginD3;
	std::shared_ptr<Decision> beginD4;
	std::shared_ptr<Decision> beginD5;
	std::shared_ptr<Decision> beginD6;
	std::shared_ptr<Decision> beginD7;
	std::shared_ptr<Decision> beginD8;
	std::shared_ptr<Decision> beginD9;
	beginD9 = decisionFactory(
		"Our mission is to explore the moon\n and survive at the orbit until backup\n arrives and we will make sure\n we can make a colony here.\n Good luck with the management!",
		connectionFactory("Ok, let's get to work!", { 0, 0, 0, 0 }, nullptr),
		connectionFactory("I have mixed feelings about that...", { 0, 0, 0, 0 }, nullptr), true
		, "./assets/captainRed300x300.png"
	);
	beginD8 = decisionFactory(
		"I am the Minister of Society Pink, I will\n report to you about the crew's \nmorale and living conditions.",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD9),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD9), true
		, "./assets/pink.png"
	);
	beginD7 = decisionFactory(
		"I am IT Specialist Orange, software\n is my field, keeping you updated\n with the newest technologies.",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD8),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD8), true
		, "./assets/orange.png"
	);
	beginD6 = decisionFactory(
		"I am Mechanic Blue,\n keeping the ship running and\n in good condition.",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD7),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD7), true
		, "./assets/blue.png"
	);
	beginD5 = decisionFactory(
		"I am Farmer Yellow,\n I am the caretaker of the greenhouses,\n crops are my specialty.",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD6),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD6), true
		, "./assets/yellow.png"
	);
	beginD4 = decisionFactory(
		"I am Doctor Purple,\n I am the person responsible for\n the healthcare aboard.",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD5),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD5), true
		, "./assets/purple.png"
	);
	beginD3 = decisionFactory(
		"I am General Green, I will\n be informing you about the\n status of the expedition .",
		connectionFactory("Hi!", { 0, 0, 0, 0 }, beginD4),
		connectionFactory("Ok, thank you", { 0, 0, 0, 0 }, beginD4), true
		, "./assets/green.png"
	);
	beginD2 = decisionFactory(
		"Captain, we have arrived at \nthe destination. Would you like\n to do a roll call?",
		connectionFactory("Yes, let's do a rollcall", { 0, 0, 0, 0 }, beginD3),
		connectionFactory("No, let's go on with the mission overview", { 0, 0, 0, 0 }, beginD9), true
		, "./assets/captainRed300x300.png"
	);
	beginD1 = decisionFactory(
		" You finally arrive at\n the moon. You decide\n to take a walk on the surface",
		connectionFactory("Let's go!", { 0, 0, 0, 0 }, beginD2),
		connectionFactory("I am kind of seasick..", { 0, 0, 0, 0 }, beginD2), true
		, "./assets/background.png"
	);
	tutorialD3 = decisionFactory(
		"Do not drop any of\n the resources to 0.",
		connectionFactory("It won't end well...", {50 , 50, 50, 50 }, beginD1),
		connectionFactory("...for you and the crew.", { 50, 50, 50, 50 }, beginD1), true
		, "./assets/black.png"
	);
	tutorialD2 = decisionFactory(
		"You have to balance\n your 4 resources: Plants\n and Food, People and Morale,\n Money and Ship's State.",
		connectionFactory("Your decisions influence the resources.", { -100, -100, -100, -100 }, tutorialD3),
		connectionFactory("Your decisions influence the resources.", { -100, -100, -100, -100 }, tutorialD3), true
		, "./assets/black.png"
	);
	tutorialD1 = decisionFactory(
		"Welcome to Project:\n Europa! Swipe left or right\n to pick an answer",
		connectionFactory("Release the card now to pick this answer", { 100, 100, 100, 100 }, tutorialD2),
		connectionFactory("Release the card now to pick this answer", { 100, 100, 100, 100 }, tutorialD2), true
		, "./assets/black.png"
	);
	



	std::shared_ptr<Decision> current = tutorialD1;
	/*resChecks = decisionFactory(
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
	);*/
	std::vector<std::shared_ptr<Decision>> decisions = allTheDecisions();
	/*std::vector<std::shared_ptr<Decision>> checks = {resChecks};*/
	Game game(current, decisions, whetherToLoad);
	//Game game(whetherToLoad, resChecks, checks);
	//debug
	

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

		game.updateNotifiers();
		
		//fade.animate((fadeRange[1] / 2.0) + (fadeRange[1] / 2.0) * std::sin(t));
		window.clear();
		window.draw(game);
		if (game.getSideNotifier() == -1) {
			window.draw((game.getArea()->getChoiceText(false)));
		}
		if (game.getSideNotifier() == 1) {
			window.draw((game.getArea()->getChoiceText(true)));
		}
		//window.draw(toCompare);
		//window.draw(fade);
		window.display();
		t += 0.05;
	}
}

void menu(MyRenderWindow& window, IsIn& state) {
	sf::Vector2f centerPoint(window.getSize().x / 2.0, window.getSize().y / 2.0);

	sf::Sprite start;
	sf::Sprite new_game;
	sf::Sprite exit;

	//sf::Music music;
	//music.openFromFile("./assets/ProjectEuropa-menu-Song.wav");
	//
	//sf::SoundBuffer buffer;
	//sf::Sound buttonClickSound;
	//buffer.loadFromFile("./assets/button-click.wav");
	//buttonClickSound.setBuffer(buffer);

	sf::Texture texture1, texture2, texture3;

	texture1.loadFromFile("./assets/continue-button.png");
	texture2.loadFromFile("./assets/start-button.png");
	texture3.loadFromFile("./assets/exit-button.png");

	start.setTexture(texture1);
	new_game.setTexture(texture2);
	exit.setTexture(texture3);

	start.setPosition(centerPoint.x-(start.getLocalBounds().width /2.0), 300.0);
	new_game.setPosition(centerPoint.x-(new_game.getLocalBounds().width /2.0), 400.0);
	exit.setPosition(centerPoint.x-(exit.getLocalBounds().width /2.0), 650.0);

	while (window.isOpen()) {
		//music.play();
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
						state = IsIn::gameL;
					}
					if (new_game.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						state = IsIn::game;
					}
					if (exit.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
					{
						state = IsIn::exit;
					}
				}
			}
			}
		}
		if (state != IsIn::menu)
			break;
		window.clear();

		sf::Texture BGtexture;
		BGtexture.loadFromFile("./assets/background.png");
		sf::Sprite background;
		sf::Vector2u size = BGtexture.getSize();
		background.setTexture(BGtexture);

		window.draw(background);
		//window.clear(sf::Color{ 48, 42, 39, 255 }); <- kolor t³a
		window.draw(start);
		window.draw(new_game);
		window.draw(exit);
		window.display();
	}
}


void working() {
	systemFont.loadFromFile("../Sansation_Regular.ttf");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	MyRenderWindow window(sf::VideoMode((int)screenSize.x, (int)screenSize.y), "Project: Europa", settings);
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
			game(window, gameFlag::New);
			break;
		};
		case IsIn::gameL: {
			game(window, gameFlag::Load);
			break;
		};
		case IsIn::exit: {
			window.close();
		}
		case IsIn::menu: {
			menu(window, state);
			break;
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
	std::cout << "Project: Europa (cmd)" << std::endl;
		working();	
	return 1;
}
