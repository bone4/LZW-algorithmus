/*
 * CArrayEnc.hpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CArrayEnc.hpp
 * \brief Definition der Klasse CArrayEnc
*/

#ifndef CARRAYENC_HPP_
#define CARRAYENC_HPP_


#include "CEnc.hpp"
#include "CArray.hpp"
#include "CEntry.hpp"
/*!
 * \class CArrayEnc
 * \brief encodiert einen String in einen Zahlenvektor über der ASCII Tabelle mit einem großen Array
 * Diese Klasse dient zum encodieren. Gegeben ist eine Zeichenkette (String). Berechnet wird ein Vektor aus integer Zahlen.
 * Dies geschieht über dem Grundwörterbuch ASCII Tabelle. Weitere Wörterbucheinträge werden selbstständig errechnet und dem Decoder auch nicht mitgeteilt.
 *
 * Die Klasse erbt von CEnc. Diese Klasse deklariert bereits abstrakt die encodier Funktion.
 * Über dieser Klasse (von CLZW) wird LZW_DICT_SIZE definiert und die Methoden intToString() und charToInt() bereit gestellt.
*/
class CArrayEnc : protected CEnc {
public:
	CArrayEnc();									//!< Konstruktor
	virtual ~CArrayEnc();							//!< Destruktor
	int searchInTable(const string &);				//!< Suche nach einem String im Wörterbuch (Array); Rückgabe ist die Nummer des Arrayspeicherplatzes @param Such-String @return Array-Feld-Nummer als int
	vector<unsigned int> encode(const string &);	//!< eigentliche encodier Funktion @param zu kodierender Text @return Zahlenvektor
private:
	CArray<CEntry,LZW_DICT_SIZE> m_symbolTable;		//!< privates Wörterbucharray vom Typ CEntry
};


#endif /* CARRAYENC_HPP_ */
