#pragma once
#include "KriteriumUJ.h"
#include "KVzdelaniePocet.h"
class KVzdelaniePodiel : public KriteriumUJ<double>
{
private:
	int i_;
public:
	KVzdelaniePodiel(int i) : KriteriumUJ(), i_(i) {};
	double evaluate(const UzemnaJednotka& object) override { return 100 * (static_cast<double>(KVzdelaniePocet(i_).evaluate(object)) / static_cast<double>(object.getPocetObyvatelov())); };
};
