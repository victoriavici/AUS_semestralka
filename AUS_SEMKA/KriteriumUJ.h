#pragma once
#include "UzemnaJednotka.h"
#include "kriterium.h"
template<typename ResultType>
class KriteriumUJ : public Kriterium<UzemnaJednotka, ResultType> {

public:
	virtual ResultType evaluate(const UzemnaJednotka& object) = 0;
};