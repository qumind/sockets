#pragma once
#include "ArenaInterface.h"
#include <math.h>
class Fighter: public FighterInterface
{
public:
	Fighter(const std::string& _name, int _maximumHP, int _strength, int _speed, int _magic);
    ~Fighter();

	std::string getName() const;
	int getMaximumHP() const;
	int getCurrentHP() const;
	int getStrength() const;
	int getSpeed() const;
	int getMagic() const;
	int getDamage();
	void takeDamage(int damage);

protected:
	std::string name;
	int maximumHP;
	int currentHP;
	int strength;
	int speed;
	int magic;	
};

