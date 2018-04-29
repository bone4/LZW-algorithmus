/*
 * CArrayDec.cpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CArrayDec.cpp
 */

#include <iostream>
#include "CArrayDec.hpp"
#include "CDec.hpp"
#include "CArray.hpp"
#include "CEntry.hpp"
#include "XOutOfBounds.hpp"
 /*!
  * Konstruktor, initialisiert m_symbolTable (das Wörterbuch) mit den Symbolen der erweiterten ASCII-Tabelle (0-255, 256 Stück).
  * Allen Feldern dadrüber, bis LZW_DICT_SIZE, wird der leere String zugewiesen.
  */
CArrayDec::CArrayDec() {
	int i;
	for(i=0;i<LZW_DICT_SIZE;i++) {
		if (i<256)	m_symbolTable[i].setSymbol(intToString(i));
		else		m_symbolTable[i].setSymbol("");
	}
}
/*!
 * standard Destruktor
 */
CArrayDec::~CArrayDec() {}
/*!
 * Suche nach einem String im Wörterbuch (Array); Rückgabe ist die Nummer des Arrayspeicherplatzes.
 * @param Such-String: text
 * @return Array-Feld-Nummer als int
 */
int CArrayDec::searchInTable(const string& text) {
	int i, rueckgabe = -1;
	for(i=0;i<LZW_DICT_SIZE;i++) {
		if(m_symbolTable[i].getSymbol()==text) rueckgabe=i;
	}
	return rueckgabe;
}
/*!
 * eigentliche Haupt-Dekodierfunktion
 * @param Zahlenvektor: in
 * @return Text als string
 */
string CArrayDec::decode(const vector<unsigned int> &in) {
	unsigned int zahl; // gelesenes Input Element
	std::string ausgabe, S, Slast;	// ausgabe speichert dir gesammte Zeichenkette; S speichert den String von der letzten Eingabe(-Position); Slast speichert den String von der vorletzten Eingabe(-Position)
	int puffer, index=256; // index zeigt auf die nächste freie Nummer im Wörterbuch

	if(in.empty()) return "";	// fängt eine leere Eingabe ab!

	/*!
	 * der erste Wert wird direkt ausgegeben und zwischengespeichert
	 */
	ausgabe.append(intToString(in[0]));
	Slast=intToString(in[0]);
	for(zahl=1; zahl<in.size(); ++zahl) {
		// S=intToString(in[zahl]); funktionier leider nicht!!!
		/*!
		 * S speichet das im Wörterbuch hinterlegte Symbol zur Zahl aus dem Eingabevektor
		 * puffer speichert diese Zahl selber
		 */
		S=m_symbolTable[in[zahl]].getSymbol();
		puffer=in[zahl];
		// prüfen, ob String zum Indexwert in der Tabelle steht:
		/*!
		 * prüft den einen Sonderfall ab, ob zwei aufeinander folgende Indexnummern übergeben wurden, wo der 1. Eintrag noch nicht fertig war und der 2. bereits auf eben diesen zugreift.
		 */
		if((searchInTable(S) != -1) && (S != "")) {	// der Indexwert steht in der Tabelle
			m_symbolTable[index].setSymbol(Slast + S[0]);
			index++;
		} else {										// der Indexwert steht NICHT in der Tabelle
			m_symbolTable[index].setSymbol(Slast + Slast[0]);
			S=m_symbolTable[in[zahl]].getSymbol();		// S neu einlesen, in diesem Fall
			index++;
		}
		// DEBUG: cout << in[zahl] << "\t\t" << index-1 << ": " << m_symbolTable[index-1].getSymbol() << "\n";
		// ausgabe.append(intToString(in[zahl])); funktioniert leider nicht!!!
		/*!
		 * ausgabe ist der String, der am Ende zurückgegeben wird. Dieser wird ergänzt um den String S.
		 * Zu Beginn um einzelne Buchstaben, später um im Wörterbuch zusammengesetzte Buchstaben.
		 */
		ausgabe.append(S);

		/*!
		 * Die aktuelle Zeichenkette wird für die nächste Vektorzahl zwischengespeichert, da S für den nächsten Wörterbucheintrag benötig wird.
		 */
		Slast=S;



		/*!
		 * Test, ob weitergearbeitet werden kann.
		 * Wenn nicht, wird eine Ausnahme geworfen.
		 */
		// Check, ob weiterer Durchlauf problemlos möglich wäre:
		if (index==LZW_DICT_SIZE) throw XOutOfBounds("Dictionary ist ausgeschöpft");
	}

	return ausgabe;
}


