#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Decision.h"
#include "./MyRenderWindow.h"
#include "./Game.h"
#include "./Animation.h"
#pragma setLocale("utf-8")

extern sf::Vector2f screenSize;
enum class IsIn {
	menu = 1,
	editor,
	game
};

/*
	How do I select one of the node connectors and connect it with another:
		I pick a connector
			I check if click is on connector
*/
void editor(MyRenderWindow& window, IsIn& state) {

	sf::RectangleShape start({ 100, 100 });
	start.setFillColor(sf::Color::Red);
	DecisionConnector* selectedConnector = 0;
	DecisionBox db;
	DecisionBox db2({600, 400});
	

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					state = IsIn::menu;
				}
			}
			case sf::Event::MouseButtonReleased: {
				if (event.key.code == sf::Mouse::Left) {
					if (start.getLocalBounds().contains(sf::Vector2f(mousePosition)))
					{
						state = IsIn::menu;
					}

					if (db.yesFrom.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
						db.yesFrom.setSelected(true);
						if (!selectedConnector) {
							selectedConnector = &db.yesFrom;
						}
					}
					else {
						db.yesFrom.setSelected(false);
					}
					if (db2.socket.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
						if (selectedConnector) {
							selectedConnector->setConnection(db2);
						}
					}

				}
			}
			}
		}
		if (state != IsIn::editor)
			break;
		window.clear();
		window.draw(start);
		window.draw(db);
		window.draw(db2);
		window.display();
	}
}

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
	
	sf::RectangleShape start({ 400, 200 });
	sf::RectangleShape editor({ 400, 200 });
	editor.setFillColor(sf::Color::Red);
	editor.setPosition({ 0, 200 });
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
					if (editor.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
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
		window.draw(editor);
		window.display();
	}
}



int main() {
	systemFont.loadFromFile("C:/Users/TrybSkupienia/Desktop/theGame/ProjectEuropa/ProjectEuropa/x64/Debug/Arial.ttf");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	MyRenderWindow window(sf::VideoMode((int)screenSize.x, (int)screenSize.y), "g", settings);
	window.setFramerateLimit(60);
	IsIn state = IsIn::editor;

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
		case IsIn::editor: {
			editor(window,  state);
		}
		}

	}
	return 1;
}
