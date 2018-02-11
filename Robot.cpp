#include "Robot.h"



Robot::Robot(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic)
	: Fighter(_name, _maximumHP, _strength, _speed, _magic), bonus_damage(0),
	maximum_energy(2 * _magic), current_energy(2 * _magic)
{
}


Robot::~Robot()
{
}

void Robot::reset()
{
	currentHP = maximumHP;
	current_energy = maximum_energy;
	bonus_damage = 0;
}

bool Robot::useAbility()
{
	if (current_energy >= ROBOT_ABILITY_COST)
	{
		bonus_damage = strength * pow(double(current_energy) / maximum_energy, 4);
		current_energy -= ROBOT_ABILITY_COST;
		return true;
	}
	else
	{
		bonus_damage = 0;
		return false;
	}
}

int Robot::getDamage()
{
	return strength + bonus_damage;
}

void Robot::regenerate()
{
	double increase = strength / 6;
	if (increase < 1)
		increase = 1;
	if ((currentHP + increase) <= maximumHP)
		currentHP += increase;
	else
		currentHP = maximumHP;
}
