#include <iostream>
#include "./Animation.h"

float approx_linear(float input[2], float output[2], float value) {
	float inputRange = input[0] - output[0];
	float outputRange = input[1] - output[1];
	float slope = (output[1] - output[0]) / (input[1] - input[0]);
	return output[0] + slope * (value);
}


void FadeIn::applyAnimation(float value) {
	sf::Color fill = object->getFillColor();
	float outputAlpha[2] = { 1, 255 };
	fill.a = 255 - approx_linear(internalRange, outputAlpha, value);
	std::cout << (int)fill.a << std::endl;
	object->setFillColor(fill);
	object->setPosition(startingPosition.x, startingPosition.y + value);
}

void FadeIn::animate(float value) {
	if (value > externalRange[1]) {
		std::cout << value << " " << approx_linear(externalRange, internalRange, internalRange[1]) << std::endl;
		applyAnimation(internalRange[1]);
	}
	else if (value < externalRange[0]) {
		std::cout << value << " " << approx_linear(externalRange, internalRange, internalRange[0]) << std::endl;
		applyAnimation(internalRange[0]);
	}
	else {
		std::cout << value << " " << approx_linear(externalRange, internalRange, value) << std::endl;
		//std::cout << approx_linear(externalRange, internalRange, value) << std::endl;
		applyAnimation(approx_linear(externalRange, internalRange, value));
	}
}

sf::Shape* FadeIn::getUnderlyingPointer() {
	return object;
}
