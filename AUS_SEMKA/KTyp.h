#pragma once
#pragma once
#include "KriteriumUJ.h"
class KTyp : public KriteriumUJ<std::wstring>
{
public:
	std::wstring evaluate(const UzemnaJednotka& object) override { return object.getUzemnaJednotka(); };
};
