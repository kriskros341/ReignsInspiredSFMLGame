#include "./Designer.h"
void TextField::setFocused(bool g) {
	isFocused = g;
}
bool TextField::getFocused() {
	return isFocused;
}

void TextField::handleEvent(sf::Event event) {
	switch(event.type) {

	case sf::Event::KeyPressed: {
		if(event.key.code == sf::Keyboard::Backspace && isFocused ) {
			std::cout << "BSP" << std::endl;
			std::cout << (int)'0' << (int)'1' << std::endl;
			if (playerInput.size() == 0) {
				return;
			}
			playerInput.pop_back();
			text.setString(playerInput);
		}
		break;
	}
	case sf::Event::TextEntered: {
		std::cout << event.text.unicode << std::endl;
		if (event.text.unicode >= 48 && event.text.unicode < 58) {
			if (isFocused) {
				playerInput += event.text.unicode;
				text.setString(playerInput);
			}
			}
	}
	
	}
}
