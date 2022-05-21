#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJTyp : public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	FUJTyp(Kriterium<UzemnaJednotka, std::wstring>* kriterium, std::wstring hodnota);

};