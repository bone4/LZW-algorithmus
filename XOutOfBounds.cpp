/*
 * XOutOfBounds.cpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file XOutOfBounds.cpp
 */

#include "XOutOfBounds.hpp"

/*!
 * Konstruktor, nimmt die Fehlermeldung entgegen und initialisiert den privaten Speicher mit dieser Fehlermeldung
 * @param Fehlermeldung
 */
XOutOfBounds::XOutOfBounds(const char* msg) : m_msg(msg) { }
/*!
 * Destruktor, greift auf den standard Destruktor zurück
 * lässt keine Ausnahmen zu -> throw()
 */
XOutOfBounds::~XOutOfBounds() throw() { }
/*!
 * Getter Methode, gibt die Fehlermeldung zurück
 * lässt keine Ausnahmen zu -> throw()
 * @return Fehlermeldung
 */
const char* XOutOfBounds::what() const throw() {
	return m_msg.c_str();
}

