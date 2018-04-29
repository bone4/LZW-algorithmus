/*!
\file CEnc.hpp
\brief Klasse CEnc Abstrakte Basisklasse für Encodierung

Dieses File enthält die abstrakte Basisklasse CEnc.
Die beiden zugehörigen Files CEnc.cpp und CEnc.hpp werden
für die finale Erfolgskontrolle durch die Originalversionen ersetzt.
*/
#pragma once

#include "CLZW.hpp"
#include <string>
#include <vector>

using namespace std;
/*!
\class CEnc
\brief Abstrakte Basisklasse für die Encoder

Abstrakte Basisklasse für die Encodierung.
CEnc erbt von CLZW.
Basisklasse der Encoderklassen CArrayEnc und CTrieEnc.
Von dieser Klasse CEnc selbst können keine Instanzen erstellt werden,
sie ist abstrakt.
 */
class CEnc : public CLZW
{
public:
	//! encodiert (komprimiert) den String in mit Hilfe des LZW-Algorithmus
	//! \param in String der zu encodierenden Zeichenfolge
	//! \return Vektor der zu übertragenden Indexwerte
	virtual vector<unsigned int> encode(const string &in) =0;

	// Destruktor
	virtual ~CEnc();

};
