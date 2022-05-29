#include "Game.h"
#include "Logic.h"
#define PI std::acos(-1);

float getAngleBetween(sf::Vector2f origin, sf::Vector2f theOther) {
	sf::Vector2f diff = origin - theOther;
	return (float)std::atan2f(diff.x, diff.y) * 180 / PI;
};

bool MainCard::getDragging() {
	return isDragging;
}
void MainCard::dragHorizontally(sf::Vector2f position) {
	sf::Vector2f startingPosition = getPosition();
	float angle = getAngleBetween(position, { screenSize.x / 2.0f, screenSize.y * 3 });
	setRotation(-angle);
	setPosition(position.x, startingPosition.y);
}
void MainCard::restartDrag() {
	setRotation(0);
	setPosition({ starting.top - 100.0f, starting.left + 100.0f });
}
void MainCard::setDragging(bool n) {
	isDragging = n;
}


bool Game::doesIntersectWithMainCard(sf::FloatRect position) {
	sf::FloatRect cardPosition = area.card.getGlobalBounds();
	return cardPosition.intersects(position);

}
bool Game::doesIntersectWithMainCard(sf::Vector2f position) {
	sf::FloatRect cardPosition = area.card.getGlobalBounds();
	return cardPosition.contains(position);
}
void Game::setDragging(bool n) {
	area.card.setDragging(n);
}
void Game::restartDrag() {
	area.card.restartDrag();
}
bool Game::getDragging() {
	return area.card.getDragging();
}

void Game::dragCard(sf::Vector2f position) {
	area.card.dragHorizontally(position);
}
void Game::makeChoice() {
	if (doesIntersectWithMainCard(area.yesZone.getGlobalBounds()))
	{
		area.makeDecision(true);
		std::cout << "YES" << std::endl;
	}
	if (doesIntersectWithMainCard(area.noZone.getGlobalBounds()))
	{
		area.makeDecision(false);
		std::cout << "NO" << std::endl;
	}
	setDragging(false);
	restartDrag();
}
