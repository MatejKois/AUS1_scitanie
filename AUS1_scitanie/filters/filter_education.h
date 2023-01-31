#pragma once

#include "filter.h"
#include "../criterions/criterion_education.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

/// <summary> Filtruje uzemne jednotky podla poctu daneho vzdelania. </summary>
class FilterEducationCountEquals
	: public FilterEquals<UzemnaJednotka, int>
{
public:
	FilterEducationCountEquals(CriterionEducationCount* criterionEducationCount, int value);
};

/// <summary> Filtruje uzemne jednotky podla podielu daneho vzdelania. </summary>
class FilterEducationRatioEquals
	: public FilterEquals<UzemnaJednotka, float>
{
public:
	FilterEducationRatioEquals(CriterionEducationRatio* criterionEducationRatio, float value);
};

/// <summary> Filtruje uzemne jednotky podla poctu daneho vzdelania. </summary>
class FilterEducationCountInterval
	: public FilterInterval<UzemnaJednotka, int>
{
public:
	FilterEducationCountInterval(CriterionEducationCount* criterionEducationCount, int valueMin, int valueMax);
};

/// <summary> Filtruje uzemne jednotky podla podielu daneho vzdelania. </summary>
class FilterEducationRatioInterval
	: public FilterInterval<UzemnaJednotka, float>
{
public:
	FilterEducationRatioInterval(CriterionEducationRatio* criterionEducationRatio, float valueMin, float valueMax);
};

//

inline FilterEducationCountEquals::FilterEducationCountEquals(CriterionEducationCount* criterionEducationCount, int value)
	: FilterEquals(criterionEducationCount, value)
{
}

inline FilterEducationRatioEquals::FilterEducationRatioEquals(CriterionEducationRatio* criterionEducationRatio, float value)
	: FilterEquals(criterionEducationRatio, value)
{
}

inline FilterEducationCountInterval::FilterEducationCountInterval(CriterionEducationCount* criterionEducationCount,
	int valueMin, int valueMax)
		: FilterInterval(criterionEducationCount, valueMin, valueMax)
{
}

inline FilterEducationRatioInterval::FilterEducationRatioInterval(CriterionEducationRatio* criterionEducationRatio,
	float valueMin, float valueMax)
		: FilterInterval(criterionEducationRatio, valueMin, valueMax)
{
}
