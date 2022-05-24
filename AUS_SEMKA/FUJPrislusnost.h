#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
#include "KUJTyp.h"
class FUJPrislusnost: public FilterWithCriterion<UzemnaJednotka, bool> {

public:
	FUJPrislusnost(Kriterium<UzemnaJednotka, bool>* kriterium, std::wstring hodnota) : FilterWithCriterion(kriterium), hodnota_(hodnota) {};
protected:
	bool passFilter(bool hodnota) override
	{
		return hodnota;
	};
private:
	std::wstring hodnota_;
};