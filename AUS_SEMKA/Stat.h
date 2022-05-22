#pragma once

#include "UzemnaJednotka.h"

class Stat : public UzemnaJednotka {

public:;
	  Stat() :UzemnaJednotka(L"Slovensko", L"SK", L"Štát", new structures::Array<int>(8),nullptr) {};
	  ~Stat() = default;
};
