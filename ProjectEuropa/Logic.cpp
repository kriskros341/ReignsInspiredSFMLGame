#include "Logic.h"
#include <iostream>

class Decision;

Decision::Decision(std::string t) {
	text = t;
};
DecisionConnector::DecisionConnector(std::string t, const int c[4], Decision* n) {
	text = t;
	for (int i = 0; i < 4; i++) {
		change[i] = c[i];
	}
	next = n;
};
Decision* DecisionConnector::getNextDecision() {
	return next;
};
void Decision::setYes(std::string t, const int c[4], Decision* d ) {
	yes = new DecisionConnector(t, c, d);
};
void Decision::setNo(std::string t, const int c[4], Decision* d ) {
	no = new DecisionConnector(t, c, d);
};
//DecisionConnector::DecisionConnector(std::string t, const int c[4], Decision* n) {
//	text = t;
//	change = c;
//	next = n;
//};


int Decision::getID() { return id; };
std::string Decision::getText() { return text; };
DecisionConnector* Decision::getYesDecision() { return yes; };
DecisionConnector* Decision::getNoDecision() { return no; };
std::string DecisionConnector::getConnectorText() { return text; };
int DecisionConnector::getChangeParameter(int a) { 
	switch (a) {
	case 0:
		return change[0];
		break;
	case 1:
		return change[1];
		break;
	case 2:
		return change[2];
		break;
	case 3:
		return change[3];
		break;
	default:
		std::cout << "wrong index" << std::endl;
		break;
	}
};





