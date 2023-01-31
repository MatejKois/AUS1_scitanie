#pragma once

#include "filter.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include  "../criterions/criterion_true.h"
#include "../structures/heap_monitor.h"

/// <summary> 'Dummy' filter, pouziva sa pri vytvarani kompzitneho filtra AND, ak by pouzivatel nezadal ziadne filtre. </summary>
template<typename ObjectType>
class FilterTrue
	: public FilterEquals<ObjectType, bool>
{
public:
	FilterTrue();
};

template <typename ObjectType>
FilterTrue<ObjectType>::FilterTrue()
	: FilterEquals<ObjectType, bool>(new CriterionTrue, true)
{
}
