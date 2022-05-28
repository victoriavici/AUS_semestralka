#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K>
	class QuickSort : public Sort<K>
	{

	public:
		QuickSort(Kriterium<UzemnaJednotka, K>* kriterium) : kriterium_(kriterium) {};
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(ArrayList<UzemnaJednotka*>* table, bool smer) override;
	private:
		void quick(ArrayList<UzemnaJednotka*>* table, int min, int max, bool smer);
		Kriterium<UzemnaJednotka, K>* kriterium_;
	};

	template<typename K>
	inline void QuickSort<K>::sort(ArrayList<UzemnaJednotka*>* table, bool smer)
	{
		quick(table, 0, table->size() - 1, smer);
	}

	template<typename K>
	inline void QuickSort<K>::quick(ArrayList<UzemnaJednotka*>* table, int min, int max, bool smer)
	{
		auto pivot = kriterium_->evaluate(*table->at((min + max) / 2));
		auto lavy = min;
		auto pravy = max;
		do {

			if (smer) {
				while (kriterium_->evaluate(*table->at(lavy)) < pivot)
					lavy++;
				while (kriterium_->evaluate(*table->at(pravy)) > pivot)
					pravy--;
			}
			else {
				while (kriterium_->evaluate(*table->at(lavy)) > pivot)
					lavy++;
				while (kriterium_->evaluate(*table->at(pravy)) < pivot)
					pravy--;
			}
			if (lavy <= pravy) {
				Utils::swap(table->at(lavy), table->at(pravy));
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);
		if (min < pravy)
			quick(table, min, pravy, smer);
		if (lavy < max)
			quick(table, lavy, max, smer);
	}
}