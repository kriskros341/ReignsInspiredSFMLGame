#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Decision;
class DecisionConnector {
	std::string text = "defaultTransition";
	Decision* next = nullptr;
	int change[4] = { 0,0,0,0 };
public:
	DecisionConnector(std::string t, const int c[4], Decision* n);
	std::string getConnectorText();
	int getChangeParameter(int a);
	Decision* getNextDecision();
};

class Decision {
private:
	int id = -1;
	std::string text = "default";
	DecisionConnector* yes = nullptr;
	DecisionConnector* no = nullptr;
public:
	
	Decision(std::string t="defau");
	/*void setYes(Decision* other);
	void setNo(Decision* other);*/
	void setYes(std::string t, const int c[4], Decision* d );
	void setNo(std::string t, const int c[4], Decision* d );


	int getID();
	std::string getText();
	DecisionConnector* getYesDecision();
	DecisionConnector* getNoDecision();

	~Decision() {
		delete yes;
		delete no;
	}
};

