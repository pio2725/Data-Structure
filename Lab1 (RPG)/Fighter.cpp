#include "Fighter.h"



Fighter::Fighter(std::string name, std::string type, int hitPoints, int strengths, int speed, int magic)
{
	this->name = name;
	this->type = type;
	this->hitPoints = hitPoints;
	this->strengths = strengths;
	this->speed = speed;
	this->magic = magic;
}

Fighter::~Fighter()
{
}

