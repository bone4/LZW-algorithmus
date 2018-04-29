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
 * \brief Z�hlerklasse, inkrementiert den Z�hler bei count()
 * Ein Z�hler, abgeleitet von CCounter.
 * Bei jedem Aufruf von count() wird die Z�hlervariable inkrementiert.
*/
// class CCounter;
class CForwardCounter : public CCounter {
public:
	CForwardCounter();				//!< Konstruktor
	virtual ~CForwardCounter();		//!< Destruktor
	virtual void count();			//!< Erh�ht den Z�hler um 1
private:

};


#endif /* CFORWARDCOUNTER_HPP_ */
