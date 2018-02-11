#pragma once
#include "Fighter.h"
class Archer : public Fighter
{
public:
	Archer(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic);
	~Archer();
	int getDamage();
	void reset();
	void regenerate();
	bool useAbility();
private:
	int current_speed;
	bool bonus;
};

