/*
 * CForwardCounter.cpp
 *
 *  Created on: 13.04.2015
 *      Author: cge0496
 */
/*!
 * \file CVariableCounter.cpp
 */

#include "CForwardCounter.hpp"

/*!
 * Konstruktor
 */
CForwardCounter::CForwardCounter() {

}
/*!
 * Destruktor
 */
CForwardCounter::~CForwardCounter() {

}

/*!
 * Z�hler, inkrementiert den Z�hlerstand
 */
void CForwardCounter::count() {
		setValue(getValue()+1);
}


