/*
 * CKnot.cpp
 *
 *  Created on: 28.05.2015
 *      Author: niklas
 */
/*!
 * \file CKnot.cpp
 */

#include "CKnot.hpp"

/*!
 * Konstruktor, initialisiert den Elternknoten mit -2
 */
CKnot::CKnot():m_parent(-2) {}
/*!
 * Destruktor, greift auf den standard Destruktor zurück
 */
CKnot::~CKnot() {}
/*!
 * Getter Methode, die den Elternknoten zurück gibt
 * @return Nummer des Elternknotens
 */
int CKnot::getParent() const {
	return m_parent;
}
/*!
 * Setter Methode, die den Elternknoten setzt
 * @param Nummer des Elternknotens
 */
void CKnot::setParent(int parent) {
	m_parent=parent;
}
