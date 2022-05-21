#pragma once
#include "UzemnaJednotka.h"
#include "Stat.h"
class Kraj : public UzemnaJednotka
{

public:
	Kraj(const std::wstring nazov, const std::wstring code) :UzemnaJednotka(nazov, code, L"Kraj", new structures::Array<int>(8), nullptr) {
		
	}
	~Kraj() = default;
};