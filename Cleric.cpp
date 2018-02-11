#include "Cleric.h"



Cleric::Cleric(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic)
	: Fighter(_name, _maximumHP, _strength, _speed, _magic), maximumMana(5 * _magic), currentMana(5 * _magic)

{
}

Cleric::~Cleric()
{
}

void Cleric::regenerate()
{
	double hp_increase = strength / 6;
	if (hp_increase < 1);
		hp_increase = 1;
	if ((currentHP + hp_increase) <= maximumHP)
		currentHP+=hp_increase;
	else
		currentHP = maximumHP;
	double mana_increase = strength / 5;
	if (mana_increase < 1)
		mana_increase = 1;
	double inc = currentMana + mana_increase;
	if (inc <= maximumMana)
		currentMana += mana_increase;
	else
		currentMana = maximumMana;
}

void Cleric::reset()
{
	currentHP = maximumHP;
	currentMana = maximumMana;
}

int Cleric::getDamage()
{
	return magic;
}

bool Cleric::useAbility()
{
	int increase = 0, hp_increase = 0;
	if (currentMana >= CLERIC_ABILITY_COST)
	{
		currentMana -= CLERIC_ABILITY_COST;
		increase = magic / 3 > 1 ? magic / 3 : 1;
		hp_increase = currentHP + increase;
		currentHP = hp_increase > maximumHP ? maximumHP : increase;
		return true;
	}
	else
		return false;
}
