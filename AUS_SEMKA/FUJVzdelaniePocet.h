#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJVzdelaniePocet : public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	FUJVzdelaniePocet(Kriterium<UzemnaJednotka, int>* kriterium, double valueMin, double valueMax, int vzdelanieTyp);
protected:


private:
	int vzdelanieTyp_;
};