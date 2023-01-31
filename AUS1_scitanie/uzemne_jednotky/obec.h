#pragma once

#include "uzemna_jednotka.h"

class Obec
	: public UzemnaJednotka
{
public:
	Obec(std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string code, std::string note)
		: UzemnaJednotka(officialTitle, mediumTitle, shortTitle, code, note)
	{
	}
	Obec(Obec& other)
		: UzemnaJednotka(other)
	{
	}
};
