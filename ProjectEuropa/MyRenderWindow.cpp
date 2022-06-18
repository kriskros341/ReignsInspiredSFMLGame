#include "./MyRenderWindow.h"


void MyRenderWindow::draw(Game& game) {
	sf::RenderWindow::draw(game.area);
	sf::RenderWindow::draw(game.area.yesZone);
	sf::RenderWindow::draw(game.area.noZone);
	sf::RenderWindow::draw(game.area.gui);
	sf::RenderWindow::draw(game.area.bottomTextZone);
	sf::RenderWindow::draw(game.area.next);
	sf::RenderWindow::draw(game.area.card);
	draw(game.area.gui.resources, game.area.gui.resourceCount);
	sf::RenderWindow::draw(game.area.flora);
	sf::RenderWindow::draw(game.area.human);
	sf::RenderWindow::draw(game.area.money);
	sf::RenderWindow::draw(game.area.rocket);
	sf::RenderWindow::draw(game.area.decisionText);
	sf::RenderWindow::draw(game.area.backButton);
	drawIndicators(game.area.gui.resources, game.area.gui.resourceCount);
}
void MyRenderWindow::draw(Resource* r, const int c) {
	for (int i = 0; i < c; i++) {
		draw(r[i]);
	};
}
void MyRenderWindow::drawIndicators(Resource* r, const int c) {
	for (int i = 0; i < c; i++) {
		draw(r[i].up);
	};
}
void MyRenderWindow::draw(Resource r) {
	sf::RenderWindow::draw(r);
}
void MyRenderWindow::draw(FadeIn f) {
	sf::RenderWindow::draw(*f.getUnderlyingPointer());
}
void MyRenderWindow::draw(sf::Shape& f) {
	sf::RenderWindow::draw(f);
}
void MyRenderWindow::draw(sf::Text* t) {
	sf::RenderWindow::draw(*t);
};
void MyRenderWindow::draw(sf::Sprite& s) {
	sf::RenderWindow::draw(s);
};