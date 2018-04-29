/*!
\file CDec.hpp
\brief Klasse CDec Abstrakte Basisklasse für Decodierung

Dieses File enthält die abstrakte Basisklasse CDec.
Die beiden zugehörigen Files CDec.cpp und CDec.hpp werden
für die finale Erfolgskontrolle durch die Originalversionen ersetzt.
*/
#pragma once

#include "CLZW.hpp"
#include <string>
#include <vector>

using namespace std;
/*!
\class CDec
\brief Abstrakte Basisklasse für die Decoder

Abstrakte Basisklasse für die Decoder.
CDec erbt von CLZW.
Basisklasse der Encoderklassen CArrayDec und CTrieDec.
Von dieser Klasse CDec selbst können keine Instanzen erstellt werden,
sie ist abstrakt.
 */
class CDec : public CLZW
{
public:
	//! decodiert (restauriert) den String in mit Hilfe des LZW-Algorithmus
	//! \param in Vektor der zu decodierenden Indexwerte
	//! \return decodierter Zählerstand
	virtual string decode(const vector<unsigned int> &in)=0;

	//! Virtueller Destruktor
	virtual ~CDec();

};
