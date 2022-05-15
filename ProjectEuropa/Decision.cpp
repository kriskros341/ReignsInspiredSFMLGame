#include "./Decision.h"
#include <iostream>

class Decision {
	Decision* yes = nullptr;
	Decision* no = nullptr;
	std::string yesText;
	std::string noText;
	int changeYes[4];
	int changeNo[4];
};



