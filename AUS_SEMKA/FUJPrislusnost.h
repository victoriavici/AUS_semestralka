#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJPrislusnost: public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	FUJPrislusnost(Kriterium<UzemnaJednotka, std::wstring>* kriterium, std::wstring hodnota);

};