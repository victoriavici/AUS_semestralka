#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJVzdelaniePocet : public FilterWithCriterion<UzemnaJednotka, int> {

public:
	FUJVzdelaniePocet(Kriterium<UzemnaJednotka, int>* kriterium, int hodnota, std::wstring viac) : FilterWithCriterion(kriterium) {
		hodnota_ = hodnota; viac_ = viac;
	};
protected:
	bool passFilter(int hodnota)  override {
		if (viac_ == L"v") {
			return hodnota_ <= hodnota;
		}
		return hodnota_ >= hodnota;
	};
private:
	int hodnota_;
	std::wstring viac_;
};