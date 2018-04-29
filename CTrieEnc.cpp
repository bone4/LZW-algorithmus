/*
 * CTrieEnc.cpp
 *
 *  Created on: 01.06.2015
 *      Author: niklas
 */
/*!
 * \file CTrieEnc.cpp
 */

#include <iostream>
#include "CTrieEnc.hpp"
#include "CEnc.hpp"
#include "CKnot.hpp"
#include "CForwardCounter.hpp"
#include "CDoubleHashing.hpp"
// #include "XOutOfBounds.hpp"
 /*!
  * Konstruktor, initialisiert m_symbolTable (das Wörterbuch) mit den Symbolen der erweiterten ASCII-Tabelle (0-255, 256 Stück) und einem Elternteil von -1 (da Wurzel).
  * Allen Feldern dadrüber, bis LZW_DICT_SIZE, wird der leere String und ein Eternteil von -2 zugewiesen.
  */
CTrieEnc::CTrieEnc() {
	int i;
	for(i=0;i<LZW_DICT_SIZE;i++) {
		if (i<256) {
			m_symbolTable[i].setSymbol(intToString(i));
			m_symbolTable[i].setParent(-1);
		} else {
			m_symbolTable[i].setSymbol("");
			m_symbolTable[i].setParent(-2);
			// unbelegte Knoten sollen m_parent = -2 haben
			// Hilft beim Suchen und Finden von freien Feldern
		}
	}
}
/*!
 * standard Destruktor
 */
CTrieEnc::~CTrieEnc() {}

/*!
 * eigentlicher Encoder: Bekommt einen Text, erzeugt Wörterbucheinträgt und sendet bei sich wiederholdenden Zeichefolgen nur die kurze Wörterbuchnummer statt des langen Texts.
 * @param text
 * @return Zahlenvektor
 */
vector<unsigned int> CTrieEnc::encode(const std::string &text) {
	int I,J, hashWert, ERSTERhashWert,i; // Elternposition I; numerischen ASCII-Wert J
	CDoubleHashing& hash = CDoubleHashing::getInstance();
	CForwardCounter attemptCounter; // für die Anz. der Rehashingversuche
	std::vector<unsigned int> ausgabe;
	std::string::const_iterator buchstabe;
	std::string JalsString;

	// Abfangen des leeren Strings:
	if(text=="") return ausgabe;

	/*!
	 * Merken der ASCII Zahl zum ersten Buchstaben.
	 * Ab dem 2. Buchstaben, Buchstabenweise den Text einlesen und verarbeiten
	 */
	I=charToInt(*text.begin());
	for(buchstabe=text.begin()+1; buchstabe!=text.end(); ++buchstabe) {
		/*!
		 * J ist den aktuelle Buchstabe als Zahl,
		 * JalsString speichert den Buchstaben als Buchstaben
		 */
		J=charToInt(*buchstabe);
		JalsString="" + *buchstabe;

		/*!
		 * i zähle die Schleifendurchläufe und damit fast die rehash-Versuche.
		 * Die rehash Nummer wird von einem Counter gezählt.
		 */
		i=1;
		attemptCounter.setValue(0);
		while(i) {
			/*!
			 * Hashen, und 1. Hash merken für den Fall, dass wir wieder beim Start ankommen
			 */
			hashWert=hash.hash(I,J,LZW_DICT_SIZE,attemptCounter.getValue());
			if(i==1) ERSTERhashWert=hashWert;
			/*!
			 * Wenn an der Stelle des berechnetten Hashwerts bereits genau die vorliegenden Daten gespeichert sind,
			 * wird I der aktuelle Hash zugewiesen und im nächsten Schritt mit dem nächsten Buchstaben aus dem Text weitegemacht.
			 */
			if((m_symbolTable[hashWert].getSymbol()==JalsString) && (m_symbolTable[hashWert].getParent()==I)) {
				// bereits gespeichert
				// ausgabe.push_back(I);
				I=hashWert;
				break;
			/*!
			 * Wenn sonst der berechnete Platz frei ist, wird er beschrieben
			 */
			} else if(m_symbolTable[hashWert].getParent()==-2) {
				// freien Platz gefunden
				m_symbolTable[hashWert].setSymbol(JalsString);
				m_symbolTable[hashWert].setParent(I);
				ausgabe.push_back(I);
				I=J;
				break;
			/*!
			 * Und wenn wir wieder am Anfang mit den Hashwerten ankommen, ist wohl kein Platz mehr im Wörterbuch für weitere neue Einträge
			 */
			} else if((hashWert==ERSTERhashWert) && (i>1)) {
				// einmal im Kreis gehasht und nichts passendes gefunden
				throw XOutOfBounds("Dictionary ist ausgeschöpft");
				break;
			}
			/*!
			 * An sonsten wird weitergezählt und neu gehasht, bis einer der 3 oberen Fälle eintritt.
			 */
			attemptCounter.count();
			i++;
		}
	}
	/*!
	 * Bedingt durch den Algorithmus, muss der letzte Wert noch ausgegeben werden
	 */
	ausgabe.push_back(I);

	return ausgabe;
}
