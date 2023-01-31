#pragma once

#include "criterion.h"
#include "../uzemne_jednotky/uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

template<typename ResultType>
class CriterionEducation
	: public Criterion<UzemnaJednotka, ResultType>
{
};

/// <summary> Vrati pocet ludi s danym vzdelanim v danej uzemnej jednotke. </summary>
class CriterionEducationCount
	: public CriterionEducation<int>
{
public:
	CriterionEducationCount(int education);
	int evaluate(UzemnaJednotka& object) override;
private:
	int education_;
};

/// <summary> Vrati podiel ludi s danym vzdelanim k celkovemu poctu obyvatelov uzemnej jednotky v percentach. </summary>
class CriterionEducationRatio
	: public CriterionEducation<float>
{
public:
	CriterionEducationRatio(int education);
	float evaluate(UzemnaJednotka& object) override;
private:
	int education_;
};

inline CriterionEducationCount::CriterionEducationCount(int education)
	: education_(education)
{
}

inline int CriterionEducationCount::evaluate(UzemnaJednotka& object)
{
	return object.education(education_);
}

inline CriterionEducationRatio::CriterionEducationRatio(int education)
	: education_(education)
{
}

inline float CriterionEducationRatio::evaluate(UzemnaJednotka& object)
{
	return object.educationRatio(education_);
}
