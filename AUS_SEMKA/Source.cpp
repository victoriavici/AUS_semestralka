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


int main() {
	std::setlocale(LC_ALL, "sk_SK.utf8");

	/*std::wstring str;
	int prevmode = _setmode(_fileno(stdout));
	std::wcin >> str;
	_setmode(_fileno(stdin));*/


	//int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);

	/*_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin), _O_WTEXT);*/

	//setlocale(getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	auto dat = new DataLoader();
	auto obce = new structures::SortedSequenceTable<std::wstring, Obec*>;
	auto duplicatyObci = new structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>;
	auto okresy = new structures::SortedSequenceTable<std::wstring, Okres*>;
	auto kraje = new structures::SortedSequenceTable<std::wstring, Kraj*>;
	auto stat = new Stat();

	dat->nacitajObce(*duplicatyObci, *obce);
	dat->nacitajOKres(*okresy);
	dat->nacitajKraj(*kraje);


	//int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);

	std::wcout.imbue(std::locale(std::wcout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

	//for (auto o : *obce) {
	//	std::wcout << "ý ž";
	//	//std::wcout << o->accessData()->getName() << "\n";
	//}
	//
//	_setmode(_fileno(stdout), prevmode);

	/*dat->priradUJ(*duplicatyObci, *obce, *okresy, *kraje, stat);
	dat->nacitajVzdelanieOkresov(*duplicatyObci, *obce);
	dat->nacitajVzdelanieKrajov(*okresy);
	dat->nacitajVzdelanieStatu(*kraje);*/
	/*
		for (auto k : *kraje) {
			for (int i = 0; i < 8; i++)
			{
				std::wcout << k->accessData()->getName() << ": " << k->accessData()->getVzdelanie(i) << std::endl;
			}
		}*/

	delete dat;
	for (auto k : *obce) {
		delete k->accessData();
	}
	delete obce;
	for (auto k : *duplicatyObci) {
		for (auto kk : *k->accessData()) {
			delete kk;
		}
		delete k->accessData();
	}
	delete duplicatyObci;
	for (auto k : *okresy) {
		delete k->accessData();
	}
	delete okresy;
	for (auto k : *kraje) {
		delete k->accessData();
	}
	delete kraje;
	delete stat;

	_CrtDumpMemoryLeaks();
	return 895;
};