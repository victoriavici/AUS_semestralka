#pragma once
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/list/linked_list.h"
#include "Obec.h"
#include "Okres.h"
#include"Kraj.h"
class DataLoader
{
public:
	DataLoader() {}
	~DataLoader() {}

	void nacitaj(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce, structures::SortedSequenceTable<std::wstring, Okres*>& okresy, structures::SortedSequenceTable<std::wstring, Kraj*>& kraje, Stat* stat);
private:
	void nacitajObce(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& zoznam);
	void nacitajOKres(structures::SortedSequenceTable<std::wstring, Okres*>& okresy);
	void nacitajKraj(structures::SortedSequenceTable<std::wstring, Kraj*>& kraje);

	void nacitajVzdelanieOkresov(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce);
	void nacitajVzdelanieKrajov(structures::SortedSequenceTable<std::wstring, Okres*>& okresy);
	void nacitajVzdelanieStatu(structures::SortedSequenceTable<std::wstring, Kraj*>& kraje);

	void priradUJ(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce, structures::SortedSequenceTable<std::wstring, Okres*>& okresy,structures::SortedSequenceTable<std::wstring, Kraj*>& kraje, Stat* stat);
};

