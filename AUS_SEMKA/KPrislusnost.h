#pragma once
#include "KriteriumUJ.h"
class KPrislusnost : public KriteriumUJ<bool>
{
public:
	bool evaluate(const UzemnaJednotka& object) override { return false; }
	bool ev(const UzemnaJednotka& object, std::wstring nazov) {
		if (object.getNadradenaUJ() != nullptr) {
			if (object.getNadradenaUJ()->getName() == nazov) {
				return true;
			}
			else {
				ev(object, nazov);
			}
		}
		return false;
	}
};