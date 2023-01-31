#pragma once

#include <string>
#include "criterion.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> Vrati typ uzemnej jednotky. </summary>
class CriterionType
	: public Criterion<UzemnaJednotka, std::string>
{
public:
	std::string evaluate(UzemnaJednotka& object) override;
};

inline std::string CriterionType::evaluate(UzemnaJednotka& object)
{
	if (object.officialTitle().length() > 5 && object.officialTitle().substr(0, 5) == "Okres")
	{
		return "Okres";
	}
	if (object.officialTitle().length() > 4 && object.officialTitle().substr(object.officialTitle().length() - 4, 4) == "kraj")
	{
		return "Kraj";
	}
	return "Obec";
}
