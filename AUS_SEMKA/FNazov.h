#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FNazov : public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	FNazov(Kriterium<UzemnaJednotka, std::wstring>* kriterium, std::wstring hodnota);

public:
	//bool FilterWithCriterion::pass(const UzemnaJednotka& object) override { return passFilter(kriterium->evaluate(object)); }
};