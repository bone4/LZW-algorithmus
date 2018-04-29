/*
 * CKnot.hpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CKnot.hpp
 * \brief Definition der Klasse CKnot
*/

#ifndef CKNOT_HPP_
#define CKNOT_HPP_


#include "CEntry.hpp"
/*!
 * \class CKnot
 * \brief Speicher für einen Elternknoten
 * Eine Klasse, die Getter und Setter Methoden bereitstellt um einen Elternknoten zu speichern.
*/
class CKnot : public CEntry {
public:
	CKnot();				//!< Konstruktor
	virtual ~CKnot();		//!< Destruktor
	int getParent() const;	//!< Getter Methode zum Auslesen des Elternknotens @return int
	void setParent(int);	//!< Setter Methode zum Abspeichern eines Elternknotens @param int
private:
	int m_parent;			//!< private integer Variable, die den Elternknoten speichert
};


#endif /* CKNOT_HPP_ */
