#include "Archer.h"


Archer::Archer(std::string name, std::string type, int hitPoints, int strengths, int speed, int magic)
	: Fighter(name, type, hitPoints, strengths, speed, magic)
{
	originalSpeed = speed;
	currentHitPoints = hitPoints;
}

Archer::~Archer()
{
}

std::string Archer::getName() const
{
	return name;
}

int Archer::getMaximumHP() const
{
	return hitPoints;
}

int Archer::getCurrentHP() const
{
	return currentHitPoints;
}

int Archer::getStrength() const
{
	return strengths;
}

int Archer::getSpeed() const
{
	return speed;
}

int Archer::getMagic() const
{
	return magic;
}

int Archer::getDamage()
{
	return speed;
}

void Archer::takeDamage(int damage)
{
	if ((damage - (speed / 4) < 1))
	{
		currentHitPoints -= 1;
	}
	else
	{
		currentHitPoints = currentHitPoints - (damage - (speed / 4));
	}
}

void Archer::reset()
{
	currentHitPoints = hitPoints;
	speed = originalSpeed;
}

void Archer::regenerate()
{
	if ((strengths / 6) < 1)
	{
		currentHitPoints += 1;
	}
	else
	{
		currentHitPoints = currentHitPoints + (strengths / 6);
	}

	if (currentHitPoints > hitPoints)
	{
		currentHitPoints = hitPoints;
	}
}

bool Archer::useAbility()
{
	++speed;
	return true;
}