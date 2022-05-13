#pragma once
#include <SFML/Graphics.hpp>


float approx_linear(float input[2], float output[2], float value);

class FadeIn {
	sf::Shape* object;
	sf::Vector2f startingPosition;
	int side;
	float externalRange[2];
	float internalRange[2] = { 0, 25 };
public:
	FadeIn(sf::Shape* o, int s, float range1[2]) {
		object = o;
		side = s;
		startingPosition = o->getPosition();
		for (int i{}; i < 2; i++) {
			externalRange[i] = range1[i];
		}
		//Horizontal from up;
		o->setPosition(o->getPosition().x, o->getPosition().y + internalRange[1]);
	}

	void applyAnimation(float value);
	void animate(float value);
	sf::Shape* getUnderlyingPointer();
};
