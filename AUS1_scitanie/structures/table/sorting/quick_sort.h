#pragma once

#include "../../list/array_list.h"
#include "../structures/heap_monitor.h"

namespace structures
{
	template<typename ValueType>
	class QuickSort
	{
	public:
		QuickSort(CriterionEducation<ValueType>* criterion);
		~QuickSort();
		void sort(structures::ArrayList<UzemnaJednotka*>& data, bool asc = true);
	private:

		/// <summary> Zoradenie - rekurzia. </summary>
		void quick(int min, int max, structures::ArrayList<UzemnaJednotka*>& data, bool asc);

		/// <summary> Kriterium, podla ktoreho sa porovnava. </summary>
		CriterionEducation<ValueType>* criterion_;
	};

	template <typename ValueType>
	QuickSort<ValueType>::QuickSort(CriterionEducation<ValueType>* criterion)
		: criterion_(criterion)
	{
	}

	template <typename ValueType>
	QuickSort<ValueType>::~QuickSort()
	{
		delete criterion_;
		criterion_ = nullptr;
	}

	template <typename ValueType>
	void QuickSort<ValueType>::sort(structures::ArrayList<UzemnaJednotka*>& data, bool asc)
	{
		quick(0, data.size() - 1, data, asc);
	}

	template <typename ValueType>
	void QuickSort<ValueType>::quick(int min, int max, structures::ArrayList<UzemnaJednotka*>& data, bool asc)
	{
		ValueType pivot = criterion_->evaluate(*data.at(min + ((max - min) / 2)));
		int left = min;
		int right = max;

		while (left <= right)
		{
			if (asc)
			{
				while (criterion_->evaluate(*data.at(left)) < pivot)
				{
					left++;
				}
				while (criterion_->evaluate(*data.at(right)) > pivot)
				{
					right--;
				}
			}
			else
			{
				while (criterion_->evaluate(*data.at(left)) > pivot)
				{
					left++;
				}
				while (criterion_->evaluate(*data.at(right)) < pivot)
				{
					right--;
				}
			}
			
			if (left <= right)
			{
				Utils::swap(data.at(left), data.at(right));
				left++;
				right--;
			}
		}
		if (min < right)
		{
			quick(min, right, data, asc);
		}
		if (left < max)
		{
			quick(left, max, data, asc);
		}
	}
}
