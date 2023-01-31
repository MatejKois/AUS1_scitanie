#pragma once

#include <string>
#include <iostream>
#include "../structures/heap_monitor.h"
#include "../structures/array/array.h"

/// <summary> Vseobecny predok pre vsetky uzemne jednotky. </summary>
class UzemnaJednotka
{
public:
	/// <summary> Parametricky konstruktor. </summary>
	UzemnaJednotka(std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string code, std::string note);

	/// <summary> Kopirovaci konstruktor. </summary>
	UzemnaJednotka(UzemnaJednotka& other);

	/// <summary> Destruktor. </summary>
	~UzemnaJednotka();

	//gettery:

	std::string officialTitle() { return officialTitle_; }
	std::string mediumTitle() { return mediumTitle_; }
	std::string shortTitle() { return shortTitle_; }
	std::string code() { return code_; }
	std::string note() { return note_; }
	int populationCount() { return populationCount_; }
	int& education(int education) { return education_->at(education); }
	float educationRatio(int educ) { return 100 * static_cast<float>(education(educ)) / static_cast<float>(populationCount_); }

	//

	/// <summary> Setter, nastavi pocet obyvatelov obce. </summary>
	void setPopCount(int count) { populationCount_ = count; }

	/// <summary> Naformatuje vypis informacii danej uzemnej jednotky do tabulky. </summary>
	void toString();

private:
	/// <summary> Oficialny nazov. </summary>
	std::string officialTitle_;
	/// <summary> Stredne dlhy nazov. </summary>
	std::string mediumTitle_;
	/// <summary> Skrateny nazov. </summary>
	std::string shortTitle_;
	/// <summary> Kod. </summary>
	std::string code_;
	std::string note_;
	/// <summary> Pocet obyvatelov. </summary>
	int populationCount_;
	/// <summary> Udaje o vzdelani. </summary>
	structures::Array<int>* education_;
};

inline UzemnaJednotka::UzemnaJednotka(std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string code, std::string note)
	: officialTitle_(officialTitle),
	mediumTitle_(mediumTitle),
	shortTitle_(shortTitle),
	code_(code),
	note_(note)
{
	education_ = new structures::Array<int>(8);
}

inline UzemnaJednotka::UzemnaJednotka(UzemnaJednotka& other)
	: officialTitle_(other.officialTitle_),
	mediumTitle_(other.mediumTitle_),
	shortTitle_(other.shortTitle_),
	code_(other.code_),
	note_(other.note_),
	populationCount_(other.populationCount_)
{
	education_->assign(*other.education_);
}

inline UzemnaJednotka::~UzemnaJednotka()
{
	delete education_;
	education_ = nullptr;
}

inline void UzemnaJednotka::toString()
{
	
	std::cout << "----------------------------------------------------------------------------------------\n";
	std::cout << officialTitle() << ", pocet obyvatelov: " << populationCount() << "\n";
	std::cout << "----------------------------------------------------------------------------------------\n";
	std::cout << "| bez(<=14)| zakladne | ucnovske |uplne str.|   VSOB   |  vysoko  | bez(>=15)| nezistene|\n";
	for (int i = 0; i < 8; ++i)
	{
		printf("|%10d", education_->at(i));
	}
	std::cout << "|\n";
	for (int i = 0; i < 8; ++i)
	{
		printf("|%9.2f", educationRatio(i));
		std::cout << "%";
	}
	std::cout << "|\n----------------------------------------------------------------------------------------\n";
}
