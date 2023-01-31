#pragma once

#include "criterion.h"
#include "criterion_type.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> Vrati kod vyssieho uzemneho celku. </summary>
class CriterionBelonging
	: public Criterion<UzemnaJednotka, std::string>
{
public:
	std::string evaluate(UzemnaJednotka& object) override;
};

inline std::string CriterionBelonging::evaluate(UzemnaJednotka& object)
{
	if (CriterionType().evaluate(object) == "Kraj")
	{
		return "";
	}
	if (CriterionType().evaluate(object) == "Okres")
	{
		return object.code().substr(0, 5);
	}
	if (CriterionType().evaluate(object) == "Obec")
	{
		return object.code().substr(0, 6);
	}
}
