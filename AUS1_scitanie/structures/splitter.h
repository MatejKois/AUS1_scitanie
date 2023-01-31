#pragma once

#include "list/array_list.h"
#include "../structures/heap_monitor.h"

namespace structures
{
	class Splitter
	{
	public:
		///<summary> Rozdeli string podla bodkociarok na substringy a vlozi ich do ArrayListu. </summary>
		static void splitBySemicolon(std::string toSplit, ArrayList<std::string*>& outList);
	};

	inline void Splitter::splitBySemicolon(std::string toSplit, ArrayList<std::string*>& outList)
	{
		std::string buff;
		for (int i = 0; i < toSplit.length(); ++i)
		{
			if (toSplit.at(i) == ';')
			{
				outList.add(new std::string(buff));
				buff.clear();
				continue;
			}
			buff += toSplit.at(i);
		}
		if (!buff.empty())
		{
			outList.add(new std::string(buff));
		}
	}
}
