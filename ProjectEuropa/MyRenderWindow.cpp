#include "./MyRenderWindow.h"

//-------------FUNKCJE RYSUJ¥CE ELEMENTY NA EKRANIE-------------

void MyRenderWindow::draw(Game& game) {
	sf::RenderWindow::draw(game.area);
	sf::RenderWindow::draw(game.area.yesZone);
	sf::RenderWindow::draw(game.area.noZone);
	sf::RenderWindow::draw(game.area.gui);
	sf::RenderWindow::draw(game.area.bottomTextZone);
	sf::RenderWindow::draw(game.area.next);
	sf::RenderWindow::draw(game.area.card);
	draw(game.area.gui.resources, game.area.gui.resourceCount);
	sf::RenderWindow::draw(game.area.gui.flora);
	sf::RenderWindow::draw(game.area.gui.human);
	sf::RenderWindow::draw(game.area.gui.money);
	sf::RenderWindow::draw(game.area.gui.rocket);
	sf::RenderWindow::draw(game.area.decisionText);
	sf::RenderWindow::draw(game.area.backButton);
	//drawIndicators(game.area.gui.resources, game.area.gui.resourceCount);
}
void MyRenderWindow::draw(Resource* r, const int c) {
	for (int i = 0; i < c; i++) {
		draw(r[i]);
		draw(r[i].underlayingCover);
	};
}
void MyRenderWindow::drawIndicators(Resource* r, const int c, std::shared_ptr<Decision> d, bool left) {
	for (int i = 0; i < c; i++) {
		
		if (left) {
			int roar = d->getNoDecision()->getChangeParameter(i);
			if (roar == 0) r[i].up.setRadius(0);
			if (abs(roar) > 0 && abs(roar) <= 15) r[i].up.setRadius(2);
			if (abs(roar) > 15) r[i].up.setRadius(5);
		}
		else {
			int roar = d->getYesDecision()->getChangeParameter(i);
			if (roar == 0) r[i].up.setRadius(0);
			if (abs(roar) > 0 && abs(roar) <= 15) r[i].up.setRadius(2);
			if (abs(roar) > 15) r[i].up.setRadius(5);
		}

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