#pragma once
#include "Fighter.h"
class Cleric : public Fighter
{
public:
	Cleric(std::string name, std::string type, int hitPoints, int strengths, int speed, int magic);
	~Cleric();
	virtual std::string getName() const;
	virtual int getMaximumHP() const;
	virtual int getCurrentHP() const;
	virtual int getStrength() const;
	virtual int getSpeed() const;
	virtual int getMagic() const;
	virtual int getDamage();
	virtual void takeDamage(int damage);
	virtual void reset();
	virtual void regenerate();
	virtual bool useAbility();
private:
	int currentHitPoints;
	int currentMana;
};

