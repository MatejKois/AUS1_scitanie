#pragma once

#include "uzemna_jednotka.h"

class Kraj
	: public UzemnaJednotka
{
public:
	Kraj(std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string code, std::string note)
		: UzemnaJednotka(officialTitle, mediumTitle, shortTitle, code, note)
	{
	}
	Kraj(Kraj& other)
		: UzemnaJednotka(other)
	{
	}
};
