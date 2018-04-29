/*
 * CForwardCounter.hpp
 *
 *  Created on: 13.04.2015
 *      Author: cge0496
 */
/*!
 * \file CForwardCounter.hpp
 * \brief Definition der Klasse CForwardCounter
*/

#ifndef CFORWARDCOUNTER_HPP_
#define CFORWARDCOUNTER_HPP_


#include "CCounter.hpp"
/*!
 * \class CForwardCounter
 * \brief Zählerklasse, inkrementiert den Zähler bei count()
 * Ein Zähler, abgeleitet von CCounter.
 * Bei jedem Aufruf von count() wird die Zählervariable inkrementiert.
*/
// class CCounter;
class CForwardCounter : public CCounter {
public:
	CForwardCounter();				//!< Konstruktor
	virtual ~CForwardCounter();		//!< Destruktor
	virtual void count();			//!< Erhöht den Zähler um 1
private:

};


#endif /* CFORWARDCOUNTER_HPP_ */
