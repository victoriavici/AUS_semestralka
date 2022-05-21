#pragma once
#include "UzemnaJednotka.h"

class Obec : public UzemnaJednotka
{
public:
	Obec(const std::wstring nazov, const std::wstring code, structures::Array<int>* ar) : UzemnaJednotka(nazov, code, L"Obec", new structures::Array<int>(8), nullptr) {}
	~Obec() =default;
	

};