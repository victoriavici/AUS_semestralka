#pragma once
#pragma once
#include "KriteriumUJ.h"
class KUJTyp : public KriteriumUJ<std::wstring>
{

	std::wstring evaluate(const UzemnaJednotka& object) override { return object.getUzemnaJednotka(); }
};
