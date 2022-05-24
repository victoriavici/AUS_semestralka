#pragma once
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include "Obec.h"
#include "Kraj.h"
#include "Okres.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include "../structures/table/sorted_sequence_table.h"

#include "KNazov.h"
#include "KTyp.h"
#include "KVzdelaniePocet.h"
#include "FTyp.h"
#include "FVzdelaniePocet.h"
#include "KPrislusnost.h"
#include "FPrislusnost.h"
#include "KVzdelaniePodiel.h"
#include "FVzdelaniePodiel.h"

#include "../structures/table/sorting/sort.h"
#include "../structures/table/sorting/quick_sort.h"
class DataProcessing
{
public:
	DataProcessing() {};
	~DataProcessing() {};
	void vykonajOperacie(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat);
private:
	void zakladnyVypis(UzemnaJednotka* hladana);
	void vzdelanieVypisInfo(UzemnaJednotka* hladana);
	void podielVypisInfo(UzemnaJednotka* hladana);
	void vypisInfo(UzemnaJednotka* hladana, bool vzdel);
	void bodoveVyhladavanie(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat);
	void filtrovanieUzemnaJednotka(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane);
	void filtrovanieVzdelaniePocet(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane);
	void filtrovaniePrislusnost(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane);
	void filtrovanieVzdelaniePodiel(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane);
	void triedenie(structures::ArrayList<UzemnaJednotka*>* vyfiltrovane);
};

