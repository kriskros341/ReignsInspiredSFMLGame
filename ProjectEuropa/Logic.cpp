#include "Logic.h"
#include <string>
#include <iostream>
class Decision;
DecisionConnector::DecisionConnector(std::string t, const int c[4], Decision* n) {
	text = t;
	for (int i = 0; i < 4; i++) {
		change[i] = c[i];
	}
	next = n;
};
std::string DecisionConnector::getConnectorText() {
	return text;
};
int DecisionConnector::getChangeParameter(int a) { 
	if (a > -1 && a < 4)
		return change[a];
	else std::cout << "Error 1: wrong index choice while getting change values in DecisionConnector" << std::endl;
};
Decision* DecisionConnector::getNextDecision() {
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
Decision::Decision(std::string t) {
	text = t;
};
Decision::Decision(std::string s, DecisionConnector* y=nullptr, DecisionConnector* n=nullptr) {
	setID();
	text = s;
	yes = y;
	no = n;
}
void Decision::setID() {
	static int ID = 0;
		id = ++ID;
}
void Decision::setText(std::string s) {
	text = s;
}
void Decision::setYes(std::string t, const int c[4], Decision* d ) {
	yes = new DecisionConnector(t, c, d);
};
void Decision::setNo(std::string t, const int c[4], Decision* d ) {
	no = new DecisionConnector(t, c, d);
};
int Decision::getID() { return id; };
std::string Decision::getText() { return text; };
DecisionConnector* Decision::getYesDecision() { return yes; };
DecisionConnector* Decision::getNoDecision() { return no; };
Decision::~Decision() {
	delete yes;
	delete no;
}




