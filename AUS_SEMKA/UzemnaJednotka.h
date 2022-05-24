#pragma once
#include <string>
#include "../structures/array/array.h"
#include"../structures/list/array_list.h"
class UzemnaJednotka
{
	
protected:
	std::wstring nazov_;
	structures::Array<int>* vzdelanost_;
	std::wstring code_;
	std::wstring typUzemnejJednotky_;
	UzemnaJednotka* nadradenaUJ_;
	structures::ArrayList<UzemnaJednotka*>* podradeneUJ = new structures::ArrayList<UzemnaJednotka*>;
	int obyvatelia = 0;
	int vzdelani = 0;
public:
	UzemnaJednotka(const std::wstring nazov, const std::wstring code, std::wstring typUzemnejJednotky, structures::Array<int>* vzdelanie, UzemnaJednotka* nadradenaUJ) :
		nazov_(nazov), code_(code), typUzemnejJednotky_(typUzemnejJednotky), vzdelanost_(vzdelanie), nadradenaUJ_(nadradenaUJ)  {

	};
	~UzemnaJednotka() {
		delete vzdelanost_;
		nadradenaUJ_ = nullptr;
		for (auto p : *podradeneUJ) {
			p = nullptr;
		}
		podradeneUJ = nullptr;
	};

	const std::wstring& getName() const { return nazov_; }
	const std::wstring& getUzemnaJednotka() const { return typUzemnejJednotky_; };
	const std::wstring& getCode() const { return code_; };
	const int getVzdelanie(int i) const { return vzdelanost_->at(i); };	

	UzemnaJednotka* getNadradenaUJ()  { return nadradenaUJ_; };
	const UzemnaJednotka* getNadradenaKriterium() const { return nadradenaUJ_; };
	UzemnaJednotka* getPodradenaUJ(int i) {return podradeneUJ->at(i);};
	void setPodradena(UzemnaJednotka* podradena) { podradeneUJ->add(podradena); };
	int getPodradenaSize() { return podradeneUJ->size(); };
	void setVzdelanie(int i, int pocet) { vzdelanost_->at(i) += pocet; };
	void setNadradenaUJ(UzemnaJednotka* nadradenaUJ) { nadradenaUJ_ = nadradenaUJ; };


	void setPocetObyvatelov();
	const int getPocetObyvatelov() const { return obyvatelia; };
	const int getPocetVzdelani() const  { return vzdelani; };
};




