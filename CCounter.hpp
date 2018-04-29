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
 * \brief abstrakte Zählerklasse
 * Zählerklasse, speichert den internen Zählerstand und stellt Methoden zum Speichern uns Auslesen bereit
*/
class CCounter {
public:
	CCounter(int value=0);						//!< Konstruktor
	virtual ~CCounter();						//!< Destruktor
	virtual void count()=0;						//!< rein virtuelle Methode zum weiter zählen
	int getValue() const;						//!< gibt den aktuellen Zählerstand aus
	void setValue(int value);					//!< überschreibt den aktuellen Zählerstand mit \param value Zählerstand

	bool operator< (const CCounter&) const;		//!< Vergleichsoperator, liefert wahr, wenn aktueller Zählerstand kleiner ist als der des übergebenen Objekts
	bool operator> (const CCounter&) const;		//!< Vergleichsoperator, liefert wahr, wenn aktueller Zählerstand größer ist als der des übergebenen Objekts
private:
	int m_value;								//!< privater Zählerstand

};


#endif /* CCOUNTER_HPP_ */
