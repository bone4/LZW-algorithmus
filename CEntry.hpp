/*
 * CEntry.hpp
 *
 *  Created on: 27.04.2015
 *      Author: cge0496
 */
/*!
 * \file CEntry.hpp
 * \brief Definition der Klasse CEntry
*/

#ifndef CENTRY_HPP_
#define CENTRY_HPP_


#include <string>
/*!
 * \class CEntry
 * \brief String-Speicher
 * Eine Klasse, die Getter und Setter Methoden bereitstellt um einen String zu speichern.
 * Ideal zum Ableiten von weiteren Klassen geeignet!
*/
class CEntry {
public:
	CEntry();								//!< Konstruktor
	virtual ~CEntry();						//!< Destruktor
	const std::string& getSymbol() const;	//!< Getter Methode, die den gespeicherten String zurückgibt; readonly, d.h. die Methode kann nichts ändern @return string
	void setSymbol(std::string);			//!< Setter Methode, die einen übergebenen String abspeichert @param text
	static unsigned int getNumber();		//!< gibt die gezählt Anzahl der Knoten zurück
private:
	std::string m_symbol;					//!< private Eigenschaft der Klasse: der String
	static unsigned int m_number;			//!< statische private Eigenschaft der Klasse: zählt die erstellen Objekte
};


#endif /* CENTRY_HPP_ */
