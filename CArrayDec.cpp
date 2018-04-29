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
  * Konstruktor, initialisiert m_symbolTable (das W�rterbuch) mit den Symbolen der erweiterten ASCII-Tabelle (0-255, 256 St�ck).
  * Allen Feldern dadr�ber, bis LZW_DICT_SIZE, wird der leere String zugewiesen.
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
 * Suche nach einem String im W�rterbuch (Array); R�ckgabe ist die Nummer des Arrayspeicherplatzes.
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
	int puffer, index=256; // index zeigt auf die n�chste freie Nummer im W�rterbuch

	if(in.empty()) return "";	// f�ngt eine leere Eingabe ab!

	/*!
	 * der erste Wert wird direkt ausgegeben und zwischengespeichert
	 */
	ausgabe.append(intToString(in[0]));
	Slast=intToString(in[0]);
	for(zahl=1; zahl<in.size(); ++zahl) {
		// S=intToString(in[zahl]); funktionier leider nicht!!!
		/*!
		 * S speichet das im W�rterbuch hinterlegte Symbol zur Zahl aus dem Eingabevektor
		 * puffer speichert diese Zahl selber
		 */
		S=m_symbolTable[in[zahl]].getSymbol();
		puffer=in[zahl];
		// pr�fen, ob String zum Indexwert in der Tabelle steht:
		/*!
		 * pr�ft den einen Sonderfall ab, ob zwei aufeinander folgende Indexnummern �bergeben wurden, wo der 1. Eintrag noch nicht fertig war und der 2. bereits auf eben diesen zugreift.
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
		 * ausgabe ist der String, der am Ende zur�ckgegeben wird. Dieser wird erg�nzt um den String S.
		 * Zu Beginn um einzelne Buchstaben, sp�ter um im W�rterbuch zusammengesetzte Buchstaben.
		 */
		ausgabe.append(S);

		/*!
		 * Die aktuelle Zeichenkette wird f�r die n�chste Vektorzahl zwischengespeichert, da S f�r den n�chsten W�rterbucheintrag ben�tig wird.
		 */
		Slast=S;



		/*!
		 * Test, ob weitergearbeitet werden kann.
		 * Wenn nicht, wird eine Ausnahme geworfen.
		 */
		// Check, ob weiterer Durchlauf problemlos m�glich w�re:
		if (index==LZW_DICT_SIZE) throw XOutOfBounds("Dictionary ist ausgesch�pft");
	}

	return ausgabe;
}


