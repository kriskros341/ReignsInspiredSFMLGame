#include "./Decision.h"
#include <iostream>

int getNextId() {
	static int id = 0;
	return (id = id + 1);
}

bool Connector::getConnected() {
	return connected;
}

void Connector::setConnected(bool c) {
	connected = c;
}

void DecisionConnector::setSelected(bool s) {
	selected = s;
	updateOutline();
}

bool DecisionConnector::getSelected() {
	return selected;
}

void DecisionConnector::updateOutline() {
	setOutlineThickness(selected ? 2 : 0);
}

void DecisionConnector::onSelect() {
	setSelected(!getSelected());
	updateOutline();
}

void DecisionConnector::setConnection(DecisionBox& b) {
	std::cout << line.getVertexCount() << std::endl;
	if (!getConnected() && !b.socket.getConnected()) {
		line[0] = getPosition();
		line[0].color = isYes ? sf::Color::Green : sf::Color::Red;
		line[1] = b.socket.getPosition();
		std::cout << line.getVertexCount() << std::endl;
		target = &b.socket;
		b.socket.setConnected(true);
		setConnected(true);
	}
}

void DecisionBox::updateOutline() {
	setOutlineThickness(selected ? 5 : 0);
}

void DecisionBox::toggleSelected() {
	selected = !selected;
	updateOutline();
}

void DecisionBox::setSelected(bool k) {
	selected = k;
	updateOutline();
}

bool DecisionBox::getSelected() {
	return selected;
}

bool DecisionBox::checkForClick(sf::Vector2i mousePosition) {
	if(yesFrom.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
		setSelected(false);
		noFrom.setSelected(false);
		yesFrom.setSelected(true);
		return true;
	}
	else {
		yesFrom.setSelected(false);
	}
	if (noFrom.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
		setSelected(false);
		yesFrom.setSelected(false);
		noFrom.setSelected(true);
		return true;
	}
	else {
		noFrom.setSelected(false);
	}
	if (getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
		setSelected(true);
		return true;
	}
	else {
		setSelected(false);
	}
	return false;


}

