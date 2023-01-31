#pragma once

#include "filter.h"
#include "../criterions/criterion_belonging.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> Filtruje uzemne jednotky podla prislusnosti. </summary>
class FilterBelonging
	: public FilterEquals<UzemnaJednotka, std::string>
{
public:
	FilterBelonging(std::string value);
	bool passFilter(std::string value) override;
};

inline FilterBelonging::FilterBelonging(std::string value)
	: FilterEquals(new CriterionBelonging, value)
{
}

inline bool FilterBelonging::passFilter(std::string value)
{
	//prekryta metoda, aby bolo mozne filtrovat aj obce z kraja podla kodu
	//kriterium pre prislusnost vracia kod jednotky iba o jeden stupen vyssie v hierarchii
	if (value.length() > value_.length())
	{
		value = value.substr(0, value_.length());
	}
	return value == value_;
}
