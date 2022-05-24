#include "DataLoader.h"
#include "Obec.h"
#include "Kraj.h"
#include "Okres.h"
#include"DataProcessing.h"

int main() {

	std::setlocale(LC_ALL, "sk_SK.utf8");

	auto dat = new DataLoader();
	auto obce = new structures::SortedSequenceTable<std::wstring, Obec*>;
	auto duplicityObci = new structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>;
	auto okresy = new structures::SortedSequenceTable<std::wstring, Okres*>;
	auto kraje = new structures::SortedSequenceTable<std::wstring, Kraj*>;
	auto stat = new Stat();

	dat->nacitaj(*duplicityObci, *obce, *okresy, *kraje, stat);
	auto proc = DataProcessing();
	proc.vykonajOperacie(duplicityObci, obce, okresy, kraje, stat);

	delete dat;
	for (auto k : *obce) {
		delete k->accessData();
	}
	delete obce;
	for (auto k : *duplicityObci) {
		for (auto kk : *k->accessData()) {
			delete kk;
		}
		delete k->accessData();
	}
	delete duplicityObci;
	for (auto k : *okresy) {
		delete k->accessData();
	}
	delete okresy;
	for (auto k : *kraje) {
		delete k->accessData();
	}
	delete stat;
	delete kraje;

	_CrtDumpMemoryLeaks();
	return 895;
};



