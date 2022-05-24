#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
#include "KTyp.h"
class FPrislusnost: public FilterWithCriterion<UzemnaJednotka, bool> {

public:
	FPrislusnost(Kriterium<UzemnaJednotka, bool>* kriterium, std::wstring hodnota) : FilterWithCriterion(kriterium), hodnota_(hodnota) {};
protected:
	bool passFilter(bool hodnota) override
	{
		return hodnota;
	};
private:
	std::wstring hodnota_;
};