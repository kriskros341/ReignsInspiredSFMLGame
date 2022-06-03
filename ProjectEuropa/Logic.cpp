#include "Logic.h"
#include <string>
#include <iostream>
class Decision;
/*
DecisionConnector::DecisionConnector(std::string t, const int c[4], Decision* n) {
	text = t;
	for (int i = 0; i < 4; i++) {
		change[i] = c[i];
	}
	next = n;
};
*/

std::string DecisionConnector::getConnectorText() {
	return text;
};
int DecisionConnector::getChangeParameter(int a) { 
	if (a > -1 && a < 4)
		return change[a];
	else std::cout << "Error 1: wrong index choice while getting change values in DecisionConnector" << std::endl;
};
std::shared_ptr<Decision> DecisionConnector::getNextDecision() {
	return next;
};
void DecisionConnector::setConnectorText(std::string s) {
	text = s;
};
void DecisionConnector::setChangeParameter(int index, int number) {
	if (index > -1 && index < 4)
		change[index]=number;
	else std::cout << "Error 2: wrong index choice while setting change values in DecisionConnector" << std::endl;
};
/*
Decision::Decision(std::string t) {
	text = t;
};

Decision::Decision(std::string s, DecisionConnector* y=nullptr, DecisionConnector* n=nullptr) {
	setID();
	text = s;
	yes = std::make_unique<DecisionConnector>(*y);
	no = std::make_unique<DecisionConnector>(*n);
}
*/


Decision::Decision(const std::string& s, std::shared_ptr<DecisionConnector> y, std::shared_ptr<DecisionConnector> n) {
	text = s;
	yes = y;
	no = n;
};


void Decision::setID() {
	static int ID = 0;
		id = ++ID;
}
void Decision::setText(std::string s) {
	text = s;
}
/*
void Decision::setYes(std::string t, const int c[4], std::shared_ptr<Decision> d ) {
	yes = std::make_shared<DecisionConnector>(t, c, d);
};
void Decision::setNo(std::string t, const int c[4], std::shared_ptr<Decision> d ) {
	no = std::make_shared<DecisionConnector>(t, c, d);
};
*/
int Decision::getID() { return id; };
std::string Decision::getText() { return text; };
std::shared_ptr<DecisionConnector>& Decision::getYesDecision() { return yes; };
std::shared_ptr<DecisionConnector>& Decision::getNoDecision() { return no; };
Decision::~Decision() {
}


std::shared_ptr<Decision> decisionFactory(
	const std::string& text,
	std::shared_ptr<DecisionConnector> c1,
	std::shared_ptr<DecisionConnector> c2
) {
	std::shared_ptr<Decision> result = std::make_shared<Decision>(text, c1, c2);
	return result;
}

std::shared_ptr<DecisionConnector> connectionFactory(
	const std::string& text,
	const DecisionStats stats,
	const std::shared_ptr<Decision>& nextDecision
) {
	std::shared_ptr<DecisionConnector> result = 
		std::make_shared<DecisionConnector>(text, stats, nextDecision);
	return result;
}

