#pragma once

#include "../criterions/criterion.h"
#include "../structures/list/array_list.h"
#include "../structures/heap_monitor.h"

template<typename ObjectType>
class Filter
{
public:
	virtual ~Filter() = default;
	virtual bool pass(ObjectType& object) = 0;
};

template<typename ObjectType, typename ValueType>
class FilterWithCriterion
	: public Filter<ObjectType>
{
public:
	FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion);
	~FilterWithCriterion() override;
	bool pass(ObjectType& object) override;
protected:
	virtual bool passFilter(ValueType value) = 0;
private:
	Criterion<ObjectType, ValueType>* criterion_;
};

template<typename ObjectType, typename ValueType>
class FilterEquals
	: public FilterWithCriterion<ObjectType, ValueType>
{
public:
	FilterEquals(Criterion<ObjectType, ValueType>* criterion, ValueType value);
protected:
	bool passFilter(ValueType value) override;
	ValueType value_;
};

template<typename ObjectType, typename ValueType>
class FilterInterval
	: public FilterWithCriterion<ObjectType, ValueType>
{
public:
	FilterInterval(Criterion<ObjectType, ValueType>* criterion, ValueType valMin, ValueType valMax);

protected:
	bool passFilter(ValueType value) override;
private:
	ValueType valueMin_;
	ValueType valueMax_;
};

template<typename ObjectType>
class CompositeFilter
	: public Filter<ObjectType>
{
public:
	~CompositeFilter() override;
	void registerFilter(Filter<ObjectType>* filter);
protected:
	structures::ArrayList<Filter<ObjectType>*> filters_;
};

template<typename ObjectType>
class FilterAnd
	: public CompositeFilter<ObjectType>
{
public:
	bool pass(ObjectType& object) override;
};

template<typename ObjectType>
class FilterOr
	: public CompositeFilter<ObjectType>
{
public:
	bool pass(ObjectType& object) override;
};

//

template <typename ObjectType, typename ValueType>
FilterWithCriterion<ObjectType, ValueType>::FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion)
	: criterion_(criterion)
{
}

template <typename ObjectType, typename ValueType>
FilterWithCriterion<ObjectType, ValueType>::~FilterWithCriterion()
{
	delete criterion_;
	criterion_ = nullptr;
}

template <typename ObjectType, typename ValueType>
bool FilterWithCriterion<ObjectType, ValueType>::pass(ObjectType& object)
{
	return passFilter(criterion_->evaluate(object));
}

template <typename ObjectType, typename ValueType>
FilterEquals<ObjectType, ValueType>::FilterEquals(Criterion<ObjectType, ValueType>* criterion, ValueType value)
	: FilterWithCriterion<ObjectType, ValueType>(criterion), value_(value)
{
}

template <typename ObjectType, typename ValueType>
bool FilterEquals<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value == value_;
}

template <typename ObjectType, typename ValueType>
FilterInterval<ObjectType, ValueType>::FilterInterval(Criterion<ObjectType, ValueType>* criterion, ValueType valMin, ValueType valMax)
	: FilterWithCriterion<ObjectType, ValueType>(criterion), valueMin_(valMin), valueMax_(valMax)
{
}

template <typename ObjectType, typename ValueType>
bool FilterInterval<ObjectType, ValueType>::passFilter(ValueType value)
{
	return value >= valueMin_ && value <= valueMax_;
}

template <typename ObjectType>
CompositeFilter<ObjectType>::~CompositeFilter()
{
	for (auto filter : filters_)
	{
		delete filter;
		filter = nullptr;
	}
}

template <typename ObjectType>
void CompositeFilter<ObjectType>::registerFilter(Filter<ObjectType>* filter)
{
	filters_.add(filter);
}

template <typename ObjectType>
bool FilterAnd<ObjectType>::pass(ObjectType& object)
{
	for (auto filter : this->filters_)
	{
		if (!filter->pass(object))
		{
			return false;
		}
	}
	return true;
}

template <typename ObjectType>
bool FilterOr<ObjectType>::pass(ObjectType& object)
{
	for (auto filter : this->filters_)
	{
		if (filter->pass(object))
		{
			return true;
		}
	}
	return false;
}
