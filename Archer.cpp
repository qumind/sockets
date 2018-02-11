#include "Archer.h"



Archer::Archer(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic)
	: Fighter(_name, _maximumHP, _strength, _speed, _magic), current_speed(_speed), bonus(false)
{
}


Archer::~Archer()
{
}

int Archer::getDamage()
{
	return speed;
}

void Archer::reset()
{
	currentHP = maximumHP;
	current_speed = speed;
	bonus = true;
}

void Archer::regenerate()
{
	double increase = strength / 6;
	if (increase < 1)
		increase = 1;
	if ((currentHP + increase) <= maximumHP)
		currentHP += increase;
	else
		currentHP = maximumHP;
}

bool Archer::useAbility()
{
	if (bonus)
	{
		speed++;
		return true;
	}
	return false;
}