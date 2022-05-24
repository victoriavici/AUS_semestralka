#include "Dataprocessing.h"

void DataProcessing::vykonajOperacie(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat)
{
	std::wstring operacia;
	do {
		do {
			std::wcout << L"Vyber, èo chceš robi: " << std::endl;
			std::wcout << L"1 - Bodové vyh¾adávanie " << std::endl;
			std::wcout << L"2 - Filtrovanie " << std::endl;

			getline(std::wcin, operacia);
		} while (operacia != L"1" && operacia != L"2");

		if (operacia == L"1") {
			bodoveVyhladavanie(obce, duplicityObci, okresy, kraje, stat);
		}
		else {
			bool uzfiltrovane = false;
			bool vek = false;
			auto vyfiltrovane = new structures::ArrayList<UzemnaJednotka*>;
			std::wcout << L"Filtrova pod¾a: " << std::endl;
			std::wcout << L"Typ územnej jednotky (0/1): " << std::endl;
			std::wstring o;
			getline(std::wcin, o);
			if (o == L"1") {
				filtrovanieUzemnaJednotka(obce, duplicityObci, okresy, kraje, stat, *vyfiltrovane);
				uzfiltrovane = true;
			}
			std::wcout << L"Poèet ¾udí vo vzdelanostnej skupine (0/1)" << std::endl;
			getline(std::wcin, o);
			if (o == L"1") {
				vek = true;
				filtrovanieVzdelaniePocet(obce, duplicityObci, okresy, kraje, stat, *vyfiltrovane, uzfiltrovane);
				uzfiltrovane = true;
			}
			std::wcout << L"Príslušnos k územnej jednotke (0/1)" << std::endl;
			getline(std::wcin, o);
			if (o == L"1") {
				filtrovaniePrislusnost(obce, duplicityObci, okresy, kraje, stat, *vyfiltrovane, uzfiltrovane);
				uzfiltrovane = true;
			}
			std::wcout << L"Podiel ¾udí vo vzdelanostnej skupine (0/1)" << std::endl;
			getline(std::wcin, o);
			bool podiel = false;
			if (o == L"1") {
				podiel = true;
				filtrovanieVzdelaniePodiel(obce, duplicityObci, okresy, kraje, stat, *vyfiltrovane, uzfiltrovane);
				uzfiltrovane = true;
			}
			if (vyfiltrovane->size() != 0) {

				std::wcout << L"Chceš utriedi výsledky? (0/1)" << std::endl;
				std::wstring tried;
				getline(std::wcin, tried);
				if (tried == L"1") {
					triedenie(vyfiltrovane);
				}

				for (int i = 0; i < vyfiltrovane->size(); i++)
				{
					vypisInfo(vyfiltrovane->at(i), vek);
					if (podiel) {
						podielVypisInfo(vyfiltrovane->at(i));
					}
					std::wcout << std::endl;
				}
			}
			else {
				std::wcout << std::endl;
				std::wcout << "Zadaným filtorm nevyhovuje žiadna územna jednotka :(" << std::endl;
				std::wcout << std::endl;
			}
			delete vyfiltrovane;
		}
		std::wcout << L"Chceš ešte nieèo? (0/1)" << std::endl;
		getline(std::wcin, operacia);
		std::wcout << std::endl;
	} while (operacia == L"1");

}

void DataProcessing::zakladnyVypis(UzemnaJednotka* hladana) {
	KNazov knazov;
	KTyp ktyp;

	std::wcout << L"Názov: " << knazov.evaluate(*hladana) << std::endl;
	std::wcout << L"Typ územnej jednotky: " << ktyp.evaluate(*hladana) << std::endl;
}

void DataProcessing::vzdelanieVypisInfo(UzemnaJednotka* hladana) {

	std::wcout << L"Poèet vzdelaných ¾udí: " << std::endl;
	KVzdelaniePocet pocet0(0);
	std::wcout << L"   Bez ukonèenia: " << pocet0.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet1(1);
	std::wcout << L"   Základné: " << pocet1.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet2(2);
	std::wcout << L"   Stredné odborné: " << pocet2.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet3(3);
	std::wcout << L"   Úplné stredné: " << pocet3.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet4(4);
	std::wcout << L"   Vyššie odborné: " << pocet4.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet5(5);
	std::wcout << L"   Vysokoškolské: " << pocet5.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet6(6);
	std::wcout << L"   Bez školského vzdelania: " << pocet6.evaluate(*hladana) << std::endl;
	KVzdelaniePocet pocet7(7);
	std::wcout << L"   Nezistené: " << pocet7.evaluate(*hladana) << std::endl;
}

void DataProcessing::podielVypisInfo(UzemnaJednotka* hladana) {
	std::wcout << L"Poèet vzdelaných ¾udí: " << std::endl;
	KVzdelaniePodiel pocet0(0);
	std::wcout << L"   Bez ukonèenia: " << pocet0.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet1(1);
	std::wcout << L"   Základné: " << pocet1.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet2(2);
	std::wcout << L"   Stredné odborné: " << pocet2.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet3(3);
	std::wcout << L"   Úplné stredné: " << pocet3.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet4(4);
	std::wcout << L"   Vyššie odborné: " << pocet4.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet5(5);
	std::wcout << L"   Vysokoškolské: " << pocet5.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet6(6);
	std::wcout << L"   Bez školského vzdelania: " << pocet6.evaluate(*hladana) << "%" << std::endl;
	KVzdelaniePodiel pocet7(7);
	std::wcout << L"   Nezistené: " << pocet7.evaluate(*hladana) << "%" << std::endl;
}

void DataProcessing::vypisInfo(UzemnaJednotka* hladana, bool vzdel) {
	KNazov knazov;
	KTyp ktyp;

	if (ktyp.evaluate(*hladana) == L"Obec") {
		zakladnyVypis(hladana);
		if (vzdel)
			vzdelanieVypisInfo(hladana);
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
	}
	else if (ktyp.evaluate(*hladana) == L"Okres") {
		zakladnyVypis(hladana);
		if (vzdel)
			vzdelanieVypisInfo(hladana);
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()->getNadradenaUJ()) << std::endl;
	}
	else if (ktyp.evaluate(*hladana) == L"Kraj") {
		zakladnyVypis(hladana);
		if (vzdel)
			vzdelanieVypisInfo(hladana);
		std::wcout << L"Vyššia územná jednotka: " << knazov.evaluate(*hladana->getNadradenaUJ()) << std::endl;
		std::wcout << L"Typ vyššej územnej jednotky: " << ktyp.evaluate(*hladana->getNadradenaUJ()) << std::endl;
	}
	else {
		zakladnyVypis(hladana);
		if (vzdel)
			vzdelanieVypisInfo(hladana);
	}
	hladana = nullptr;
}


void DataProcessing::bodoveVyhladavanie(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat) {
	std::wstring input;
	int prevmode = _setmode(_fileno(stdin), _O_U16TEXT);
	do {
		std::wcout << L"Zadaj, èo ideme vyh¾ada: ";
		std::wcout << std::endl;
		getline(std::wcin, input);
	} while (input.empty());
	std::wcout << std::endl;
	_setmode(_fileno(stdin), prevmode);

	Obec* hladane = nullptr;
	Okres* hladOk = nullptr;
	Kraj* hladKraj = nullptr;
	if (obce->tryFind(input, hladane)) {
		if (hladane != nullptr)
		{
			vypisInfo(hladane, true);
		}
		else {
			std::wcout << L"Obci s rovným názvom existuje viac: " << std::endl;
			auto pole = duplicityObci->find(input);
			for (int i = 0; i < pole->size(); i++)
			{
				std::wcout << i + 1 << ". " << pole->at(i)->getName() << " - " << pole->at(i)->getNadradenaUJ()->getName() << std::endl;
			}
			std::wcout << std::endl;
			int cisloinput;
			do {
				std::wcout << L"Zvol si, ktorú chceš: " << std::endl;
				std::wcin >> cisloinput;
			} while (cisloinput < 1 || cisloinput >= pole->size());
			vypisInfo(pole->at(cisloinput - 1), true);
		}
	}
	else if (okresy->tryFind(input, hladOk)) {
		vypisInfo(hladOk, true);

	}
	else if (kraje->tryFind(input, hladKraj)) {
		vypisInfo(hladKraj, true);

	}
	else if (input == stat->getName()) {
		vypisInfo(stat, true);
	}
	else {
		std::wcout << std::endl;
		std::wcout << L"Zadané slovo nie je žiadnou územnou jednotkou Slovenska." << std::endl;
	}
	input.~basic_string();
}


void DataProcessing::filtrovanieUzemnaJednotka(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane) {
	std::wstring input;
	do {
		std::wcout << L"Zadaj typ územnej jednotky (obec, okres, kraj, stat):" << std::endl;
		getline(std::wcin, input);
		std::wcout << std::endl;
	} while (input != L"okres" && input != L"kraj" && input != L"obec" && input != L"stat");
	if (input == L"obec") {
		for (auto o : *obce) {
			vyfiltrovane.add(o->accessData());
		}
		for (auto d : *duplicityObci) {
			for (int i = 0; i < d->accessData()->size(); i++)
			{
				vyfiltrovane.add(d->accessData()->at(i));
			}
		}
	}
	else if (input == L"okres") {
		for (auto o : *okresy) {
			vyfiltrovane.add(o->accessData());
		}
	}
	else if (input == L"kraj") {
		for (auto k : *kraje) {
			vyfiltrovane.add(k->accessData());
		}
	}
	else if (input == L"stat") {
		vyfiltrovane.add(stat);
	}
}

void DataProcessing::filtrovanieVzdelaniePocet(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane) {
	std::wstring typ;
	do {
		std::wcout << L"Zadaj typ vzdelania (1-8): " << std::endl;
		getline(std::wcin, typ);
	} while (typ != L"1" && typ != L"2" && typ != L"3" && typ != L"4" && typ != L"5" && typ != L"6" && typ != L"7" && typ != L"8");
	std::wstring pocet;
	do {
		std::wcout << L"Zadaj poèet: " << std::endl;
		getline(std::wcin, pocet);
	} while (pocet.empty());
	std::wstring viac;
	do {
		std::wcout << L"Chceš viac èi menej (v/m): " << std::endl;
		getline(std::wcin, viac);
	} while (viac != L"v" || viac != L"m");

	KVzdelaniePocet* kvzdel = new KVzdelaniePocet(stoi(typ) - 1);
	auto vzdel = new FVzdelaniePocet(kvzdel, stoi(pocet), viac);

	if (!uzfiltrovane) {
		if (viac == L"v") {
			if (vzdel->pass(*stat)) {
				vyfiltrovane.add(stat); // stat
				for (auto k : *kraje) {
					if (vzdel->pass(*k->accessData())) { //kraje
						vyfiltrovane.add(k->accessData());
						for (int i = 0; i < k->accessData()->getPodradenaSize(); i++)
						{
							if (vzdel->pass(*k->accessData()->getPodradenaUJ(i))) {// okres
								vyfiltrovane.add(k->accessData()->getPodradenaUJ(i));
								for (int j = 0; j < k->accessData()->getPodradenaUJ(i)->getPodradenaSize(); j++)
								{
									if (vzdel->pass(*k->accessData()->getPodradenaUJ(i)->getPodradenaUJ(j))) {
										vyfiltrovane.add(k->accessData()->getPodradenaUJ(i)->getPodradenaUJ(j)); // dzedzina
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if (vzdel->pass(*stat)) {
				vyfiltrovane.add(stat);
			}
			for (auto k : *kraje) {
				if (vzdel->pass(*k->accessData()))
					vyfiltrovane.add(k->accessData());
			}
			for (auto k : *okresy) {
				if (vzdel->pass(*k->accessData())) {
					vyfiltrovane.add(k->accessData());
				}
			}
			for (auto k : *obce) {
				if (k->accessData() != nullptr) {
					if (vzdel->pass(*k->accessData())) {
						vyfiltrovane.add(k->accessData());
					}
				}
			}
			for (auto k : *duplicityObci) {
				for (int i = 0; i < k->accessData()->size(); i++)
				{
					if (vzdel->pass(*k->accessData()->at(i))) {
						vyfiltrovane.add(k->accessData()->at(i));
					}
				}
			}
		}
	}
	else {
		auto pom = new structures::ArrayList<UzemnaJednotka*>;
		for (auto v : vyfiltrovane)
		{
			if (vzdel->pass(*v)) {
				pom->add(v);
			}
		}
		vyfiltrovane.clear();
		vyfiltrovane.assign(*pom);
		delete pom;
	}

}


void DataProcessing::filtrovaniePrislusnost(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane) {
	std::wstring input;
	do {
		std::wcout << L"Zadaj územnú jednotku:" << std::endl;
		int prevmode = _setmode(_fileno(stdin), _O_U16TEXT);

		getline(std::wcin, input);
		std::wcout << std::endl;
		_setmode(_fileno(stdin), prevmode);
	} while (input.empty());

	auto kp = new KPrislusnost(input);
	auto prislusnot = new FPrislusnost(kp, input);
	if (vyfiltrovane.size() == 0) {
		if (prislusnot->pass(*stat)) {
			vyfiltrovane.add(stat);
		}
		for (auto k : *kraje) {
			if (prislusnot->pass(*k->accessData())) {
				vyfiltrovane.add(k->accessData());
			}
		}
		for (auto k : *okresy) {
			if (prislusnot->pass(*k->accessData())) {
				vyfiltrovane.add(k->accessData());
			}
		}
		for (auto k : *obce) {
			if (k->accessData() != nullptr) {
				if (prislusnot->pass(*k->accessData())) {
					vyfiltrovane.add(k->accessData());
				}
			}
		}
		for (auto k : *duplicityObci) {
			for (int i = 0; i < k->accessData()->size(); i++)
			{
				if (prislusnot->pass(*k->accessData()->at(i))) {
					vyfiltrovane.add(k->accessData()->at(i));
				}
			}
		}
	}
	else {
		auto pom = new structures::ArrayList<UzemnaJednotka*>;
		for (auto v : vyfiltrovane)
		{
			if (prislusnot->pass(*v)) {
				pom->add(v);
			}
		}
		vyfiltrovane.clear();
		vyfiltrovane.assign(*pom);
		delete pom;
	}

}

void DataProcessing::filtrovanieVzdelaniePodiel(structures::SortedSequenceTable<std::wstring, Obec*>* obce, structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>* duplicityObci, structures::SortedSequenceTable<std::wstring, Okres*>* okresy, structures::SortedSequenceTable<std::wstring, Kraj*>* kraje, Stat* stat, structures::ArrayList<UzemnaJednotka*>& vyfiltrovane, bool uzfiltrovane) {
	std::wstring typ;
	do {
		std::wcout << L"Zadaj typ vzdelania (1-8): " << std::endl;
		getline(std::wcin, typ);
	} while (typ != L"1" && typ != L"2" && typ != L"3" && typ != L"4" && typ != L"5" && typ != L"6" && typ != L"7" && typ != L"8");
	std::wstring pocet;
	do {
		std::wcout << L"Zadaj poèet percent: " << std::endl;
		getline(std::wcin, pocet);

	} while (pocet.empty());
	std::wstring viac;
	do {
		std::wcout << L"Chceš viac èi menej (v/m): " << std::endl;
		getline(std::wcin, viac);
	} while (viac != L"v" && viac != L"m");


	KVzdelaniePodiel* kvzdel = new KVzdelaniePodiel((stoi(typ)) - 1);
	auto vzdel = new FVzdelaniePodiel(kvzdel, static_cast<double>(stoi(pocet)), viac);

	if (!uzfiltrovane) {
		if (viac == L"v") {
			if (vzdel->pass(*stat)) {
				vyfiltrovane.add(stat); // stat
				for (auto k : *kraje) {
					if (vzdel->pass(*k->accessData())) { //kraje
						vyfiltrovane.add(k->accessData());
						for (int i = 0; i < k->accessData()->getPodradenaSize(); i++)
						{
							if (vzdel->pass(*k->accessData()->getPodradenaUJ(i))) {// okres
								vyfiltrovane.add(k->accessData()->getPodradenaUJ(i));
								for (int j = 0; j < k->accessData()->getPodradenaUJ(i)->getPodradenaSize(); j++)
								{
									if (vzdel->pass(*k->accessData()->getPodradenaUJ(i)->getPodradenaUJ(j))) {
										vyfiltrovane.add(k->accessData()->getPodradenaUJ(i)->getPodradenaUJ(j)); // dzedzina
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if (vzdel->pass(*stat)) {
				vyfiltrovane.add(stat);
			}
			for (auto k : *kraje) {
				if (vzdel->pass(*k->accessData()))
					vyfiltrovane.add(k->accessData());
			}
			for (auto k : *okresy) {
				if (vzdel->pass(*k->accessData())) {
					vyfiltrovane.add(k->accessData());
				}
			}
			for (auto k : *obce) {
				if (k->accessData() != nullptr) {
					if (vzdel->pass(*k->accessData())) {
						vyfiltrovane.add(k->accessData());
					}
				}
			}
			for (auto k : *duplicityObci) {
				for (int i = 0; i < k->accessData()->size(); i++)
				{
					if (vzdel->pass(*k->accessData()->at(i))) {
						vyfiltrovane.add(k->accessData()->at(i));
					}
				}
			}
		}
	}
	else {
		auto pom = new structures::ArrayList<UzemnaJednotka*>;
		for (auto v : vyfiltrovane)
		{
			if (vzdel->pass(*v)) {
				pom->add(v);
			}
		}
		vyfiltrovane.clear();
		vyfiltrovane.assign(*pom);
		delete pom;
	}
}
void DataProcessing::triedenie(structures::ArrayList<UzemnaJednotka*>* vyfiltrovane) {
	std::wstring tried;

	std::wcout << L"Vzostupne(0) èi zostupne (1)" << std::endl;
	getline(std::wcin, tried);
	bool smer = false;
	if (tried == L"0") {
		smer = true;
	}
	else {
		smer = false;
	}
	do {
		std::wcout << L"Pod¾a nazvu (1)" << std::endl;
		std::wcout << L"Pod¾a poètu obyvate¾ov vzdelanostnej skupiny (2)" << std::endl;
		std::wcout << L"Pod¾a podielu obyvate¾ov vzdelanostnej skupiny (3)" << std::endl;
		getline(std::wcin, tried);
	} while (tried != L"1" && tried != L"2" && tried != L"3");
	if (tried == L"1") {
		KNazov* kn = new KNazov;

		auto kvik = structures::QuickSort<std::wstring>(kn);
		kvik.sort(vyfiltrovane, smer);

	}
	if (tried == L"2") {
		do {
			std::wcout << L"vyber si vzdelanostnú skupinu (1-8): " << std::endl;
			getline(std::wcin, tried);
		} while (tried != L"1" && tried != L"2" && tried != L"3" && tried != L"4" && tried != L"5" && tried != L"6" && tried != L"7" && tried != L"8");
		KVzdelaniePocet* kv = new KVzdelaniePocet(stoi(tried));
		auto kvik = structures::QuickSort<int>(kv);
		kvik.sort(vyfiltrovane, smer);

	}
	if (tried == L"3") {
		do {
			std::wcout << L"vyber si vzdelanostnú skupinu (1-8): " << std::endl;
			getline(std::wcin, tried);
		} while (tried != L"1" && tried != L"2" && tried != L"3" && tried != L"4" && tried != L"5" && tried != L"6" && tried != L"7" && tried != L"8");
		KVzdelaniePodiel* kv = new KVzdelaniePodiel(stoi(tried));
		auto kvik = structures::QuickSort<double>(kv);
		kvik.sort(vyfiltrovane, smer);
	}
}