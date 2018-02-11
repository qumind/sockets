#pragma once
#include "Fighter.h"
class Robot : public Fighter
{
public:
	Robot(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic);
	~Robot();
	void reset();
	bool useAbility();
	int getDamage();
	void regenerate();
private:
	int current_energy;
	int maximum_energy;
	int bonus_damage;
};

