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
    auto vzdelanie = new structures::Array<int>(8);
    int i = 0;
    while (getline(input, riadok)) {
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
            zoznam.insert(nazov, (new Obec(nazov, code, vzdelanie)));
        }
        else {
            if (zoznam.find(nazov) != nullptr) {
                auto del = zoznam.remove(nazov);
                zoznam.insert(nazov, nullptr);
                duplicaty.insert(nazov, new structures::LinkedList<Obec*>);
                duplicaty.find(nazov)->add(del);
            }
            else
            {
                duplicaty.find(nazov)->add(new Obec(nazov, code, vzdelanie));
            }
        }
    }
    delete vzdelanie;
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





void DataLoader::nacitajVzdelanieOkresov(structures::SortedSequenceTable<std::wstring, structures::ArrayList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce)
{

    for (auto o : obce) {
        for (int i = 0; i < 8; i++)
        {
            o->accessData()->getNadradenaUJ()->setVzdelanie(i, o->accessData()->getVzdelanie(i));
        }
    }
    for (auto d : duplicaty) {
        for (int i = 0; i < d->accessData()->size(); i++)
        {
            for (int j = 0; j < 8; j++)
            {
                d->accessData()->at(i)->getNadradenaUJ()->setVzdelanie(i, d->accessData()->at(i)->getVzdelanie(j));
            }
        }
    }


    //for (auto oo : okresy) {
    //    for (auto zo : obce) {

    //        if (zo->accessData() != nullptr) {
    //            if (zo->accessData()->getNadradenaUJ()->getCode() == oo->accessData()->getCode()) {
    //                for (int i = 0; i < 8; i++)
    //                {
    //                    oo->accessData()->setVzdelanie(i, zo->accessData()->getVzdelanie(i));
    //                }
    //            }
    //        }
    //        else {
    //            for (auto dd : duplicaty) {
    //                for (int j = 0; j < dd->accessData()->size(); j++) {
    //                    if (dd->accessData()->at(j)->getNadradenaUJ()->getCode() == oo->accessData()->getCode()) {
    //                        for (int i = 0; i < 8; i++)
    //                        {
    //                            oo->accessData()->setVzdelanie(i, dd->accessData()->at(j)->getVzdelanie(i));
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}

}

void DataLoader::nacitajVzdelanieKrajov(structures::SortedSequenceTable<std::wstring, Okres*>& okresy)
{
   /* for (auto kk : kraje) {
        for (auto oo : okresy)
        {
            
            if (oo->accessData()->getNadradenaUJ()->getCode() == kk->accessData()->getCode()) {
                for (int i = 0; i < 8; i++)
                {
                    kk->accessData()->setVzdelanie(i, oo->accessData()->getVzdelanie(i));
                }
            }
        }
    }*/

    for (auto oo : okresy) {
        for (int i = 0; i < 8; i++)
        {
            oo->accessData()->getNadradenaUJ()->setVzdelanie(i, oo->accessData()->getVzdelanie(i));
        }
    }

}

void DataLoader::nacitajVzdelanieStatu(structures::SortedSequenceTable<std::wstring, Kraj*>& kraje)
{

    for (auto kk : kraje) {
        for (int i = 0; i < 8; i++)
        {
            kk->accessData()->getNadradenaUJ()->setVzdelanie(i,kk->accessData()->getVzdelanie(i));
        }
    }
}

void DataLoader::priradUJ(structures::SortedSequenceTable<std::wstring, structures::ArrayList<Obec*>*>& duplicaty, structures::SortedSequenceTable<std::wstring, Obec*>& obce, structures::SortedSequenceTable<std::wstring, Okres*>& okresy, structures::SortedSequenceTable<std::wstring, Kraj*>& kraje, Stat* stat)
{
    for (auto k : kraje) {
        k->accessData()->setNadradenaUJ(stat);
    }

    for (auto o : okresy) {
        o->accessData()->setNadradenaUJ(kraje.find(o->accessData()->getCode().substr(0, 5)));
    }
    

    for (auto ob : obce) {
        if(ob->accessData() != nullptr)
        ob->accessData()->setNadradenaUJ(okresy.find(ob->accessData()->getCode().substr(0, 6)));
    }
    for (auto d : duplicaty) {
            for (int j = 0; j < d->accessData()->size(); j++) {
                 d->accessData()->at(j)->setNadradenaUJ(okresy.find(d->accessData()->at(j)->getCode().substr(0, 6)));
            }
        }
}

