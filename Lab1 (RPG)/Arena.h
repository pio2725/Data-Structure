#ifndef  ARENA_H
#define ARENA_H

#include "ArenaInterface.h"
#include "Fighter.h"
#include "Robot.h"
#include "Archer.h"
#include "Cleric.h"
#include <sstream>


class Arena : public ArenaInterface
{
public:
	Arena();
	~Arena();
	bool addFighter(std::string info);
	bool removeFighter(std::string name);
	FighterInterface* getFighter(std::string name);
	int getSize() const;
private:
	std::vector<Fighter*> fightersVec;
};

#endif AREANA_H