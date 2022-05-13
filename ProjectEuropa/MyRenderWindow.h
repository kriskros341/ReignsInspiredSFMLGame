#pragma once
#include "sfml/Graphics.hpp"
#include "./Decision.h"
#include "./Game.h"
#include "./Animation.h"
#include "./Designer.h"

class Game;
class Resource;
class FadeIn;
class TextField;
class Decision;

class MyRenderWindow : public sf::RenderWindow {
public:
	MyRenderWindow(sf::VideoMode v, std::string t, sf::ContextSettings& c) : 
		sf::RenderWindow(v, t, sf::Style::Close, c) {};
	void draw(Game& game);
	void draw(Resource* r, const int c);
	void draw(Resource r);
	void draw(FadeIn f);
	void draw(sf::Shape& f);
	void draw(TextField& f);
	void draw(DecisionBox& db);
};
