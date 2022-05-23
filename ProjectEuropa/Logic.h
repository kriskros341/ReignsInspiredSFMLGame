#pragma once
#include <string>
#include <SFML/Graphics.hpp>


class DecisionConnector;

class DecisionStats {
	
	int a, b, c, d;
	friend class DecisionConnector;
public:
	DecisionStats(int i = 0, int j = 0, int k = 0, int l = 0) {
		a = i;
		b = j;
		c = k;
		d = l;
	}
	DecisionStats(const int s[]) {
		a = s[0];
		b = s[1];
		c = s[2];
		d = s[3];
	}

};

class DecisionStats;
class Decision;
class DecisionConnector {
	std::string text = "defaultTransition";
	std::shared_ptr<Decision> next = nullptr;
	int change[4] = { 0,0,0,0 };
public:
	//DecisionConnector(std::string t, const int c[4], Decision* n);
	
	DecisionConnector(std::string t, DecisionStats stats, const std::shared_ptr<Decision> n) {
		text = t;
		change[0] = stats.a;
		change[1] = stats.a;
		change[2] = stats.a;
		change[3] = stats.a;
		next = std::move(n);
	};
	std::string getConnectorText();
	int getChangeParameter(int a);
	std::shared_ptr<Decision> getNextDecision();
	void setConnectorText(std::string s);
	void setChangeParameter(int index, int number); 
	void setNextDecision(Decision* nex);
};

std::shared_ptr<DecisionConnector> connectionFactory(
	const std::string& text,
	const DecisionStats stats,
	const std::shared_ptr<Decision> nextDecision
);

class Decision {
private:
	int id = -1;
	std::string text = "default";
	std::shared_ptr<DecisionConnector> yes;
	std::shared_ptr<DecisionConnector> no;
	friend std::shared_ptr<Decision> decisionFactory(
		const std::string& text,
		std::shared_ptr<DecisionConnector>& c1,
		std::shared_ptr<DecisionConnector>& c2
	);
public:
	//Decision(const std::string& t="defau");
	//Decision(std::string s, DecisionConnector* y, DecisionConnector* n);
	Decision(const std::string& s, std::shared_ptr<DecisionConnector> y, std::shared_ptr<DecisionConnector> n);
	Decision(const Decision& d) {
		text = d.text;
		yes = d.yes;
		no = d.no;
	}
	void setID();
	void setText(std::string s);
	void setYes(std::string t, const int c[4], std::shared_ptr<Decision>& d );
	void setNo(std::string t, const int c[4], std::shared_ptr<Decision>& d );
	int getID();
	std::string getText();
	std::shared_ptr<DecisionConnector>& getYesDecision();
	std::shared_ptr<DecisionConnector>& getNoDecision();
	~Decision();
};

std::shared_ptr<Decision> decisionFactory(
	const std::string& text,
	std::shared_ptr<DecisionConnector> c1,
	std::shared_ptr<DecisionConnector> c2
);


