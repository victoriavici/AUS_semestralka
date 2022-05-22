#include "DataLoader.h"
#include "Obec.h"
#include "Kraj.h"
#include "Okres.h"
#include <iostream>

#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <sstream>
#include "DataLoader.h"
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include <string>

#include "KNazov.h"
#include "KUJTyp.h"
#include "KVzdelaniePocet.h"

void zakladnyVypisInfo(UzemnaJednotka* hladana) {
	KNazov knazov;
	KUJTyp ktyp;
	KVzdelaniePocet pocet;

	std::wcout << L"N�zov: " << knazov.evaluate(*hladana) << std::endl;
	std::wcout << L"Typ �zemnej jednotky: " << ktyp.evaluate(*hladana) << std::endl;
	std::wcout << L"Po�et vzdelan�ch �ud�: " << std::endl;
	std::wcout << L"   Bez ukon�enia: " << pocet.ev(*hladana, 0) << std::endl;
	std::wcout << L"   Z�kladn�: " << pocet.ev(*hladana, 1) << std::endl;
	std::wcout << L"   Stredn� odborn�: " << pocet.ev(*hladana, 2) << std::endl;
	std::wcout << L"   �pln� stredn�: " << pocet.ev(*hladana, 3) << std::endl;
	std::wcout << L"   Vy��ie odborn�: " << pocet.ev(*hladana, 4) << std::endl;
	std::wcout << L"   Vysoko�kolsk�: " << pocet.ev(*hladana, 5) << std::endl;
	std::wcout << L"   Bez �kolsk�ho vzdelania: " << pocet.ev(*hladana, 6) << std::endl;
	std::wcout << L"   Nezisten�: " << pocet.ev(*hladana, 7) << std::endl;
}


void vypisInfo(UzemnaJednotka* hladana) {
	KNazov knazov;
	KUJTyp ktyp;
	KVzdelaniePocet pocet;

	if (ktyp.evaluate(*hladana) == L"Obec") {
		zakladnyVypisInfo(hladana);
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
	}
	else if (ktyp.evaluate(*hladana) == L"Okres") {
		zakladnyVypisInfo(hladana);
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
	}
	else if (ktyp.evaluate(*hladana) == L"Kraj") {
		zakladnyVypisInfo(hladana);
		std::wcout << L"Vy��ia �zemn� jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vy��ej �zemnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
	}
	else {
		zakladnyVypisInfo(hladana);
	}
	hladana = nullptr;
}

int main() {

	std::setlocale(LC_ALL, "sk_SK.utf8");

	auto dat = new DataLoader();
	auto obce = new structures::SortedSequenceTable<std::wstring, Obec*>;
	auto duplicityObci = new structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>;
	auto okresy = new structures::SortedSequenceTable<std::wstring, Okres*>;
	auto kraje = new structures::SortedSequenceTable<std::wstring, Kraj*>;
	auto stat = new Stat();

	dat->nacitajObce(*duplicityObci, *obce);

	dat->nacitajOKres(*okresy);
	dat->nacitajKraj(*kraje);


	dat->priradUJ(*duplicityObci, *obce, *okresy, *kraje, stat);
	dat->nacitajVzdelanieOkresov(*duplicityObci, *obce);
	dat->nacitajVzdelanieKrajov(*okresy);
	dat->nacitajVzdelanieStatu(*kraje);
	stat->setPocetObyvatelov();


	std::wstring input;
	int prevmode = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wcout << L"Zadaj, �o ideme vyh�ada�: ";
	std::wcout << std::endl;
	getline(std::wcin, input);
	std::wcout << std::endl;
	_setmode(_fileno(stdin), prevmode);

	Obec* hladane = nullptr;
	Okres* hladOk = nullptr;
	Kraj* hladKraj = nullptr;
	if (obce->tryFind(input, hladane)) {
		if (hladane != nullptr)
		{
			vypisInfo(hladane);
		}
		else {
			std::wcout << L"Obci s rovn�m n�zvom existuje viac: " << std::endl;
			auto pole = duplicityObci->find(input);
			for (int i = 0; i < pole->size(); i++)
			{
				std::wcout << i+1 << ". " << pole->at(i)->getName() << " - " << pole->at(i)->getNadradenaUJ()->getName() << std::endl;
			}
			std::wcout<<std::endl;
			int cisloinput;
			std::wcout << L"Zvol si, ktor� chce�: " << std::endl;
			std::wcin >> cisloinput;
			vypisInfo(pole->at(cisloinput-1));
		}
	}
	else if (okresy->tryFind(input, hladOk)) {
		vypisInfo(hladOk);
	
	}
	else if (kraje->tryFind(input, hladKraj)) {
		vypisInfo(hladKraj);
		 
	}
	else if (input == stat->getName()) {
		vypisInfo(stat);
	}
	else {
		std::wcout << L"Zadan� slovo nie je �iadnou �zemnou jednotkou Slovenska." << std::endl;
	}
	input.~basic_string();
	



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



