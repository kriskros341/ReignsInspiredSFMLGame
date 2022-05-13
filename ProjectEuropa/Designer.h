#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>

extern sf::Font systemFont;
extern sf::Vector2f screenSize;

class TextField : public sf::RectangleShape {
	sf::Text text;
	sf::Vector2f minimal;
	sf::Vector2f position;
	friend class MyRenderWindow;
	std::string playerInput;
	bool isFocused = false;
public:
	TextField(sf::FloatRect pos) : sf::RectangleShape({ pos.width, pos.height }) {
		text.setFont(systemFont);
		position = { pos.left, pos.top };
		setPosition(position);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(11);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(position.x + 4, position.y + 4);
	}
	void setFocused(bool g);
	bool getFocused();
	void handleEvent(sf::Event event);

};
