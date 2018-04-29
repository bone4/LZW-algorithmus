/*
 * cArray.hpp
 *
 *  Created on: 11.05.2015
 *      Author: cge0496
 */
/*!
 * \file CArray.hpp
 * \brief Definition des Klassentemplates CArray
*/

#ifndef CARRAY_HPP_
#define CARRAY_HPP_



#include "XOutOfBounds.hpp"



/*!
 * \class CArray
 * \brief Klassentemplate für ein 1 dimensionales Array vom Typ T mit N Feldern
 * Eine Klasse, die über den Konstruktor ein Array dynamisch allokiert, über den Destruktor wieder frei gibt und Methoden zum Zugriff bereit stellt.
 * Jedes angelegte Array (Instanz/Objekt der Klasse) ist vom Typ T, z.B. int, float oder double, und enthält N Felder, von 0 bis N-1.
*/
template <typename T, unsigned int N>
class CArray
{
public:
	CArray();						//!< Konstruktor, legt ein Array an / reserviert Speicher
	CArray(const CArray&);			//!< Kopierkonstruktor
	virtual ~CArray();				//!< Destruktor, gibt das Array wieder frei
	T& operator[](unsigned int);	//!< Methode für den Zugriff auf einzelne Spcherzellen
private:
	T *entries;						//!< privater Pointer auf die Startadresse des Arrays
};

/*!
 * Konstruktor, initialisiert den privaten Speicher mit der Speicheradresse des zugeteilten Arrayspcherplatzes
 */
template <typename T, unsigned int N>
CArray<T,N>::CArray(): entries(new T[N])
{
}

/*!
 * Kopierkonstruktor
 * aktuell ist der Kopierkonstruktor für tiefe Kopien aktiv,
 * d.h. es wird ein komplett neues Array erstellt und alle Inhalte werden kopiert,
 * statt nur einen neuen Pointer auf das Startelement zu erstellen.
 * @param other
 */
// Kopierkonstruktor mit flacher Kopie
/*
template <typename T, unsigned int N>
CArray<T,N>::CArray(const CArray& other): entries(other.entries)
{
}
*/
// Kopierkonstruktor mit tiefer Kopie
template <typename T, unsigned int N>
CArray<T,N>::CArray(const CArray& other): entries(new T[N])
{
	int i;
	for (i=0;i<N;i++) entries[i]=other.entries[i];
}

/*!
 * Destruktor, gibt den reservierten Speicherplatz wieder frei
 */
template <typename T, unsigned int N>
CArray<T,N>::~CArray() {
	delete [] entries;
}
/*!
 * Operator[x], gibt den Inhalt an x. Speicheradresse zurück (WICHTIG: Zählung von 0 bis N-1)
 * @param Z
 * @return Speicherinhalt vom Typ T
 */
template <typename T, unsigned int N>
T& CArray<T,N>::operator[](unsigned int Z) {
	if (Z >= N) throw XOutOfBounds("Außerhalb des Arrays");
	else return entries[Z];
}


#endif /* CARRAY_HPP_ */
