/*
 * CDoubleHashing.cpp
 *
 *  Created on: 18.05.2015
 *      Author: cge0496
 */
/*!
 * \file CDoubleHashing.cpp
 */

#include "CDoubleHashing.hpp"

/*!
 * Getter Methode, die die Referenz auf die einzige Instanz dieser Klasse zurück gibt
 * @return
 */
CDoubleHashing& CDoubleHashing::getInstance() {
	return m_instance;
}

/*!
 * privater Konstruktor, initialisiert die Variablen a und b
 */
CDoubleHashing::CDoubleHashing():a(0), b(0) {}

/*!
 * Die einzige Instanz der Klasse CDoubleHashing wird hier erstellt
 */
// Aufruf des Konstruktors
CDoubleHashing CDoubleHashing::m_instance;
// Objekt erstellen, wie sonst auch CCounter counter

/*!
 * Hash-Methode, berrechnet eine Hashzahl zu 2 eingegebenen Zahlen
 * @param I, 1. zu hashende Zahl
 * @param J, 2. zu hashende Zahl
 * @param dict_size, m im Skript; Größe des Hashwerts
 * @param attempt, Anzahl des hash Anlaufs; steigt bei Kollision; wird für jedes rehashing inkrementiert
 * @return
 */
unsigned int CDoubleHashing::hash(unsigned int I, unsigned int J, unsigned int dict_size, unsigned int attempt) {
	unsigned int x = 0.5*(I + J)*(I + J + 1) + J; // nicht 1/2 zu Beginn, da dies 0 als integer ist, im Gegensatz zu 0.5*(...) was erst am Ende zu einem Integer gecasted wird
	// doppelhashing
	return (x + (attempt*(1+(x%(dict_size-2)))))%dict_size;
}
