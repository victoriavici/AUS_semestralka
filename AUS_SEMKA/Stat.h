#pragma once
#include "UzemnaJednotka.h"
class Stat : public UzemnaJednotka {

public:;
	  Stat() :UzemnaJednotka(L"Slovensko", L"SK", L"Stat", nullptr,nullptr) {};
	  ~Stat() = default;
};
