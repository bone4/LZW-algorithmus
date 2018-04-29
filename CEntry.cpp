/*
 * CEntry.cpp
 *
 *  Created on: 27.05.2015
 *      Author: niklas
 */
/*!
 * \file CEntry.cpp
 */

#include <string>
using namespace std;
#include "CEntry.hpp"

/*!
 * globale Definition der statischen m_Number Klasseneigenschaft
 */
unsigned int CEntry::m_number=0;
/*!
  * Konstruktor, initialisiert m_value mit einem leeren String
  */
CEntry::CEntry():m_symbol("") {
	m_number+=1;
}
/*!
 * Destruktor
 */
CEntry::~CEntry() {
	m_number-=1;
}
/*!
 * Getter Methode, die den gespeicherten String zurückgibt;
 * readonly, d.h. die Methode kann nichts ändern
 * @return string
 */
const string& CEntry::getSymbol() const {
	return m_symbol;
}
/*!
 * Setter Methode, die einen übergebenen String abspeichert
 * @param text
 */
void CEntry::setSymbol(string text) {
	m_symbol=text;
}
/*!
 * Gibt die positive ganze Zahl, erstellter Objekte dieser Klasse aus.
 * -> Zählt die Anzahl der Knoten
 * @return positive ganze Zahl
 */
unsigned int CEntry::getNumber() {
	return m_number;
}

