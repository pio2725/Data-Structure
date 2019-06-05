#include "Robot.h"

Robot::Robot(std::string name, std::string type, int hitPoints, int strengths, int speed, int magic)
	: Fighter(name, type, hitPoints, strengths, speed, magic)
{
	energy = magic * 2;
	currentEnergy = energy;
	currentHitPoints = hitPoints;
	bonusDamage = 0;
}

Robot::~Robot()
{
}

std::string Robot::getName() const
{
	return name;
}

int Robot::getMaximumHP() const
{
	return hitPoints;
}

int Robot::getCurrentHP() const
{
	return currentHitPoints;
}

int Robot::getStrength() const
{
	return strengths;
}

int Robot::getSpeed() const
{
	return speed;
}

int Robot::getMagic() const
{
	return magic;
}

int Robot::getDamage()
{
	int plus = bonusDamage + strengths;
	bonusDamage = 0;
	return plus;
}

void Robot::takeDamage(int damage)
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

void Robot::reset()
{
	currentHitPoints = hitPoints;
	currentEnergy = energy;
	bonusDamage = 0;
}

void Robot::regenerate()
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

bool Robot::useAbility()
{
	if (currentEnergy >= ROBOT_ABILITY_COST)
	{
		bonusDamage = (double)strengths * pow(((double)currentEnergy / energy), 4);
		currentEnergy -= ROBOT_ABILITY_COST;
		return true;
	}
	return false;
}