#pragma once
#include "FIlterWithCriterion.h"
#include "UzemnaJednotka.h"
class FUJVzdelaniePodiel : public FilterWithCriterion<UzemnaJednotka, std::wstring> {

private:
	FUJVzdelaniePodiel(Kriterium<UzemnaJednotka, int>* kriterium, double valueMin, double valueMax, int vzdelanieTyp);
protected:
	//bool passFilter(double hodnota) override;
private:
	int vzdelanieTyp_;
};
