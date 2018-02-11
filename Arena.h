#pragma once
#include <sstream>
#include "ArenaInterface.h"
#include "Archer.h"
#include "Cleric.h"
#include "Robot.h"

class Arena: public ArenaInterface
{
public:
	Arena();
	~Arena();

	FighterInterface* getFighter(std::string name);
	bool addFighter(std::string info);
	bool removeFighter(std::string name);
	int getSize() const;

private:
	std::vector<FighterInterface *> fighters;
};
