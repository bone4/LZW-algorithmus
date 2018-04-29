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
  * Konstruktor, initialisiert m_value mit dem übergebenen Wert
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
 * Getter Methode für den aktuellen Zählerstand
 * @return Zählerstand
 */
int CCounter::getValue() const{
	return m_value;
}
/*!
 * Setter Methode für den aktuellen Zählerstand
 * @param value Zählerstand
 */
void CCounter::setValue(int value) {
	m_value = value;
}

/*!
 * Vergleichsoperator, liefert wahr, wenn aktueller Zählerstand kleiner ist als der des übergebenen Objekts
 * @param b
 * @return true/false
 */
bool CCounter::operator<(const CCounter& b) const {
	if (getValue()<b.getValue()) return true;
	return false;
}
/*!
 * Vergleichsoperator, liefert wahr, wenn aktueller Zählerstand größer ist als der des übergebenen Objekts
 * @param b
 * @return true/false
 */
bool CCounter::operator>(const CCounter& b) const {
	if (getValue()>b.getValue()) return true;
	return false;
}
