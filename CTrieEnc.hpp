/*
 * CTrieEnc.hpp
 *
 *  Created on: 01.06.2015
 *      Author: niklas
 */
/*!
 * \file CTrieEnc.hpp
 * \brief Definition der Klasse CTrieEnc
*/

#ifndef CTRIEENC_HPP_
#define CTRIEENC_HPP_


#include "CEnc.hpp"
#include "CArray.hpp"
#include "CKnot.hpp"
// #include <string>, wird bereits in CEnc.hpp gemacht
/*!
 * \class CTrieEnc
 * \brief encodiert einen String in einen Zahlenvektor über der ASCII Tabelle mit Tries
 * Diese Klasse dient zum encodieren. Gegeben ist eine Zeichenkette (String). Berechnet wird ein Vektor aus integer Zahlen.
 * Dies geschieht über dem Grundwörterbuch ASCII Tabelle. Weitere Wörterbucheinträge werden selbstständig errechnet und dem Decoder auch nicht mitgeteilt.
 *
 * Die Klasse erbt von CEnc. Diese Klasse deklariert bereits abstrakt die encodier Funktion.
 * Über dieser Klasse (von CLZW) wird LZW_DICT_SIZE definiert und die Methoden intToString() und charToInt() bereit gestellt.
*/
class CTrieEnc : protected CEnc {
public:
	CTrieEnc();												//!< Konstruktor
	virtual ~CTrieEnc();									//!< Destruktor
	vector<unsigned int> encode(const std::string &text);	//!< eigentliche encodier Funktion @param zu kodierender Text @return Zahlenvektor
private:
	CArray<CKnot,LZW_DICT_SIZE> m_symbolTable;				//!< privates Wörterbucharray vom Typ CKnot
};


#endif /* CTRIEENC_HPP_ */
