#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJVzdelaniePodiel : public FilterWithCriterion<UzemnaJednotka, double> {

public:
	FUJVzdelaniePodiel(Kriterium<UzemnaJednotka, double>* kriterium, double hodnota, std::wstring viac) : FilterWithCriterion(kriterium) {
		hodnota_ = hodnota; viac_ = viac;
	};
protected:
	bool passFilter(double hodnota)  override {
		if (viac_ == L"v")
			return hodnota_ <= hodnota;
		return  hodnota_ >= hodnota;
	};
private:
	double hodnota_;
	std::wstring viac_;
};
