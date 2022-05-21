#include "Okres.h"

Okres::~Okres()
{
}

void Okres::setVzdelanie(int i, int pocet)
{
	vzdelanost_->at(i) += pocet;
}
