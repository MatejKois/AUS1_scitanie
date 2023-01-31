#pragma once

#include "criterion.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> 'Dummy' kriterium, pouziva sa pri vytvarani kompzitneho filtra AND, ak by pouzivatel nezadal ziadne filtre. </summary>
class CriterionTrue
	: public Criterion<UzemnaJednotka, bool>
{
public:
	bool evaluate(UzemnaJednotka& object) override;
};

inline bool CriterionTrue::evaluate(UzemnaJednotka& object)
{
	return true;
}
