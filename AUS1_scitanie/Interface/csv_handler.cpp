#include "csv_handler.h"

#include <iostream>
#include <string>
#include <sstream>

#include "../structures/heap_monitor.h"
#include "../structures/list/array_list.h"
#include "../structures/splitter.h"

void CsvHandler::fillTables(structures::SortedSequenceTable<std::string, Kraj*>& kraje, structures::SortedSequenceTable<std::string, Okres*>& okresy, structures::SortedSequenceTable<std::string, Obec*>& obce)
{
	inObce.open("../obce.csv");
	inVzdelanie.open("../vzdelanie.csv");
	inOkresy.open("../okresy.csv");
	inKraje.open("../kraje.csv");

	if (!inObce)
	{
		std::cout << "Nenajdeny subor s obcami!" << "\n";
		return;
	}
	if (!inVzdelanie)
	{
		std::cout << "Nenajdeny subor so vzdelanim!" << "\n";
		return;
	}
	if (!inOkresy)
	{
		std::cout << "Nenajdeny subor s okresmi!" << "\n";
		return;
	}
	if (!inKraje)
	{
		std::cout << "Nenajdeny subor s krajmi!" << "\n";
		return;
	}

	std::string dummy;
	std::getline(inObce, dummy);
	std::getline(inVzdelanie, dummy);
	std::getline(inOkresy, dummy);
	std::getline(inKraje, dummy);

	readEducation();
	read(kraje, okresy, obce);

	inObce.close();
	inVzdelanie.close();
	inOkresy.close();
	inKraje.close();
}

void CsvHandler::readEducation()
{
	std::string vzdelInput;
	std::getline(inVzdelanie, vzdelInput);

	while (!vzdelInput.empty())
	{
		structures::ArrayList<std::string*>* vzdel = new structures::ArrayList<std::string*>;
		structures::Splitter::splitBySemicolon(vzdelInput, *vzdel);

		educInput_.insert(*vzdel->at(0), vzdel);
		std::getline(inVzdelanie, vzdelInput);
	}

	//chybajuca obec!
	structures::ArrayList<std::string*>* vzdel = new structures::ArrayList<std::string*>;

	//data inej nahodnej obce...
	vzdel->add(new std::string("SK0413523551"));
	vzdel->add(new std::string("Javorina(vojensky obvod)"));
	vzdel->add(new std::string("119"));
	vzdel->add(new std::string("214"));
	vzdel->add(new std::string("272"));
	vzdel->add(new std::string("245"));
	vzdel->add(new std::string("48"));
	vzdel->add(new std::string("68"));
	vzdel->add(new std::string("6"));
	vzdel->add(new std::string("50"));

	educInput_.insert("SK0413523551", vzdel);
}

void CsvHandler::read(structures::SortedSequenceTable<std::string, Kraj*>& kraje, structures::SortedSequenceTable<std::string, Okres*>& okresy, structures::SortedSequenceTable<std::string, Obec*>& obce)
{
	std::cout << "Prebieha nacitanie..." << "\n";

	Kraj* krajToAdd = readFromKraje();
	Okres* okresToAdd = readFromOkresy();
	Obec* obecToAdd = readFromObce();
	int countObce = 0;
	int countOkresy = 0;
	int countKraje = 0;
	while (krajToAdd != nullptr)
	{
		int popCountKraj = 0;
		while (okresToAdd != nullptr && (okresToAdd->code().substr(0, 5) == krajToAdd->note().substr(5, 5)))
		{
			int popCountOkres = 0;

			while (obecToAdd != nullptr && (obecToAdd->code().substr(0, 6) == okresToAdd->code()))
			{
				//udaje o vzdelani v okrese sa zrataju podla obci v nom
				for (int i = 0; i < 8; ++i)
				{
					okresToAdd->education(i) += obecToAdd->education(i);
				}
				addObec(obce, obecToAdd);
				countObce++;
				popCountOkres += obecToAdd->populationCount();
				obecToAdd = readFromObce();
			}

			for (int i = 0; i < 8; ++i)
			{
				krajToAdd->education(i) += okresToAdd->education(i);
			}
			okresToAdd->setPopCount(popCountOkres);
			okresy.insert(okresToAdd->officialTitle(), okresToAdd);
			countOkresy++;
			popCountKraj += popCountOkres;
			okresToAdd = readFromOkresy();
		}
		krajToAdd->setPopCount(popCountKraj);
		kraje.insert(krajToAdd->officialTitle(), krajToAdd);
		countKraje++;
		krajToAdd = readFromKraje();
	}

	std::cout << "Nacitanie prebehlo uspesne!\nNacitanych "
			  << countKraje << " krajov, "
			  << countOkresy << " okresov a "
			  << countObce << " obci." << "\n";
}

Kraj* CsvHandler::readFromKraje()
{
	std::string krajInput;
	std::getline(inKraje, krajInput);

	if (krajInput.empty() || krajInput.substr(4, 10) == "Zahranicie")
	{
		return nullptr;
	}

	structures::ArrayList<std::string*> kraj;
	structures::Splitter::splitBySemicolon(krajInput, kraj);

	Kraj* toAdd = new Kraj(*kraj.at(2), *kraj.at(3), *kraj.at(4), *kraj.at(1), *kraj.at(5));

	for (std::string* entry : kraj) delete entry;

	return toAdd;
}

Okres* CsvHandler::readFromOkresy()
{
	std::string okresInput;
	std::getline(inOkresy, okresInput);

	if (okresInput.empty() || okresInput.substr(3, 3) == "SKZ")
	{
		return nullptr;
	}

	structures::ArrayList<std::string*> okres;
	structures::Splitter::splitBySemicolon(okresInput, okres);

	Okres* toAdd = new Okres(*okres.at(2), *okres.at(3), *okres.at(4), *okres.at(1), *okres.at(5));

	for (std::string* entry : okres) delete entry;

	return toAdd;
}

Obec* CsvHandler::readFromObce()
{
	std::string obecInput;

	std::getline(inObce, obecInput);
	
	if (obecInput.empty() || obecInput.substr(5, 3) == "SKZ")
	{
		return nullptr;
	}

	structures::ArrayList<std::string*> obec;
	structures::Splitter::splitBySemicolon(obecInput, obec);
	structures::ArrayList<std::string*>* vzdel = educInput_.find(*obec.at(1));
	
	Obec* toAdd = new Obec(*obec.at(2), *obec.at(3), *obec.at(4), *obec.at(1), *obec.at(5));
	
	int popCount = 0;
	for (int i = 0; i < 8; ++i)
	{
		int educInt = std::stoi(*vzdel->at(i + 2));
		popCount += educInt;
		toAdd->education(i) = educInt;
	}
	toAdd->setPopCount(popCount);

	for (std::string* entry : obec) delete entry;
	for (std::string* entry : *vzdel) delete entry;
	delete vzdel;

	return toAdd;
}

void CsvHandler::addObec(structures::SortedSequenceTable<std::string, Obec*>& obce, Obec* obec)
{
	try
	{
		obce.insert(obec->officialTitle(), obec);
	}
	catch (std::logic_error e) // v pripade, ze sa uz nachadza v zozname obec s rovnakym nazvom, vytvori sa umely kluc...
	{
		int count = 1;
		std::stringstream candidateKey;
		do
		{
			candidateKey.str(std::string());
			candidateKey << obec->officialTitle() << " " << count;
			count++;
		} while (obce.containsKey(candidateKey.str()));
		obce.insert(candidateKey.str(), obec);
	}
}
