#pragma once
#include "kriterium.h"
#include "Filter.h"
template<typename ObjectType, typename ValueType>
class FilterWithCriterion : public Filter<ObjectType> {
public:
	FilterWithCriterion(Kriterium<ObjectType, ValueType>* kriterium);
	~FilterWithCriterion();
	bool pass(const ObjectType& object);
protected:
	virtual bool passFilter(ValueType value);
private:
	Kriterium<ObjectType, ValueType>* kriterium_;
};