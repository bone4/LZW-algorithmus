/*
 * XOutOfBounds.hpp
 *
 *  Created on: 11.05.2015
 *      Author: cge0496
 */
/*!
 * \file XOutOfBounds.hpp
 * \brief Definition der Klasse XOutOfBounds, inklusive Deklaration und Definition der Methoden
*/

#ifndef XOUTOFBOUNDS_HPP_
#define XOUTOFBOUNDS_HPP_


#include <string>
#include <exception>
using namespace std;
/*!
 * \class XOutOfBounds
 * \brief Klasse zum Abfangen von Fehlern
 * Eine eigene Klasse zum Abfangen und Abfragen von Fehlern (exceptions).
 * Die Klasse ist eine Ableitung der Klasse "exception".
*/
class XOutOfBounds : public exception {
public:
	XOutOfBounds(const char*);					//!< Konstruktor, nimmt die Fehlermeldung entgegen @param Fehlermeldung
	virtual ~XOutOfBounds() throw();			//!< Destruktor, lässt keine Ausnahmen zu
	virtual const char* what() const throw();	//!< Getter Methode, die die Fehlermeldung zurückgibt, lässt ebenfalls keine Ausnahmen zu
private:
	std::string m_msg;							//!< privater String Speicher für die Fehlermeldung
};


#endif /* XOUTOFBOUNDS_HPP_ */
