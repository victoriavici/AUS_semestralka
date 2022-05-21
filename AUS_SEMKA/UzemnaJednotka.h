#pragma once
#include <string>
#include "../structures/array/array.h"
class UzemnaJednotka
{
protected:
	std::wstring nazov_;
	structures::Array<int>* vzdelanost_;
	std::wstring code_;
	std::wstring typUzemnejJednotky_;
	UzemnaJednotka* nadradenaUJ_;
	int obyvatelia = 0;
public:
	UzemnaJednotka(const std::wstring nazov, const std::wstring code, std::wstring typUzemnejJednotky, structures::Array<int>* vzdelanie, UzemnaJednotka* nadradenaUJ) :
		nazov_(nazov), code_(code), typUzemnejJednotky_(typUzemnejJednotky), vzdelanost_(vzdelanie), nadradenaUJ_(nadradenaUJ) {
	};
	~UzemnaJednotka() {
		delete vzdelanost_;
		delete nadradenaUJ_;
	};

	const std::wstring getName() const { return nazov_; }
	const std::wstring& getUzemnaJednotka() const { return typUzemnejJednotky_; };
	const std::wstring& getCode() const { return code_; };
	int getVzdelanie(int i) { return vzdelanost_->at(i); };
	UzemnaJednotka* getNadradenaUJ() { return nadradenaUJ_; };

	void setVzdelanie(int i, int pocet) { vzdelanost_->at(i) += pocet; };
	void setNadradenaUJ(UzemnaJednotka* nadradenaUJ) { nadradenaUJ_ = nadradenaUJ; };

	void pocetObyvatelov();
};



