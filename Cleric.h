#pragma once
#include "Fighter.h"
class Cleric : public Fighter
{
public:
	Cleric(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic);
	~Cleric();
	void regenerate();
	void reset();
	int getDamage();
	bool useAbility();
private:
	int currentMana;
	int maximumMana;
};

