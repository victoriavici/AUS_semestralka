#pragma once
#include "KriteriumUJ.h"
class KVzdelaniePocet : public KriteriumUJ<int>
{
public:
	int evaluate(const UzemnaJednotka& object) override { return object.getPocetVzdelani(); };
	int ev(const UzemnaJednotka& object, int i) {
		return object.getVzdelanie(i);
	};
};