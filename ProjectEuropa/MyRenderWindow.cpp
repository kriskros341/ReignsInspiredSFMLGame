#include "./MyRenderWindow.h"


void MyRenderWindow::draw(Game& game) {
	sf::RenderWindow::draw(game.area);
	sf::RenderWindow::draw(game.area.yesZone);
	sf::RenderWindow::draw(game.area.noZone);
	sf::RenderWindow::draw(game.area.gui);
	sf::RenderWindow::draw(game.area.next);
	sf::RenderWindow::draw(game.area.card);
	draw(game.area.gui.resources, game.area.gui.resourceCount);
}
void MyRenderWindow::draw(Resource* r, const int c) {
	for (int i = 0; i < c; i++) {
		draw(r[i]);
	};
}
void MyRenderWindow::draw(Resource r) {
	sf::RenderWindow::draw(r);
	sf::RenderWindow::draw(r.t);
}
void MyRenderWindow::draw(FadeIn f) {
	sf::RenderWindow::draw(*f.getUnderlyingPointer());
}
void MyRenderWindow::draw(sf::Shape& f) {
	sf::RenderWindow::draw(f);
}
void MyRenderWindow::draw(TextField& f) {
	sf::RenderWindow::draw(f);
	sf::RenderWindow::draw(f.text);
}
void MyRenderWindow::draw(DecisionBox& db) {
	sf::RenderWindow::draw(db);
	sf::RenderWindow::draw(db.yesFrom);
	sf::RenderWindow::draw(db.noFrom);
	sf::RenderWindow::draw(db.socket);
	if (db.yesFrom.getConnected()) {
		sf::RenderWindow::draw(db.yesFrom.line);
	}
	if (db.noFrom.getConnected()) {
		sf::RenderWindow::draw(db.noFrom.line);
	}
};
