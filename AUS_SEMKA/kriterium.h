#pragma once
template<typename ObjectType, typename ResultType>
class Kriterium {

public:
	virtual ResultType evaluate(const ObjectType& object);
};