#pragma once
#include "KriteriumUJ.h"
class KNazov : public KriteriumUJ<std::wstring>
{
public:
	 std::wstring evaluate(const UzemnaJednotka& object) override { return object.getName();}
};