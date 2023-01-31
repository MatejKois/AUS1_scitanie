#include "interface.h"
#include "csv_handler.h"
#include "../filters/filter.h"
#include "../filters/filter_true.h"
#include "../filters/filter_belonging.h"
#include "../filters/filter_education.h"
#include "../criterions/criterion_name.h"
#include "../criterions/criterion_education.h"
#include "../criterions/criterion_type.h"
#include "../criterions/criterion_belonging.h"
#include "../structures/list/array_list.h"
#include "../structures/splitter.h"
#include "../structures/heap_monitor.h"
#include "../structures/table/sorting/quick_sort.h"

#include <iostream>

#define OPTION_SEARCH "1"
#define OPTION_FILTER "2"
#define OPTION_SORT "3"

#define OPTION_KRAJE 1
#define OPTION_OKRESY 2
#define OPTION_OBCE 3

#define OPTION_CRITERION_NONE 0
#define OPTION_CRITERION_NAME 1
#define OPTION_CRITERION_TYPE 2
#define OPTION_CRITERION_EDUCATION_COUNT 3
#define OPTION_CRITERION_EDUCATION_RATIO 4
#define OPTION_CRITERION_BELONGING 5

#define OPTION_FILTER_NONE "0"
#define OPTION_FILTER_EDUCATION_COUNT "1"
#define OPTION_FILTER_EDUCATION_RATIO "2"

#define OPTION_FILTER_TYPE_EQUALS "1"
#define OPTION_FILTER_TYPE_INTERVAL "2"

Interface::~Interface()
{
	for (auto data : obce_)
	{
		delete data->accessData();
	}
	for (auto data : okresy_)
	{
		delete data->accessData();
	}
	for (auto data : kraje_)
	{
		delete data->accessData();
	}
}

void Interface::initialize()
{
	CsvHandler().fillTables(kraje_, okresy_, obce_);
}

void Interface::displayOptions()
{
	std::string selection;
	std::cout << "\n" << OPTION_SEARCH << " - vyhladanie\n" << OPTION_FILTER << " - filtrovanie\n" << OPTION_SORT <<
		" - zoradenie\nexit - koniec\n";
	std::getline(std::cin, selection);

	if (selection == "exit")
	{
		return;
	}

	if (selection == OPTION_SEARCH)
	{
		std::string userInput;
		std::cout << "Co mam hladat?\n";
		std::getline(std::cin, userInput);
		UzemnaJednotka* found = search(userInput);
		if (found != nullptr)
		{
			std::cout << "Vysledok:\n";
			found->toString();
			//std::cout << "Hodnota kriteria pre meno: " << CriterionName().evaluate(*found) << "\n";
			criterionMenu(found);
		}
	}

	if (selection == OPTION_FILTER)
	{
		std::string userInput;
		std::cout << "Co mam filtrovat?\n" << OPTION_KRAJE << " - kraje\n" << OPTION_OKRESY << " - okresy\n" <<
			OPTION_OBCE << " - obce\n";
		std::getline(std::cin, userInput);
		try
		{
			filterMenu(std::stoi(userInput));
		}
		catch (std::exception e)
		{
			std::cout << "Neplatna volba!\n";
		}
	}

	if (selection == OPTION_SORT)
	{
		std::string userInput;
		std::cout << "Co mam zoradit?\n" << OPTION_KRAJE << " - kraje\n" << OPTION_OKRESY << " - okresy\n" <<
			OPTION_OBCE << " - obce\n";
		structures::ArrayList<UzemnaJednotka*>* sortBuffer = new structures::ArrayList<UzemnaJednotka*>;
		std::getline(std::cin, userInput);
		try
		{
			filterMenu(std::stoi(userInput), sortBuffer);
			sortingMenu(sortBuffer);
		}
		catch (std::exception e)
		{
			std::cout << "Neplatna volba!\n";
		}
		delete sortBuffer;
	}

	displayOptions();
}

UzemnaJednotka* Interface::search(std::string input)
{
	UzemnaJednotka* found = nullptr;
	try
	{
		found = kraje_.find(input);
	}
	catch (std::logic_error e)
	{
		try
		{
			found = okresy_.find(input);
		}
		catch (std::logic_error e)
		{
			try
			{
				found = obce_.find(input);
			}
			catch (std::logic_error e)
			{
				std::cout << "Nenajdeny ziaden vysledok!\n";
			}
		}
	}
	return found;
}

void Interface::criterionMenu(UzemnaJednotka* object)
{
	std::cout <<
		"Pouzit kriterium?\n" << OPTION_CRITERION_NONE << " - ziadne\n" << OPTION_CRITERION_NAME << " - meno\n" <<
		OPTION_CRITERION_TYPE
		<< " - typ\n" << OPTION_CRITERION_EDUCATION_COUNT << " - vzdelanie pocet\n" << OPTION_CRITERION_EDUCATION_RATIO
		<< " - vzdelanie podiel\n"
		<< OPTION_CRITERION_BELONGING << " - prislusnost" << "\n";

	std::string userInput;
	std::getline(std::cin, userInput);
	int intUserInput = -1;
	try
	{
		intUserInput = std::stoi(userInput);
	}
	catch (std::exception e)
	{
		std::cout << "Neplatna volba!\n";
	}
	switch (intUserInput)
	{
	case OPTION_CRITERION_NONE:
		return;
	case OPTION_CRITERION_NAME:
		{
			std::cout << "Hodnota kriteria: " << CriterionName().evaluate(*object) << "\n";
		}
		break;
	case OPTION_CRITERION_TYPE:
		{
			std::cout << "Hodnota kriteria: " << CriterionType().evaluate(*object) << "\n";
		}
		break;
	case OPTION_CRITERION_EDUCATION_COUNT:
		{
			std::cout << "Zadajte typ vzdelania:\n"
				<< "0 - Bez vzdelania (0 - 14)" << "\n"
				<< "1 - Zakladne vzdelanie" << "\n"
				<< "2 - Stredne odborne vzdelanie" << "\n"
				<< "3 - Uplne stredne vzdelanie" << "\n"
				<< "4 - VSOB" << "\n"
				<< "5 - Vysokoskolske vzdelanie" << "\n"
				<< "6 - Bez vzdelania (15+)" << "\n"
				<< "7 - Nezistene" << "\n";
			std::string educationC;
			std::getline(std::cin, educationC);
			try
			{
				std::cout << "Hodnota kriteria: " << CriterionEducationCount(std::stoi(educationC)).evaluate(*object) <<
					"\n";
			}
			catch (std::exception e)
			{
				std::cout << "Neplatna volba!\n";
			}
		}
		break;
	case OPTION_CRITERION_EDUCATION_RATIO:
		{
			std::cout << "Zadajte typ vzdelania:\n"
				<< "0 - Bez vzdelania (0 - 14)" << "\n"
				<< "1 - Zakladne vzdelanie" << "\n"
				<< "2 - Stredne odborne vzdelanie" << "\n"
				<< "3 - Uplne stredne vzdelanie" << "\n"
				<< "4 - VSOB" << "\n"
				<< "5 - Vysokoskolske vzdelanie" << "\n"
				<< "6 - Bez vzdelania (15+)" << "\n"
				<< "7 - Nezistene" << "\n";
			std::string educationR;
			std::getline(std::cin, educationR);
			try
			{
				std::cout << "Hodnota kriteria: " << CriterionEducationRatio(std::stoi(educationR)).evaluate(*object) <<
					"\n";
			}
			catch (std::exception e)
			{
				std::cout << "Neplatna volba!\n";
			}
		}
		break;
	case OPTION_CRITERION_BELONGING:
		{
			std::cout << "Hodnota kriteria: " << CriterionBelonging().evaluate(*object) << "\n";
			std::string code = CriterionBelonging().evaluate(*object);
			if (code == "")
			{
				std::cout << "Kraj prislucha Slovenskej Republike\n";
			}
			if (code.length() == 6)
			{
				for (auto okres : okresy_)
				{
					if (okres->accessData()->code() == code)
					{
						std::cout << "Prislusnost: " << okres->accessData()->officialTitle() << "\n";
						break;
					}
				}
			}
			if (code.length() == 5)
			{
				for (auto kraj : kraje_)
				{
					if (kraj->accessData()->note().substr(5, 5) == code)
					{
						std::cout << "Prislusnost: " << kraj->accessData()->officialTitle() << "\n";
						break;
					}
				}
			}
		}
		break;
	}
	criterionMenu(object);
}

void Interface::filterMenu(int input, structures::ArrayList<UzemnaJednotka*>* sortBuffer)
{
	FilterAnd<UzemnaJednotka> completeFilter;
	completeFilter.registerFilter(new FilterTrue<UzemnaJednotka>);

	if (input > OPTION_KRAJE)
	{
		std::cout << "Aplikovat filtre prislusnosti? (a/n)\n";
		std::string in;
		std::getline(std::cin, in);
		if (in == "a")
		{
			FilterOr<UzemnaJednotka>* filterBelonging = new FilterOr<UzemnaJednotka>;
			std::cout << "Zadajte zoznam VUC, ktore vyhovuju filtru (oddelit bodkociarkou)\n";
			std::getline(std::cin, in);
			structures::ArrayList<std::string*> inputSplit;
			structures::Splitter().splitBySemicolon(in, inputSplit);
			for (auto entry : inputSplit)
			{
				try
				{
					if (input == OPTION_OKRESY)
					{
						filterBelonging->registerFilter(new FilterBelonging(kraje_.find(*entry)->note().substr(5, 5)));
					}
					else if (input == OPTION_OBCE)
					{
						if (entry->length() > 4 && entry->substr(0, 5) == "Okres")
						{
							filterBelonging->registerFilter(new FilterBelonging(okresy_.find(*entry)->code()));
						}
						else
						{
							filterBelonging->registerFilter(
								new FilterBelonging(kraje_.find(*entry)->note().substr(5, 5)));
						}
					}
				}
				catch (std::logic_error e)
				{
					std::cout << *entry << " nenajdeny!\n";
				}
				delete entry;
			}
			inputSplit.clear();
			completeFilter.registerFilter(filterBelonging);
		}
	}

	std::cout <<
		"Ktore filtre mam aplikovat? (zadavat po jednom)\n" << OPTION_FILTER_NONE << " - pokracovat\n" <<
		OPTION_FILTER_EDUCATION_COUNT
		<< " - vzdelanie pocet\n" << OPTION_FILTER_EDUCATION_RATIO << " - vzdelanie podiel\n";
	std::string in;
	std::getline(std::cin, in);
	while (in != OPTION_FILTER_NONE)
	{
		if (in == OPTION_FILTER_EDUCATION_COUNT || in == OPTION_FILTER_EDUCATION_RATIO)
		{
			std::cout << "Zadajte typ filtra\n" << OPTION_FILTER_TYPE_EQUALS << " - filter zhody\n" <<
				OPTION_FILTER_TYPE_INTERVAL << " - filter intervalu\n";
			std::string in1;
			std::getline(std::cin, in1);
			if (in1 == OPTION_FILTER_TYPE_EQUALS)
			{
				std::cout << "Zadajte typ vzdelania:\n"
					<< "0 - Bez vzdelania (0 - 14)" << "\n"
					<< "1 - Zakladne vzdelanie" << "\n"
					<< "2 - Stredne odborne vzdelanie" << "\n"
					<< "3 - Uplne stredne vzdelanie" << "\n"
					<< "4 - VSOB" << "\n"
					<< "5 - Vysokoskolske vzdelanie" << "\n"
					<< "6 - Bez vzdelania (15+)" << "\n"
					<< "7 - Nezistene" << "\n";
				std::getline(std::cin, in1);
				std::cout << "Zadajte hodnotu kriteria pre filter:\n";
				std::string in2;
				std::getline(std::cin, in2);
				try
				{
					if (in == OPTION_FILTER_EDUCATION_COUNT)
					{
						completeFilter.registerFilter(
							new FilterEducationCountEquals(new CriterionEducationCount(std::stoi(in1)),
							                               std::stoi(in2)));
					}
					else if (in == OPTION_FILTER_EDUCATION_RATIO)
					{
						completeFilter.registerFilter(
							new FilterEducationRatioEquals(new CriterionEducationRatio(std::stoi(in1)),
							                               std::stoi(in2)));
					}
				}
				catch (std::exception e)
				{
					std::cout << "Neplatna volba!\n";
				}
			}
			else
			{
				std::cout << "Zadajte typ vzdelania:\n"
					<< "0 - Bez vzdelania (0 - 14)" << "\n"
					<< "1 - Zakladne vzdelanie" << "\n"
					<< "2 - Stredne odborne vzdelanie" << "\n"
					<< "3 - Uplne stredne vzdelanie" << "\n"
					<< "4 - VSOB" << "\n"
					<< "5 - Vysokoskolske vzdelanie" << "\n"
					<< "6 - Bez vzdelania (15+)" << "\n"
					<< "7 - Nezistene" << "\n";
				std::getline(std::cin, in1);
				std::cout << "Zadajte hodnotu intervalu od:\n";
				std::string in2;
				std::getline(std::cin, in2);
				std::cout << "Zadajte hodnotu intervalu do:\n";
				std::string in3;
				std::getline(std::cin, in3);

				try
				{
					if (in == OPTION_FILTER_EDUCATION_COUNT)
					{
						completeFilter.registerFilter(new FilterEducationCountInterval(
							new CriterionEducationCount(std::stoi(in1)), std::stoi(in2), std::stoi(in3)));
					}
					else if (in == OPTION_FILTER_EDUCATION_RATIO)
					{
						completeFilter.registerFilter(new FilterEducationRatioInterval(
							new CriterionEducationRatio(std::stoi(in1)), std::stoi(in2), std::stoi(in3)));
					}
				}
				catch (std::exception e)
				{
					std::cout << "Neplatna volba!\n";
				}
			}
		}
		std::cout <<
			"Ktore filtre mam aplikovat? (zadavat po jednom)\n0 - pokracovat\n1 - vzdelanie pocet\n2 - vzdelanie podiel\n";
		std::getline(std::cin, in);
	}

	switch (input)
	{
	case OPTION_KRAJE:
		{
			for (auto kraj : kraje_)
			{
				if (completeFilter.pass(*kraj->accessData()))
				{
					if (sortBuffer != nullptr) //v pripade ak filtrujeme do mnoziny na utriedenie
					{
						sortBuffer->add(kraj->accessData());
					}
					else
					{
						kraj->accessData()->toString();
					}
				}
			}
		}
		break;
	case OPTION_OKRESY:
		{
			for (auto okres : okresy_)
			{
				if (completeFilter.pass(*okres->accessData()))
				{
					if (sortBuffer != nullptr)
					{
						sortBuffer->add(okres->accessData());
					}
					else
					{
						okres->accessData()->toString();
					}
				}
			}
		}
		break;
	case OPTION_OBCE:
		{
			for (auto obec : obce_)
			{
				if (completeFilter.pass(*obec->accessData()))
				{
					if (sortBuffer != nullptr)
					{
						sortBuffer->add(obec->accessData());
					}
					else
					{
						obec->accessData()->toString();
					}
				}
			}
		}
		break;
	}
}

void Interface::sortingMenu(structures::ArrayList<UzemnaJednotka*>* sortBuffer)
{
	if (sortBuffer->size() == 0)
	{
		std::cout << "Prazdna mnozina!\n";
		return;
	}
	std::string selectionstr;
	int selection = -1;
	std::string education;
	std::string sortType;
	std::cout << "Podla ktoreho kriteria si prajete zoradit?\n" << OPTION_CRITERION_EDUCATION_COUNT <<
		" - vzdelanie pocet\n" << OPTION_CRITERION_EDUCATION_RATIO << " - vzdelanie podiel\n";
	std::getline(std::cin, selectionstr);

	try
	{
		selection = std::stoi(selectionstr);

		if (selection == OPTION_CRITERION_EDUCATION_COUNT || selection == OPTION_CRITERION_EDUCATION_RATIO)
		{
			std::cout << "Zadajte typ vzdelania:\n"
				<< "0 - Bez vzdelania (0 - 14)" << "\n"
				<< "1 - Zakladne vzdelanie" << "\n"
				<< "2 - Stredne odborne vzdelanie" << "\n"
				<< "3 - Uplne stredne vzdelanie" << "\n"
				<< "4 - VSOB" << "\n"
				<< "5 - Vysokoskolske vzdelanie" << "\n"
				<< "6 - Bez vzdelania (15+)" << "\n"
				<< "7 - Nezistene" << "\n";
			std::getline(std::cin, education);
		}
		if (selection == OPTION_CRITERION_EDUCATION_COUNT)
		{
			std::cout << "Zoradit:\n1 - vzostupne\n2 - zostupne" << "\n";
			std::getline(std::cin, sortType);
			if (sortType == "2")
			{
				structures::QuickSort<int>(new CriterionEducationCount(std::stoi(education))).sort(*sortBuffer, false);
			}
			else
			{
				structures::QuickSort<int>(new CriterionEducationCount(std::stoi(education))).sort(*sortBuffer, true);
			}
		}
		else if (selection == OPTION_CRITERION_EDUCATION_RATIO)
		{
			std::cout << "Zoradit:\n1 - vzostupne\n2 - zostupne" << "\n";
			std::getline(std::cin, sortType);
			if (sortType == "2")
			{
				structures::QuickSort<float>(new CriterionEducationRatio(std::stoi(education))).
					sort(*sortBuffer, false);
			}
			else
			{
				structures::QuickSort<float>(new CriterionEducationRatio(std::stoi(education))).sort(*sortBuffer, true);
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Neplatna volba!\n";
		return;
	}
	std::cout << "Vysledok:\n";
	for (auto element : *sortBuffer)
	{
		if (selection == OPTION_CRITERION_EDUCATION_COUNT)
		{
			std::cout << element->officialTitle() << " , hodnota kriteria: ";
			std::cout << CriterionEducationCount(std::stoi(education)).evaluate(*element) << '\n';
		}
		else if (selection == OPTION_CRITERION_EDUCATION_RATIO)
		{
			std::cout << element->officialTitle() << " , hodnota kriteria: ";
			std::cout << CriterionEducationRatio(std::stoi(education)).evaluate(*element) << '\n';
		}
	}
}

#undef OPTION_KRAJE
#undef OPTION_OKRESY
#undef OPTION_OBCE

#undef OPTION_SEARCH
#undef OPTION_FILTER
#undef OPTION_SORT

#undef OPTION_CRITERION_NONE
#undef OPTION_CRITERION_NAME
#undef OPTION_CRITERION_TYPE
#undef OPTION_CRITERION_EDUCATION_COUNT
#undef OPTION_CRITERION_EDUCATION_RATIO
#undef OPTION_CRITERION_BELONGING

#undef OPTION_FILTER_NONE
#undef OPTION_FILTER_EDUCATION_COUNT
#undef OPTION_FILTER_EDUCATION_RATIO

#undef OPTION_FILTER_TYPE_EQUALS
#undef OPTION_FILTER_TYPE_INTERVAL
