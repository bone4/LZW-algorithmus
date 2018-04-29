/*
 * CArrayDec.hpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CArrayDec.hpp
 * \brief Definition der Klasse CArrayDec
*/

#ifndef CARRAYDEC_HPP_
#define CARRAYDEC_HPP_


#include "CDec.hpp"
#include "CArray.hpp"
#include "CEntry.hpp"
/*!
 * \class CArrayDec
 * \brief decodiert einen Zahlenvektor in einen String �ber der ASCII Tabelle in einem gro�en Array
 * Diese Klasse dient zum decodieren. Gegeben ist ein Vektor aus integer Zahlen. Berechnet wird eine Zeichenkette (String).
 * Dies geschieht �ber dem Grundw�rterbuch ASCII Tabelle. Weitere W�rterbucheintr�ge werden selbstst�ndig errechnet aus dem gegebenen Eingabevektor.
*/
class CArrayDec : protected CDec {
public:
	CArrayDec();									//!< Konstruktor
	virtual ~CArrayDec();							//!< Destruktor
	int searchInTable(const string &);				//!< Suche nach einem String im W�rterbuch (Array); R�ckgabe ist die Nummer des Arrayspeicherplatzes @param Such-String @return Array-Feld-Nummer als int
	string decode(const vector<unsigned int> &in);	//!< eigentliche Haupt-Dekodierfunktion @param Zahlenvektor @return Text als String
private:
	CArray<CEntry,LZW_DICT_SIZE> m_symbolTable;		//!< privates W�rterbucharray vom Typ CEntry
};


#endif /* CARRAYDEC_HPP_ */
