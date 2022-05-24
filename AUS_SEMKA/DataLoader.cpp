#pragma once
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <sstream>
#include "DataLoader.h"
#include "../structures/list/array_list.h"


void DataLoader::nacitaj(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce, structures::SortedSequenceTable<std::wstring, Okres*>& okresy, structures::SortedSequenceTable<std::wstring, Kraj*>& kraje, Stat* stat)
{
    nacitajObce(duplicaty, obce);
    nacitajOKres(okresy);
    nacitajKraj(kraje);
    priradUJ(duplicaty, obce, okresy, kraje, stat);
    nacitajVzdelanieOkresov(duplicaty, obce);
    nacitajVzdelanieKrajov(okresy);
    nacitajVzdelanieStatu(kraje);
    stat->setPocetObyvatelov();
}

void DataLoader::nacitajObce(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& zoznam)
{
    std::wifstream input("../data/obce.csv");
    input.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wstring riadok;
    std::wcout.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wifstream vzdel("../data/vzdelanie.csv");
    vzdel.imbue(std::locale(vzdel.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wstring riadokvzdelania;

    getline(input, riadok);
    getline(vzdel, riadokvzdelania);
    
    int i = 0;
    while (getline(input, riadok)) {
        auto vzdelanie = new structures::Array<int>(8);
        getline(vzdel, riadokvzdelania);
        int poz = riadok.find(';');
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        std::wstring code = riadok.substr(0, poz);
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        std::wstring nazov = riadok.substr(0, poz);
        poz = riadokvzdelania.find(';');
        riadokvzdelania = riadokvzdelania.substr(poz + 1);
        poz = riadokvzdelania.find(';');
        riadokvzdelania = riadokvzdelania.substr(poz + 1);
        if (!riadokvzdelania.empty()) {
            for (int j = 0; j < 7; j++)
            {
                poz = riadokvzdelania.find(';');
                vzdelanie->at(j) = stoi(riadokvzdelania.substr(0, poz));
                riadokvzdelania = riadokvzdelania.substr(poz + 1);
            }
            vzdelanie->at(7) = stoi(riadokvzdelania);
        }
        if (!zoznam.containsKey(nazov)) {
            Obec* o = new Obec(nazov, code, new structures::Array<int>(*vzdelanie));
            o->setPocetObyvatelov();
             zoznam.insert(nazov, o);
        }
        else {
            if (zoznam.find(nazov) != nullptr) {
                auto del = zoznam.remove(nazov);
                zoznam.insert(nazov, nullptr);
                duplicaty.insert(nazov, new structures::LinkedList<Obec*>);
                duplicaty.find(nazov)->add(del);
            }
            Obec* o = new Obec(nazov, code, new structures::Array<int>(*vzdelanie));
            o->setPocetObyvatelov();
            duplicaty.find(nazov)->add(o);

        }
        delete vzdelanie;
    }
    
}

void DataLoader::nacitajOKres(structures::SortedSequenceTable<std::wstring, Okres*>& zoznam)
{
    std::wifstream input("../data/okresy.csv");
    input.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wstring riadok;
    std::wcout.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    getline(input, riadok);
    int i = 0;
    while (getline(input, riadok)) {
        int poz = riadok.find(';');
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        std::wstring code = riadok.substr(0, poz);
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        std::wstring nazov = riadok.substr(0, poz);
        zoznam.insert(nazov, (new Okres(nazov, code)));
    }
}

void DataLoader::nacitajKraj(structures::SortedSequenceTable<std::wstring, Kraj*>& zoznam)
{
    
    std::wifstream input("../data/kraje.csv");
    input.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wstring riadok;
    std::wcout.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    getline(input, riadok);
    int i = 0;
    while (getline(input, riadok)) {
        int poz = riadok.find(';');
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        riadok = riadok.substr(poz + 1);
        poz = riadok.find(';');
        std::wstring nazov = riadok.substr(0, poz);

        riadok = riadok.substr(poz + 2);
        poz = riadok.find(';');
        riadok = riadok.substr(poz + 6);
        std::wstring code = riadok.substr(0, 5);
        zoznam.insert(nazov, (new Kraj(nazov, code)));
    }
}

void DataLoader::nacitajVzdelanieOkresov(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce)
{

    for (auto o : obce) {
        if (o->accessData() != nullptr){
            for (int i = 0; i < 8; i++)
            {
                o->accessData()->getNadradenaUJ()->setVzdelanie(i, o->accessData()->getVzdelanie(i));
            }
        }
    }
    for (auto d : duplicaty) {
        for (int i = 0; i < d->accessData()->size(); i++)
        {
            for (int j = 0; j < 8; j++)
            {
                d->accessData()->at(i)->getNadradenaUJ()->setVzdelanie(j, d->accessData()->at(i)->getVzdelanie(j));
            }
        }
    }
}

void DataLoader::nacitajVzdelanieKrajov(structures::SortedSequenceTable<std::wstring, Okres*>& okresy)
{
    for (auto oo : okresy) {
        oo->accessData()->setPocetObyvatelov();
        for (int i = 0; i < 8; i++)
        {
            oo->accessData()->getNadradenaUJ()->setVzdelanie(i, oo->accessData()->getVzdelanie(i));
        }
    }

}

void DataLoader::nacitajVzdelanieStatu(structures::SortedSequenceTable<std::wstring, Kraj*>& kraje)
{

    for (auto kk : kraje) {
        kk->accessData()->setPocetObyvatelov();
        for (int i = 0; i < 8; i++)
        {
            kk->accessData()->getNadradenaUJ()->setVzdelanie(i,kk->accessData()->getVzdelanie(i));
        }
    }
}

void DataLoader::priradUJ(structures::SortedSequenceTable<std::wstring, structures::LinkedList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce, structures::SortedSequenceTable<std::wstring, Okres*>& okresy, structures::SortedSequenceTable<std::wstring, Kraj*>& kraje, Stat* stat)
{
        for (auto d : duplicaty) {
            for (int j = 0; j < d->accessData()->size(); j++) {
                for (auto oo : okresy) {
                    if (d->accessData()->at(j)->getCode().substr(0, 6) == oo->accessData()->getCode()) {
                        d->accessData()->at(j)->setNadradenaUJ(oo->accessData());
                        oo->accessData()->setPodradena(d->accessData()->at(j));
                    }
                }
            }
        }
        for (auto ob : obce) {
            if (ob->accessData() != nullptr)
            {
                for (auto oo : okresy) {
                    if (ob->accessData()->getCode().substr(0, 6) == oo->accessData()->getCode())
                    {
                        ob->accessData()->setNadradenaUJ(oo->accessData());
                        ob->accessData()->getNadradenaUJ()->setPodradena(ob->accessData());
                    }
                }
            }
        }
        for (auto o : okresy) {
            for (auto k : kraje) {
                if (o->accessData()->getCode().substr(0, 5) == k->accessData()->getCode())
                {
                    o->accessData()->setNadradenaUJ(k->accessData());
                    o->accessData()->getNadradenaUJ()->setPodradena(o->accessData());
                }
            }
        }
        for (auto k : kraje) {
            k->accessData()->setNadradenaUJ(stat);
            k->accessData()->getNadradenaUJ()->setPodradena(k->accessData());
        }
}

