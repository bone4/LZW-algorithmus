/*!
\file CLZW.hpp
\brief CLZW.hpp Basisklasse für LZW Encoder und Decoder

Diese Basisklasse zu den abstrakten Klassen CEnc und CDec
stellt zwei statische Methoden und eine Konstante zur Verfügung.
intToString  wandelt von Integer nach String und
charToInt    wandelt von char nach Integer
Beide statischen Funktionen werden verwendet zur Wandlung
von Zeichen in ihre Indexwerte.

LZW_DICT_SIZE legt die Größe des Dictionarys fest.
*/

#pragma once

#include <string>
#include <vector>

using namespace std;

/*! Größe des Arrays für Dictionary festlegen
// Größe des Dictionary bei 16 bit           65636
// Praktikable Größe für kürzere Rechenzeit   2000
// Anmerkung: Versuche, diese Konstante anders als über Präprozessor Deklarative
// festzulegen (statische Variable, Konstante in main.cpp) scheitern,
// da die Initialisierung für das CArray zu spät stattfindet.
*/
#define LZW_DICT_SIZE 2000

/*!
 * \class CLZW
 * \brief CLZW.hpp Basisklasse für LZW Encoder und Decoder
 *
 * intToString ermöglicht  das Umwandeln von Integern zu string
 * charToInt ermöglicht das Umwandeln von einzelnen Elementen eines string in
 * die zugehörige ASCII-Zahl auch für Einträge 128-255 (z.B. Umlaute)
 */
class CLZW
{
public:

	// ermöglicht das Umwandeln von Integern zu string
	static string intToString(int i);

	// ermöglicht das Umwandeln von einzelnen Elementen eines string in 
	// die zugehörige ASCII-Zahl auch für Einträge 128-255 (z.B. Umlaute)
	static unsigned int charToInt(char);

	// Größe des Dictionary (16 bit)        65636
	// Kleinere Größe für kürzere Rechenzeit 2000

};
