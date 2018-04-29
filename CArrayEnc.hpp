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
 * \brief encodiert einen String in einen Zahlenvektor �ber der ASCII Tabelle mit einem gro�en Array
 * Diese Klasse dient zum encodieren. Gegeben ist eine Zeichenkette (String). Berechnet wird ein Vektor aus integer Zahlen.
 * Dies geschieht �ber dem Grundw�rterbuch ASCII Tabelle. Weitere W�rterbucheintr�ge werden selbstst�ndig errechnet und dem Decoder auch nicht mitgeteilt.
 *
 * Die Klasse erbt von CEnc. Diese Klasse deklariert bereits abstrakt die encodier Funktion.
 * �ber dieser Klasse (von CLZW) wird LZW_DICT_SIZE definiert und die Methoden intToString() und charToInt() bereit gestellt.
*/
class CArrayEnc : protected CEnc {
public:
	CArrayEnc();									//!< Konstruktor
	virtual ~CArrayEnc();							//!< Destruktor
	int searchInTable(const string &);				//!< Suche nach einem String im W�rterbuch (Array); R�ckgabe ist die Nummer des Arrayspeicherplatzes @param Such-String @return Array-Feld-Nummer als int
	vector<unsigned int> encode(const string &);	//!< eigentliche encodier Funktion @param zu kodierender Text @return Zahlenvektor
private:
	CArray<CEntry,LZW_DICT_SIZE> m_symbolTable;		//!< privates W�rterbucharray vom Typ CEntry
};


#endif /* CARRAYENC_HPP_ */
