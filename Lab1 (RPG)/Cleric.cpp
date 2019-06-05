#include "Cleric.h"

Cleric::Cleric(std::string name, std::string type, int hitPoints, int strengths, int speed, int magic)
	: Fighter(name, type, hitPoints, strengths, speed, magic)
{
	currentHitPoints = hitPoints;
	currentMana = magic * 5;
}

Cleric::~Cleric()
{
}

std::string Cleric::getName() const
{
	return name;
}

int Cleric::getMaximumHP() const
{
	return hitPoints;
}

int Cleric::getDamage()
{
	return magic;
}

void Cleric::takeDamage(int damage)
{
	int damageTaken = 0;
	if ((damage - (speed / 4) < 1))
	{
		currentHitPoints -= 1;
	}
	else
	{
		damageTaken = (damage - (speed / 4));
		currentHitPoints = currentHitPoints - damageTaken;
	}
}

int Cleric::getCurrentHP() const
{
	return currentHitPoints;
}

int Cleric::getStrength() const
{
	return strengths;
}

int Cleric::getSpeed() const
{
	return speed;
}

int Cleric::getMagic() const
{
	return magic;
}

void Cleric::reset()
{
	currentHitPoints = hitPoints;
	currentMana = magic * 5;
}

void Cleric::regenerate()
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

	if ((magic / 5) < 1)
	{
		currentMana += 1;
	}
	else
	{
		currentMana = currentMana + (magic / 5);
	}

	if (currentMana > (magic * 5))
	{
		currentMana = (magic * 5);
	}
}

bool Cleric::useAbility()
{
	if (currentMana >= CLERIC_ABILITY_COST)
	{
		if ((magic / 3) < 1)
		{
			++currentHitPoints;
		}
		else
		{
			currentHitPoints = currentHitPoints + (magic / 3);
		}

		if (currentHitPoints > hitPoints)
		{
			currentHitPoints = hitPoints;
		}
		currentMana -= CLERIC_ABILITY_COST;
		return true;
	}
	return false;
}