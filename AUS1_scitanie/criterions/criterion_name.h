#pragma once

#include <string>
#include "criterion.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> Vrati nazov danej uzemnej jednotky. </summary>
class CriterionName
	: public Criterion<UzemnaJednotka, std::string>
{
public:
	std::string evaluate(UzemnaJednotka& object) override;
};

inline std::string CriterionName::evaluate(UzemnaJednotka& object)
{
	return object.officialTitle();
}
