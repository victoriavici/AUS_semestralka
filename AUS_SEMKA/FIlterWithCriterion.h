#pragma once
#include "kriterium.h"
#include "Filter.h"
template<typename ObjectType, typename ValueType>
class FilterWithCriterion : public Filter<ObjectType> {
public:
	FilterWithCriterion(Kriterium<ObjectType, ValueType>* kriterium) : kriterium_(kriterium) {};
	~FilterWithCriterion() { delete kriterium_; };
	bool pass(const ObjectType& object) { return passFilter(kriterium_->evaluate(object)); };
protected:
	virtual bool passFilter(ValueType value)=0;
private:
	Kriterium<ObjectType, ValueType>* kriterium_;
};