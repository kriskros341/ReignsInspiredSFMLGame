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
enum class IsIn;
//-----------KLASA RENDERUJ¥CA WSZYSTKIE ELEMENTY POJAWIAJ¥CE SIÊ NA EKRANIE-------
class MyRenderWindow : public sf::RenderWindow {
public:
	MyRenderWindow(sf::VideoMode v, std::string t, sf::ContextSettings& c) : 
		sf::RenderWindow(v, t, sf::Style::Close, c) {
	};
	void drawIndicators(Resource* r, const int c, std::shared_ptr<Decision> d, bool left);
	void draw(Game& game);
	IsIn stateFlag;
	void draw(Resource* r, const int c);
	void draw(Resource r);
	void draw(FadeIn f);
	void draw(sf::Shape& f);
	void draw(sf::Text* t);
	void draw(sf::Sprite& s);
};
