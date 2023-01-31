#pragma once

#include  <string>
#include "../structures/table/sorted_sequence_table.h"
#include "../uzemne_jednotky/kraj.h"
#include "../uzemne_jednotky/okres.h"
#include "../uzemne_jednotky/obec.h"
#include "../filters/filter.h"
#include "../structures/heap_monitor.h"

class Interface
{
public:
	/// <summary> Destruktor. </summary>
	~Interface();

	/// <summary> Zavola metodu pre nacitanie uzemnych jednotiek do pamate. </summary>
	void initialize();

	/// <summary> Spusti mainloop s vypismi moznosti pre pouzivatela. </summary>
	void displayOptions();

	/// <summary> Bezpecne hladanie podla nazvu medzi vsetkymi uzemnymi jednotkami. </summary>
	UzemnaJednotka* search(std::string input);

	/// <summary> Zobrazi menu na aplikovanie kriterii pre najdeny vysledok. </summary>
	void criterionMenu(UzemnaJednotka* object);

	/// <summary> Zobrazi menu s dostupnymi filtrami pre danu mnozinu. </summary>
	void filterMenu(int input, structures::ArrayList<UzemnaJednotka*>* sortBuffer = nullptr);

	/// <summary> Zobrazi menu na triedenie. </summary>
	void sortingMenu(structures::ArrayList<UzemnaJednotka*>* sortBuffer);
private:
	/// <summary> Vsetky kraje. </summary>
	structures::SortedSequenceTable<std::string, Kraj*> kraje_;
	/// <summary> Vsetky okresy. </summary>
	structures::SortedSequenceTable<std::string, Okres*> okresy_;
	/// <summary> Vsetky obce. </summary>
	structures::SortedSequenceTable<std::string, Obec*> obce_;
};
