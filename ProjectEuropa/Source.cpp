#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Decision.h"
#include "./MyRenderWindow.h"
#include "./Game.h"
#include "./Animation.h"
#pragma setLocale("utf-8")
#define papiez 2137;

extern sf::Vector2f screenSize;
enum class IsIn {
	menu = 1,
	editor,
	game
};

void game(MyRenderWindow& window) {

	Game game;

	sf::CircleShape toCompare(4, 40);
	toCompare.setPosition(400, 400);
	sf::CircleShape* animationTest = new sf::CircleShape(4, 40);
	animationTest->setPosition(400, 400);
	animationTest->setFillColor(sf::Color::Black);
	float fadeRange[2] = { 0, 10 };
	FadeIn fade(animationTest, 0, fadeRange);

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

		fade.animate((fadeRange[1] / 2.0) + (fadeRange[1] / 2.0) * std::sin(t));
		window.clear();
		window.draw(game);
		window.draw(toCompare);
		window.draw(fade);
		window.display();
		t += 0.05;
	}
}

void menu(MyRenderWindow& window, IsIn& state) {
	sf::Vector2f centerPoint(window.getSize().x / 2.0, window.getSize().y / 2.0);
	sf::RectangleShape start({ 200, 100 });
	sf::RectangleShape options({ 200, 100 });
	sf::RectangleShape exit({ 200,100 });
	start.setPosition(centerPoint.x-(start.getSize().x/2.0), 200.0);
	options.setPosition(centerPoint.x-(options.getSize().x/2.0), 300.0);
	exit.setFillColor(sf::Color::Red);
	exit.setPosition(centerPoint.x-(exit.getSize().x/2.0), 400.0);
	options.setFillColor(sf::Color::Blue);
	sf::Text startText;
	sf::Text optionsText;
	sf::Text exitText;


	startText.setString("Start");
	sf::FloatRect startRect = startText.getLocalBounds();
	startText.setFont(systemFont);

	startText.setPosition(
		start.getPosition().x + start.getSize().x/2.0 - startText.getLocalBounds().width / 2.f, 
		start.getPosition().y + start.getSize().y/2.0 - startText.getLocalBounds().height / 2.f
	);
	startText.setFillColor(sf::Color::Black);

	
	optionsText.setString("Options");
	optionsText.setFont(systemFont);
	optionsText.setPosition(options.getPosition().x+(options.getSize().x/2.0)-optionsText.getLocalBounds().width / 2.f,options.getPosition().y+(options.getSize().y/2.0)-optionsText.getLocalBounds().height / 2.f);
	optionsText.setFillColor(sf::Color::Black);
	exitText.setString("Exit");
	exitText.setFont(systemFont);
	exitText.setPosition(exit.getPosition().x+(exit.getSize().x/2.0)-exitText.getLocalBounds().width / 2.f,exit.getPosition().y+(exit.getSize().y/2.0)-exitText.getLocalBounds().height / 2.f);
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
		window.draw(start);
		window.draw(options);
		window.draw(exit);
		window.draw(startText);
		window.draw(optionsText);
		window.draw(exitText);
		window.display();
	}
}



int main() {
	systemFont.loadFromFile("../Arial.ttf");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	MyRenderWindow window(sf::VideoMode((int)screenSize.x, (int)screenSize.y), "g", settings);
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
	return 1;
}
