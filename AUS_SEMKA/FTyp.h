#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
#include "KTyp.h"
class FTyp : public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	std::wstring hodnota_;
public:
	FTyp(Kriterium<UzemnaJednotka, std::wstring>* kriterium, std::wstring hodnota) : FilterWithCriterion(kriterium) { hodnota_ = hodnota; };

protected:
	bool passFilter(std::wstring hodnota)  override {
		return hodnota == hodnota_;
	};

};