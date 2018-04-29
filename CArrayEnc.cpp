/*
 * CArrayEnc.cpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CArrayEnc.cpp
 */

#include <iostream>
#include "CArrayEnc.hpp"
#include "CEnc.hpp"
#include "CArray.hpp"
#include "CEntry.hpp"
#include "XOutOfBounds.hpp"
 /*!
  * Konstruktor, initialisiert m_symbolTable (das W�rterbuch) mit den Symbolen der erweiterten ASCII-Tabelle (0-255, 256 St�ck).
  * Allen Feldern dadr�ber, bis LZW_DICT_SIZE, wird der leere String zugewiesen.
  */
CArrayEnc::CArrayEnc() {
	int i;
	for(i=0;i<LZW_DICT_SIZE;i++) {
		if (i<256)	m_symbolTable[i].setSymbol(intToString(i));
		else		m_symbolTable[i].setSymbol("");
	}
}
/*!
 * standard Destruktor
 */
CArrayEnc::~CArrayEnc() {}
/*!
 * Suche nach einem String im W�rterbuch (Array); R�ckgabe ist die Nummer des Arrayspeicherplatzes.
 * @param Such-String: text
 * @return Array-Feld-Nummer als int
 */
int CArrayEnc::searchInTable(const string& text) {
	int i, rueckgabe = -1;
	for(i=0;i<LZW_DICT_SIZE;i++) {
		if(m_symbolTable[i].getSymbol()==text) rueckgabe=i;
	}
	return rueckgabe;
}

/*!
 * eigentlicher Encoder: Bekommt einen Text, erzeugt W�rterbucheintr�gt und sendet bei sich wiederholdenden Zeichefolgen nur die kurze W�rterbuchnummer statt des langen Texts.
 * @param text
 * @return Zahlenvektor
 */
vector<unsigned int> CArrayEnc::encode(const string& text) {
	// std::cout << text << "\n"; DEBUG
	std::string S, Sx;
	std::vector<unsigned int> ausgabe;
	std::string::const_iterator buchstabe;
	int puffer, index=256; 	// puffer speichert Indexnummer der gesuchten Zeichenkette; index zeigt auf die n�chste freie Nummer im W�rterbuch
	// Abfangen des leeren Strings:
	if(text=="") return ausgabe;

	for(buchstabe=text.begin(); buchstabe!=text.end(); ++buchstabe) {	//!< lie�t Zeichenweise den Text ein
		/*!
		 * Sx ist das aktuelle Wort,
		 * S ist das Wort vom letzten Durchlauf und
		 * *buchstabe ist das aktuelle Zeichen aus dem Text
		 */
		Sx = S + *buchstabe;
		/*!
		 * puffer speichert die W�rterbuchzugriffsnummer zu dem String Sx
		 */
		puffer = searchInTable(Sx);
		if (puffer != -1) {	//!< Sx in Tabelle gefunden
			S = Sx;
		} else {			//!< Sx NICHT in Tabelle gefunden
			// Notiz: puffer ist immer gleich -1
			/*!
			 * Die W�rterbuchnummer zu S wird ausgegeben
			 */
			ausgabe.push_back(searchInTable(S));

			/*!
			 * Sicherheitshalber ein Test, ob weitergearbeitet werden kann. (CArray pr�ft sonst auch noch den Zugriff auf eine nicht reservierte Speicherstelle und wirft ggf. eine Ausnahme)
			 * Wenn nicht, wird eine Ausnahme geworfen.
			 */
			// Check, ob weiterer Dictionary-Eintrag m�glich ist:
			if (index==LZW_DICT_SIZE) throw XOutOfBounds("Dictionary ist ausgesch�pft");

			/*!
			 * Sx wird an der n�chsten freien Stelle im W�rterbucharray abgelegt.
			 */
			m_symbolTable[index].setSymbol(Sx);
			index++;
			// std::cout << Sx << "\n"; DEBUG
			S=*buchstabe;
		}
	}
	// Weil der Algorithmus es fordert, wird hier der letzte Buchstabe (der Index davon) in den Ausgabevektor geschrieben
	ausgabe.push_back(searchInTable(S));

	return ausgabe;
}

