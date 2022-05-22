#pragma once
#include "UzemnaJednotka.h"

void UzemnaJednotka::setPocetObyvatelov()
{
	for (int i = 0; i < vzdelanost_->size(); i++)
	{
		obyvatelia += vzdelanost_->at(i);
	}
	for (int i = 0; i < 6; i++)
	{
		vzdelani += vzdelanost_->at(i);
	}
}
