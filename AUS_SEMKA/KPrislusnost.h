#pragma once
#include "KriteriumUJ.h"
class KPrislusnost : public KriteriumUJ<bool>
{
private:
	std::wstring nazov_;
public:
	KPrislusnost(std::wstring nazov) : KriteriumUJ(), nazov_(nazov) {};
	bool evaluate(const UzemnaJednotka& object) override {
		if (object.getNadradenaKriterium() != nullptr) {
			if (object.getNadradenaKriterium()->getName() == nazov_) {
				return true;
			}
			else {
				
				auto object1 = object.getNadradenaKriterium();
				
				evaluate(*object1);
			}
		}
		return false;
	}
	
};