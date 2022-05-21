#pragma once
#include "UzemnaJednotka.h"
#include "kriterium.h"
template<typename ResultType>
class KriteriumUJ : public Kriterium{

public:
	virtual ResultType evaluate(const UzemnaJednotka& object) override;
};