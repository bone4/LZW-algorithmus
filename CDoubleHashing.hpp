/*
 * CDoubleHashing.hpp
 *
 *  Created on: 18.05.2015
 *      Author: cge0496
 */
/*!
 * \file CDoubleHashing.hpp
 * \brief Definition der Klasse CDoubleHashing
*/

#ifndef CDOUBLEHASHING_HPP_
#define CDOUBLEHASHING_HPP_


/*!
 * \class CDoubleHashing
 * \brief Die Hashfunktion ordnet einem Objekt eine Zahl zu
 * Diese Klasse lässt nur eine Instanz zu, mit der man belibig oft Hashes berrechnen kann.
 * nach dem Entwurfsmuster: Singleton-Musters
*/
class CDoubleHashing {
public:
	static CDoubleHashing& getInstance();																//!< Getter Methode, gibt die einzige Instanz zurück
	unsigned int hash(unsigned int I, unsigned int J, unsigned int dict_size, unsigned int attempt);	// dict_size = m im Skript; attempt = i im Skript
																										//!< Hash-Methode
private:
	CDoubleHashing();																					//!< privater Konstruktor
		// Konstruktor verboten
	CDoubleHashing(const CDoubleHashing& other);														//!< privater Kopierkonstruktor
		// Kopierkonstruktor verboten
	CDoubleHashing operator=(CDoubleHashing& other);													//!< privater Operator=
		// Zuweisungsoperator verboten
	static CDoubleHashing m_instance;																	//!< private statische Klasseneigenschaft, die die einzige Klasseninstanz speichert

	unsigned int a,b;																					//!< evt. für die Hash-Methode, momentan gerade nciht in Gebrauch
};


#endif /* CDOUBLEHASHING_HPP_ */
