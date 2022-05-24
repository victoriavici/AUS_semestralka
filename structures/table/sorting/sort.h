#pragma once

#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie NonortedSequenceTable navrhnuté ako funkèný objekt. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K>
	class Sort
	{
	public:

		/// <summary> Destruktor. </summary>
		virtual ~Sort();

		/// <summary> Funkcny operator utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		/// <remarks> Využíva metódu sort. </remarks>
		void operator()(ArrayList<UzemnaJednotka*>& table);

		/// <summary> Utriedi utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		virtual void sort(ArrayList<UzemnaJednotka*>* table, bool smer) = 0;
	};

	template<typename K>
	inline Sort<K>::~Sort()
	{
	}

	template<typename K>
	inline void Sort<K>::operator()(ArrayList<UzemnaJednotka*>& table)
	{
		this->sort(table);
	}
}