#pragma once
#include "sfml/Graphics.hpp"
#include "./Logic.h"
#include "./Game.h"
#include "./Animation.h"

class Game;
class Resource;
class FadeIn;
class TextField;
class Decision;

class MyRenderWindow : public sf::RenderWindow {
public:
	MyRenderWindow(sf::VideoMode v, std::string t, sf::ContextSettings& c) : 
		sf::RenderWindow(v, t, sf::Style::Close, c) {
		clear(sf::Color(200, 0, 0));
	};
	void draw(Game& game);
	void draw(Resource* r, const int c);
	void draw(Resource r);
	void draw(FadeIn f);
	void draw(sf::Shape& f);
	void draw(sf::Text& t);
};
