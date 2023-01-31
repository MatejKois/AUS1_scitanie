#pragma once

#include "uzemna_jednotka.h"

class Okres
	: public UzemnaJednotka
{
public:
	Okres(std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string code, std::string note)
		: UzemnaJednotka(officialTitle, mediumTitle, shortTitle, code, note)
	{
	}
	Okres(Okres& other)
		: UzemnaJednotka(other)
	{
	}
};