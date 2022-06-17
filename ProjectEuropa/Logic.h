#pragma once
#include <string>
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>


class DecisionConnector;

class DecisionStats {
	
	friend class DecisionConnector;
public:
	//this should ve been an array all along
	std::array<int, 4> stats = {0, 0, 0, 0};
	DecisionStats(int i = 0, int j = 0, int k = 0, int l = 0) {
		stats[0] = i;
		stats[1] = j;
		stats[2] = k;
		stats[3] = l;
		cout();
	}
	void cout() {
		for (const auto& c : stats) {
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
	int& operator [](const int i) {
		return stats[i];
	}
	void apply(DecisionStats other) {
		for (int i = 0; i < 4; i++) {
			stats[i] += other.stats[i];
			if (stats[i] > 100)
				stats[i] = 100;
		}
	}

};

class DecisionStats;
class Decision;
class DecisionConnector {
	std::string text = "defaultTransition";
	std::shared_ptr<Decision> next = nullptr;
	DecisionStats change;
	public:
	//DecisionConnector(std::string t, const int c[4], Decision* n);
	
	DecisionConnector(std::string t, DecisionStats stats, const std::shared_ptr<Decision>& n) {
		text = t;
		change = stats;
		next = std::move(n);
	};
	std::string getConnectorText();
	int getChangeParameter(int a);
	DecisionStats getChangeParameters() {
		return change;
	};
	std::shared_ptr<Decision> getNextDecision();
	void setConnectorText(std::string s);
	void setChangeParameter(int index, int number); 
	void setNextDecision(Decision* nex);
};

std::shared_ptr<DecisionConnector> connectionFactory(
	const std::string& text,
	const DecisionStats stats,
	const std::shared_ptr<Decision>& nextDecision
);

const std::string defaultImage = "./assets/captainRed300x300.png";
class Decision {
private:

	int id = -1;
	std::string text = "default";
	bool wasUsed = false;
	bool tobeUsed;
	std::shared_ptr<DecisionConnector> yes;
	std::shared_ptr<DecisionConnector> no;
	std::string imagePath;
	friend std::shared_ptr<Decision> decisionFactory(
		const std::string& text,
		std::shared_ptr<DecisionConnector>& c1,
		std::shared_ptr<DecisionConnector>& c2
	);
public:
	//Decision(const std::string& t="defau");
	//Decision(std::string s, DecisionConnector* y, DecisionConnector* n);
	Decision(const std::string& s, std::shared_ptr<DecisionConnector> y, std::shared_ptr<DecisionConnector> n, bool toBeRolled = true, std::string path = defaultImage);
	Decision(const Decision& d) {
		text = d.text;
		yes = d.yes;
		no = d.no;
		imagePath = d.imagePath;
		tobeUsed = d.tobeUsed;
	}
	std::string getImagePath() {
		return imagePath;
	}
	void setID();
	bool getToBeUsed()
	{
		return tobeUsed;
	};
	void setToBeUsed(bool b) { tobeUsed = b; };
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
	std::shared_ptr<DecisionConnector> c2,
	bool isRolled,
	std::string imagePath = defaultImage
);


