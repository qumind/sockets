#include "Fighter.h"



Fighter::Fighter(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic)
	:  name(_name), maximumHP(_maximumHP), currentHP(_maximumHP), strength(_strength),
	speed(_speed), magic(_magic)

{
}


Fighter::~Fighter()
{
}

std::string Fighter::getName() const
{
	return name;
}

int Fighter::getMaximumHP() const
{
	return maximumHP;
}

int Fighter::getCurrentHP() const
{
	return currentHP;
}

int Fighter::getStrength() const
{
	return strength;
}

int Fighter::getSpeed() const
{
	return speed;
}

int Fighter::getMagic() const
{
	return magic;
}

int Fighter::getDamage()
{
	return 1;
}

void Fighter::takeDamage(int damage)
{
	int input_damage;
	int decrease = damage - speed / 4;
	if (decrease > 1)
		input_damage = decrease;
	else
		input_damage = 1;
	currentHP -= input_damage;
}
