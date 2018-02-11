#include "Arena.h"



Arena::Arena() :fighters(std::vector<FighterInterface *>())
{
}


Arena::~Arena()
{
	for (int i = 0; i < fighters.size(); i++)
		delete fighters[i];
}

bool Arena::addFighter(std::string info)
{
	std::istringstream st(info);
        std::string name, type;
        int maxHP = 0, strength = 0, speed = 0, magic = 0;

	if (!(st >> name) || getFighter(name))
		return false;
	if (!(st >> type) || type.size() > 1)
		return false;
	if (!(st >> maxHP) || maxHP <= 0)
		return false;
	if (!(st >> strength) || strength <= 0)
		return false;
	if (!(st >> speed) || speed <= 0)
		return false;
	if (!(st >> magic) || magic <= 0)
		return 0;
	if (st.rdbuf()->in_avail())
		return false;
	FighterInterface * buff;
	if (type == "A")
		fighters.push_back(new Archer(name, maxHP, strength, speed, magic));
	else if (type == "C")
		fighters.push_back(new Cleric(name, maxHP, strength, speed, magic));
	else
		fighters.push_back(new Robot(name, maxHP, strength, speed, magic));
	return true;
}

FighterInterface* Arena::getFighter(std::string name)
{
	for (int i = 0; i < fighters.size(); i++)
	{
		if (fighters[i]->getName() == name)
			return fighters[i];
	}
	return NULL;
}

int Arena::getSize() const
{
	return fighters.size();
}

bool Arena::removeFighter(std::string name)
{
	for (int i = 0; i < fighters.size(); i++)
	{
		if (fighters[i]->getName() == name)
		{
			delete fighters[i];
			fighters.erase(fighters.begin() + i);
			return true;
		}
	}
	return false;
}
