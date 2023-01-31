#pragma once

#include <fstream>
#include "../structures/table/sorted_sequence_table.h"
#include "../uzemne_jednotky/kraj.h"
#include "../uzemne_jednotky/okres.h"
#include "../structures/heap_monitor.h"
#include "../uzemne_jednotky/obec.h"

class CsvHandler
{
public:
	/// <summary> Otvori vstupne subory a spusti nacitavanie do tabuliek v parametroch. </summary>
	void fillTables(structures::SortedSequenceTable<std::string, Kraj*>& kraje, structures::SortedSequenceTable<std::string, Okres*>& okresy, structures::SortedSequenceTable<std::string, Obec*>& obce);

	/// <summary> Nacita data zo suporu so vzdelanim. Nakolko je subor poprehadzovany, je potrebne ulozit data so vzdelanim do docasnej utriedenej tabulky. </summary>
	void readEducation();

	/// <summary> Uklada systematicky jednotilve uzemne jednotky do prislusnych tabuliek. </summary>
	void read(structures::SortedSequenceTable<std::string, Kraj*>& kraje, structures::SortedSequenceTable<std::string, Okres*>& okresy, structures::SortedSequenceTable<std::string, Obec*>& obce);

	/// <summary> Vrati nacitany zaznam zo suboru s krajmi. </summary>
	Kraj* readFromKraje();

	/// <summary> Vrati nacitany zaznam zo suboru s okresmi. </summary>
	Okres* readFromOkresy();

	/// <summary> Vrati nacitany zaznam zo suboru s obcami. </summary>
	Obec* readFromObce();

	/// <summary> Zabezpeci bezpecne vlozenie do tabulky s obcami. V pripade duplicitneho nazvu vytvori umely kluc (pridane cislo za nazov). </summary>
	void addObec(structures::SortedSequenceTable<std::string, Obec*>& obce, Obec* obec);

private:
	/// <summary> Docasna tabulka s datami o vzdelani. K mazaniu dochadza priamo pri citani z tabulky, ked sa vytvara instancia obce. </summary>
	structures::SortedSequenceTable <std::string, structures::ArrayList<std::string*>*> educInput_;
	/// <summary> Vstupny prud zo suboru so vzdelanim. </summary>
	std::ifstream inVzdelanie;
	/// <summary> Vstupny prud zo suboru s obcami. </summary>
	std::ifstream inObce;
	/// <summary> Vstupny prud zo suboru s okresmi. </summary>
	std::ifstream inOkresy;
	/// <summary> Vstupny prud zo suboru s krajmi. </summary>
	std::ifstream inKraje;
};
