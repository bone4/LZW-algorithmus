/*
 * CCounter.cpp
 *
 *  Created on: 13.04.2015
 *      Author: cge0496
 */
/*!
 * \file CCounter.cpp
 */

#include "CCounter.hpp"
 /*!
  * Konstruktor, initialisiert m_value mit dem �bergebenen Wert
  * @param value
  */
CCounter::CCounter(int value)
{
	m_value=value;
}
/*!
 * Destruktor
 */
CCounter::~CCounter() {

}
/*!
 * count() ist in CCounter rein virtuell und muss in abgeleiteten Klassen definiert werden!
 */
/*!
 * Getter Methode f�r den aktuellen Z�hlerstand
 * @return Z�hlerstand
 */
int CCounter::getValue() const{
	return m_value;
}
/*!
 * Setter Methode f�r den aktuellen Z�hlerstand
 * @param value Z�hlerstand
 */
void CCounter::setValue(int value) {
	m_value = value;
}

/*!
 * Vergleichsoperator, liefert wahr, wenn aktueller Z�hlerstand kleiner ist als der des �bergebenen Objekts
 * @param b
 * @return true/false
 */
bool CCounter::operator<(const CCounter& b) const {
	if (getValue()<b.getValue()) return true;
	return false;
}
/*!
 * Vergleichsoperator, liefert wahr, wenn aktueller Z�hlerstand gr��er ist als der des �bergebenen Objekts
 * @param b
 * @return true/false
 */
bool CCounter::operator>(const CCounter& b) const {
	if (getValue()>b.getValue()) return true;
	return false;
}
