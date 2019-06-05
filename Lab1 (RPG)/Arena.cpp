#include "Arena.h"

Arena::Arena()
{
}

Arena::~Arena()
{
}

bool Arena::addFighter(std::string info)
{
	std::istringstream ss(info);
	std::string name;
	std::string type;
	int hitPoints, strengths, speed, magic, test;


	if (ss >> name >> type >> hitPoints >> strengths >> speed >> magic)
	{
		//Find duplicate names
		for (int i = 0; i < fightersVec.size(); ++i)
		{
			if (fightersVec.at(i)->getName() == name)
			{
				return false;
			}
		}

		if (ss >> test)
		{
			return false;
		}

		if (type == "R")
		{
			fightersVec.push_back(new Robot(name, type, hitPoints, strengths, speed, magic));
			return true;
		}
		else if (type == "A")
		{
			fightersVec.push_back(new Archer(name, type, hitPoints, strengths, speed, magic));
			return true;
		}
		else if (type == "C")
		{
			fightersVec.push_back(new Cleric(name, type, hitPoints, strengths, speed, magic));
			return true;
		}
		else
		{
			ss.clear();
			return false;
		}
	}
	ss.clear();
	return false;
}

bool Arena::removeFighter(std::string name)
{
	for (int i = 0; i < fightersVec.size(); ++i)
	{
		if (fightersVec.at(i)->getName() == name)
		{
			fightersVec.erase(fightersVec.begin() + i);
			return true;
		}
	}

	return false;
}

FighterInterface* Arena::getFighter(std::string name)
{
	for (Fighter* fighter : fightersVec)
	{
		if (fighter->getName() == name)
		{
			return fighter;
		}
	}

	return NULL;
}

int Arena::getSize() const
{
	return fightersVec.size();
}