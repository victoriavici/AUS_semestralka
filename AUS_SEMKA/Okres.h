#pragma once
#include "UzemnaJednotka.h"
class Okres : public UzemnaJednotka
{
	
public:
	Okres(const std::wstring nazov, const std::wstring code) : UzemnaJednotka(nazov, code, L"Okres", new structures::Array<int>(8), nullptr) {}
	~Okres() = default;

	
	
};