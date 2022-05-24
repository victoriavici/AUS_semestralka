#pragma once
#include "KriteriumUJ.h"
class KVzdelaniePocet : public KriteriumUJ<int>
{
private:
	int i_;
public:
	KVzdelaniePocet(int i) : KriteriumUJ(), i_(i) {};
	int evaluate(const UzemnaJednotka& object) override { return object.getVzdelanie(i_); };
};