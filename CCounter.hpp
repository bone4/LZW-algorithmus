/*
 * CCounter.hpp
 *
 *  Created on: 13.04.2015
 *      Author: cge0496
 */
/*!
 * \file CCounter.hpp
 * \brief Definition der Klasse CCounter
*/

#ifndef CCOUNTER_HPP_
#define CCOUNTER_HPP_


/*!
 * \class CCounter
 * \brief abstrakte Z�hlerklasse
 * Z�hlerklasse, speichert den internen Z�hlerstand und stellt Methoden zum Speichern uns Auslesen bereit
*/
class CCounter {
public:
	CCounter(int value=0);						//!< Konstruktor
	virtual ~CCounter();						//!< Destruktor
	virtual void count()=0;						//!< rein virtuelle Methode zum weiter z�hlen
	int getValue() const;						//!< gibt den aktuellen Z�hlerstand aus
	void setValue(int value);					//!< �berschreibt den aktuellen Z�hlerstand mit \param value Z�hlerstand

	bool operator< (const CCounter&) const;		//!< Vergleichsoperator, liefert wahr, wenn aktueller Z�hlerstand kleiner ist als der des �bergebenen Objekts
	bool operator> (const CCounter&) const;		//!< Vergleichsoperator, liefert wahr, wenn aktueller Z�hlerstand gr��er ist als der des �bergebenen Objekts
private:
	int m_value;								//!< privater Z�hlerstand

};


#endif /* CCOUNTER_HPP_ */
