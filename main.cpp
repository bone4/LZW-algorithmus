/*!******************************************************//**
 *                Unit-Tests fürs Praktikum                  *
 ***********************************************************/

// Bitte hier eintragen, welcher Teil bearbeitet wird,
//   TEIL_1 = Array-Implementierung (CArray)
//   TEIL_2 = Trie-Implementierung (CTrie)
#define TEIL_2

// Benötigte Bibliotheken einbinden
#include <iostream>
#include <vector>
#include <string>
#include <map>

// Google Test einbinden
#include "gtest/gtest.h"

// Vorgegebene Klassen einbinden
#include "CLZW.hpp"
#include "CEnc.hpp"
#include "CDec.hpp"

// Praktikumsklassen einbinden
#include "CEntry.hpp"
#include "CArray.hpp"
#include "XOutOfBounds.hpp"
#include "CKnot.hpp"
#include "CDoubleHashing.hpp"
#include "CCounter.hpp"
#include "CForwardCounter.hpp"
#include "CArrayEnc.hpp"
#include "CArrayDec.hpp"

#ifdef TEIL_2
#include "CTrieEnc.hpp"
#include "CTrieDec.hpp"
#endif

using namespace std;

// Maps mit Zuordnung von Strings zu Ausgabewerten für den Test der Komprimierung
map<string, vector<unsigned int> > testPhrasesList;
map<string, vector<unsigned int> > testPhrasesTrie;

// Initialwert des CForwardCounter testen  (Aufgaben 2 und 3)
TEST(CForwardCounterTest, InitialZero) {
	CForwardCounter counter;
	EXPECT_EQ(0, counter.getValue()) << "Vorwaertszaehler ist nach Erstellung nicht 0!";
}

// Zählen des CForwardCounter testen  (Aufgaben 2 und 3)
TEST(CForwardCounterTest, Counting) {
	CForwardCounter counter;
	int value = counter.getValue() + 1;
	counter.count();
	EXPECT_EQ(value, counter.getValue()) << "Zaehlerwert wird bei count() nicht um 1 erhoeht!";
}

// Testen ob CEntry ordentlich initialisiert wird (Aufgabe 5)
TEST(CEntryTest, InitialEmpty) {
	CEntry entry;
	EXPECT_EQ("", entry.getSymbol()) << "Symbol ist initial nicht leer!";
}

// Testen ob das Symbol in CEntry gesetzt werden kann (Aufgabe 5)
TEST(CEntryTest, SetSymbol) {
	CEntry entry;
	string str = "TEST";
	entry.setSymbol(str);
	EXPECT_EQ(str, entry.getSymbol()) << "Symbol kann nicht gesetzt werden!";
}

// Testen ob die Anzahl der CEntry-Instanzen richtig gezählt wird (Aufgabe 5)
TEST(CEntryTest, CountInstances) {
	EXPECT_EQ(0, CEntry::getNumber());
	CEntry* entries[10];
	for (int i = 0; i < 10; i++) {
		entries[i] = new CEntry;
		EXPECT_EQ(i+1, CEntry::getNumber());
	}
	for (int i = 0; i < 10; i++) {
		delete entries[i];
		EXPECT_EQ(9-i, CEntry::getNumber());
	}
}

// Test ob Zugriff auf Arrayelemente in CArray funktioniert (Aufgabe 6)
TEST(CArrayTest, Array) {
	CArray<int, 10> dict;
	for (unsigned int i = 0; i < 10; i++) {
		dict[i] = i;
	}
	for (unsigned int i = 0; i < 10; i++) {
		EXPECT_EQ(i, dict[i]);
	}
}

// Test ob Exception bei Bereichsüberschreitung in CArray wirklich geworfen wird  (Aufgabe 6)
TEST(CArrayTest, Exception) {
	CArray<int, 10> dict;
	EXPECT_THROW(dict[10], XOutOfBounds) << "Exception wird bei zu grossem Index nicht geworfen!";
}

// Test der Methoden für Attribut symbol in CKnot (Aufgabe 6)
TEST(CKnotTest, symbol) {
	CKnot knot;
	EXPECT_EQ("", knot.getSymbol()) << "symbol ist initial nicht leer!";
	knot.setSymbol("Unit-Test");
	EXPECT_EQ("Unit-Test", knot.getSymbol()) << "symbol kann nicht gesetzt werden!";
}

// Test der Methoden für Attribut parent in CKnot (Aufgabe 6)
TEST(CKnotTest, parent) {
	CKnot knot;
	EXPECT_EQ(-2, knot.getParent()) << "parent ist initial nicht -2!";
	knot.setParent(6);
	EXPECT_EQ(6, knot.getParent()) << "parent kann nicht gesetzt werden!";
}

// Test der ersten Hashingfunktion in CDoubleHashing (Aufgabe 7)
TEST(CDoubleHashingTest, SimpleHashing) {
	CDoubleHashing& hash = CDoubleHashing::getInstance();
	EXPECT_EQ(4, hash.hash(3, 4, 7, 0));
	EXPECT_EQ(1, hash.hash(1, 2, 7, 0));
	EXPECT_EQ(0, hash.hash(2, 1, 7, 0));
}

// Test des doppelten Hashing in CDoubleHashing (Aufgabe 7)
TEST(CDoubleHashingTest, DoubleHashing) {
	CDoubleHashing& hash = CDoubleHashing::getInstance();
	EXPECT_EQ(10, hash.hash(3, 4, 11, 0));
	EXPECT_EQ(5, hash.hash(3, 4, 11, 1));
	EXPECT_EQ(0, hash.hash(3, 4, 11, 2));
	EXPECT_EQ(6, hash.hash(3, 4, 11, 3));
}

#ifdef TEIL_1
// LZW-Listenimplementierung getrennt nach Encoder und Decoder mit allen Testphrasen testen
TEST(CLZWListTest, Encoder) {
	// über alle Teststring iterieren
	for (map<string, vector<unsigned int> >::iterator it = testPhrasesList.begin(); it != testPhrasesList.end(); it++) {
		// Instanz muss immer neu angelegt werden, da sonst die Tabelle noch alte Einträge enthält
		CArrayEnc* lzw_enc = new CArrayEnc;
		// Phrase testen
		string input = it->first;
		vector<unsigned int> encoded = lzw_enc->encode(input);
		vector<unsigned int> reference = it->second;
		EXPECT_EQ(reference, encoded) << "Liste: Encodierung des Strings \"" << it->first << "\" ist fehlerhaft.";
		// und Instanz wieder löschen
		delete lzw_enc;
	}
}
TEST(CLZWListTest, Decoder) {
	// über alle Teststring iterieren
	for (map<string, vector<unsigned int> >::iterator it = testPhrasesList.begin(); it != testPhrasesList.end(); it++) {
		// Instanz muss immer neu angelegt werden, da sonst die Tabelle noch alte Einträge enthält
		CArrayDec* lzw_dec = new CArrayDec;
		// Phrase testen
		vector<unsigned int> input = it->second;
		string reference = it->first;
		string decoded = lzw_dec->decode(input);
		EXPECT_EQ(reference, decoded) << "Liste: Decodierung der Indizes \"" << it->first << "\" ist fehlerhaft.";
		// und Instanz wieder löschen
		delete lzw_dec;
	}
}
#endif // Ende Listenversion Encoder und Decoder


#ifdef TEIL_2
// LZW Trie-Implementierung getrennt nach Encoder und Decoder mit allen Testphrasen testen
// Zur Zeit wird nur der Encoder im Praktikum verlangt, später ggf. den Decodertest einkommentieren.

TEST(CTrieTest, Encoder) {
	// über alle Teststring iterieren
	for (map<string, vector<unsigned int> >::iterator it = testPhrasesTrie.begin(); it != testPhrasesTrie.end(); it++) {
		// Instanz muss immer neu angelegt werden, da sonst die Tabelle noch alte Einträge enthält
		CTrieEnc* lzw_enc = new CTrieEnc;
		// Phrase testen
		string input = it->first;
		vector<unsigned int> encoded = lzw_enc->encode(input);
		vector<unsigned int> reference = it->second;
		EXPECT_EQ(reference, encoded) << "Trie: Encodierung des Strings \"" << it->first << "\" ist fehlerhaft.";
		// und Instanz wieder löschen
		delete lzw_enc;
	}
}

//TEST(CTrieTest, Decoder) {
//	// über alle Teststring iterieren
//	for (map<string, vector<unsigned int>>::iterator it = testPhrasesTrie.begin(); it != testPhrasesTrie.end(); it++) {
//		// Instanz muss immer neu angelegt werden, da sonst die Tabelle noch alte Einträge enthält
//		CTrieDec* lzw_dec = new CTrieDec;
//		// Phrase testen
//		vector<unsigned int> input = it->second;
//		string reference = it->first;
//		string decoded = lzw_dec->decode(input);
//		EXPECT_EQ(reference, decoded) << "Trie: Decodierung des Strings \"" << it->first << "\" ist fehlerhaft.";
//		// und Instanz wieder löschen
//		delete lzw_dec;
//	}
//}


#endif  // Ende Trie Encoder und Decoder

// Map mit den Testphrasen und Ergebnissen aufbauen
void buildPhrases() {
	vector<unsigned int> resultList;
	vector<unsigned int> resultTrie;


// Test auf leere Liste
	resultList.clear();
	resultTrie.clear();
// Hier entsteht die für Test verwendete Datenstruktur
	testPhrasesList[""] = resultList;
	testPhrasesTrie[""] = resultTrie;

// Test auf periodische Paare
resultList.clear();
resultList.push_back(120);
resultList.push_back(121);
resultList.push_back(256);
resultList.push_back(258);
resultList.push_back(257);
resultList.push_back(260);
resultList.push_back(259);

resultTrie.clear();
resultTrie.push_back(120);
resultTrie.push_back(121);
resultTrie.push_back(1282);
resultTrie.push_back(1623);
resultTrie.push_back(1281);
resultTrie.push_back(1624);
resultTrie.push_back(1761);
// Hier entsteht die für Test verwendete Datenstruktur
testPhrasesList["xyxyxyxyxyxyxyxy"] = resultList;
testPhrasesTrie["xyxyxyxyxyxyxyxy"] = resultTrie;

// Test auf Wiederholung eines Zeichens
resultList.clear();
resultList.push_back(99);
resultList.push_back(256);
resultList.push_back(257);
resultList.push_back(258);
resultList.push_back(259);
resultList.push_back(259);
resultTrie.clear();
resultTrie.push_back(99);
resultTrie.push_back(1800);
resultTrie.push_back(1965);
resultTrie.push_back(1179);
resultTrie.push_back(1380);
resultTrie.push_back(1380);
// Hier entsteht die für Test verwendete Datenstruktur
testPhrasesList["cccccccccccccccccccc"] = resultList;
testPhrasesTrie["cccccccccccccccccccc"] = resultTrie;


// Test auf Umlaute und Sonderzeichen
resultList.clear();
resultList.push_back(228);
resultList.push_back(246);
resultList.push_back(252);
resultList.push_back(196);
resultList.push_back(214);
resultList.push_back(220);
resultList.push_back(223);
resultList.push_back(33);
resultList.push_back(167);
resultList.push_back(36);
resultList.push_back(37);
resultList.push_back(38);
resultList.push_back(47);
resultList.push_back(40);
resultList.push_back(41);
resultList.push_back(61);
resultList.push_back(63);
resultList.push_back(123);
resultList.push_back(91);
resultList.push_back(93);
resultList.push_back(125);
resultList.push_back(92);
resultList.push_back(180);
resultList.push_back(96);
resultList.push_back(43);
resultList.push_back(42);
resultList.push_back(126);
resultList.push_back(35);
resultList.push_back(39);
resultList.push_back(45);
resultList.push_back(95);
resultList.push_back(46);
resultList.push_back(58);
resultList.push_back(44);
resultList.push_back(59);
resultList.push_back(60);
resultList.push_back(62);
resultList.push_back(124);

resultTrie.clear();
resultTrie.push_back(228);
resultTrie.push_back(246);
resultTrie.push_back(252);
resultTrie.push_back(196);
resultTrie.push_back(214);
resultTrie.push_back(220);
resultTrie.push_back(223);
resultTrie.push_back(33);
resultTrie.push_back(167);
resultTrie.push_back(36);
resultTrie.push_back(37);
resultTrie.push_back(38);
resultTrie.push_back(47);
resultTrie.push_back(40);
resultTrie.push_back(41);
resultTrie.push_back(61);
resultTrie.push_back(63);
resultTrie.push_back(123);
resultTrie.push_back(91);
resultTrie.push_back(93);
resultTrie.push_back(125);
resultTrie.push_back(92);
resultTrie.push_back(180);
resultTrie.push_back(96);
resultTrie.push_back(43);
resultTrie.push_back(42);
resultTrie.push_back(126);
resultTrie.push_back(35);
resultTrie.push_back(39);
resultTrie.push_back(45);
resultTrie.push_back(95);
resultTrie.push_back(46);
resultTrie.push_back(58);
resultTrie.push_back(44);
resultTrie.push_back(59);
resultTrie.push_back(60);
resultTrie.push_back(62);
resultTrie.push_back(124);

// Hier entsteht die für Test verwendete Datenstruktur
// Der Backslash 92 \ muss im String doppelt erscheinen, sonst wäre es ein Steuerzeichen.
testPhrasesList["äöüÄÖÜß!§$%&/()=?{[]}\\""´`+*~#'-_.:,;<>|"] = resultList;
testPhrasesTrie["äöüÄÖÜß!§$%&/()=?{[]}\\""´`+*~#'-_.:,;<>|"] = resultTrie;

// Test auf allgemeinen Text
resultList.clear();
resultList.push_back(87);
resultList.push_back(101);
resultList.push_back(110);
resultList.push_back(110);
resultList.push_back(32);
resultList.push_back(83);
resultList.push_back(111);
resultList.push_back(110);
resultList.push_back(100);
resultList.push_back(101);
resultList.push_back(114);
resultList.push_back(122);
resultList.push_back(101);
resultList.push_back(105);
resultList.push_back(99);
resultList.push_back(104);
resultList.push_back(257);
resultList.push_back(32);
resultList.push_back(110);
resultList.push_back(269);
resultList.push_back(104);
resultList.push_back(116);
resultList.push_back(32);
resultList.push_back(107);
resultList.push_back(111);
resultList.push_back(114);
resultList.push_back(114);
resultList.push_back(101);
resultList.push_back(107);
resultList.push_back(277);
resultList.push_back(100);
resultList.push_back(97);
resultList.push_back(114);
resultList.push_back(103);
resultList.push_back(101);
resultList.push_back(115);
resultList.push_back(116);
resultList.push_back(101);
resultList.push_back(108);
resultList.push_back(108);
resultList.push_back(277);
resultList.push_back(119);
resultList.push_back(265);
resultList.push_back(264);
resultList.push_back(110);
resultList.push_back(44);
resultList.push_back(32);
resultList.push_back(115);
resultList.push_back(111);
resultList.push_back(32);
resultList.push_back(108);
resultList.push_back(105);
resultList.push_back(101);
resultList.push_back(103);
resultList.push_back(277);
resultList.push_back(290);
resultList.push_back(32);
resultList.push_back(98);
resultList.push_back(268);
resultList.push_back(32);
resultList.push_back(65);
resultList.push_back(83);
resultList.push_back(67);
resultList.push_back(73);
resultList.push_back(73);
resultList.push_back(45);
resultList.push_back(90);
resultList.push_back(268);
resultList.push_back(270);
resultList.push_back(272);
resultList.push_back(111);
resultList.push_back(313);
resultList.push_back(114);
resultList.push_back(104);
resultList.push_back(97);
resultList.push_back(108);
resultList.push_back(98);
resultList.push_back(32);
resultList.push_back(49);
resultList.push_back(50);
resultList.push_back(55);
resultList.push_back(32);
resultList.push_back(97);
resultList.push_back(259);
resultList.push_back(264);
resultList.push_back(114);
resultList.push_back(32);
resultList.push_back(322);
resultList.push_back(275);
resultList.push_back(257);
resultList.push_back(115);
resultList.push_back(97);
resultList.push_back(116);
resultList.push_back(122);
resultList.push_back(45);
resultList.push_back(69);
resultList.push_back(105);
resultList.push_back(110);
resultList.push_back(291);
resultList.push_back(293);
resultList.push_back(108);
resultList.push_back(117);
resultList.push_back(110);
resultList.push_back(103);
resultList.push_back(46);

resultTrie.clear();
resultTrie.push_back(87);
resultTrie.push_back(101);
resultTrie.push_back(110);
resultTrie.push_back(110);
resultTrie.push_back(32);
resultTrie.push_back(83);
resultTrie.push_back(111);
resultTrie.push_back(110);
resultTrie.push_back(100);
resultTrie.push_back(101);
resultTrie.push_back(114);
resultTrie.push_back(122);
resultTrie.push_back(101);
resultTrie.push_back(105);
resultTrie.push_back(99);
resultTrie.push_back(104);
resultTrie.push_back(476);
resultTrie.push_back(32);
resultTrie.push_back(110);
resultTrie.push_back(1009);
resultTrie.push_back(104);
resultTrie.push_back(116);
resultTrie.push_back(32);
resultTrie.push_back(107);
resultTrie.push_back(111);
resultTrie.push_back(114);
resultTrie.push_back(114);
resultTrie.push_back(101);
resultTrie.push_back(107);
resultTrie.push_back(1058);
resultTrie.push_back(100);
resultTrie.push_back(97);
resultTrie.push_back(114);
resultTrie.push_back(103);
resultTrie.push_back(101);
resultTrie.push_back(115);
resultTrie.push_back(116);
resultTrie.push_back(101);
resultTrie.push_back(108);
resultTrie.push_back(108);
resultTrie.push_back(1058);
resultTrie.push_back(119);
resultTrie.push_back(1334);
resultTrie.push_back(402);
resultTrie.push_back(110);
resultTrie.push_back(44);
resultTrie.push_back(32);
resultTrie.push_back(115);
resultTrie.push_back(111);
resultTrie.push_back(32);
resultTrie.push_back(108);
resultTrie.push_back(105);
resultTrie.push_back(101);
resultTrie.push_back(103);
resultTrie.push_back(1058);
resultTrie.push_back(1551);
resultTrie.push_back(32);
resultTrie.push_back(98);
resultTrie.push_back(1426);
resultTrie.push_back(32);
resultTrie.push_back(65);
resultTrie.push_back(83);
resultTrie.push_back(67);
resultTrie.push_back(73);
resultTrie.push_back(73);
resultTrie.push_back(45);
resultTrie.push_back(90);
resultTrie.push_back(1426);
resultTrie.push_back(810);
resultTrie.push_back(1318);
resultTrie.push_back(111);
resultTrie.push_back(265);
resultTrie.push_back(114);
resultTrie.push_back(104);
resultTrie.push_back(97);
resultTrie.push_back(108);
resultTrie.push_back(98);
resultTrie.push_back(32);
resultTrie.push_back(49);
resultTrie.push_back(50);
resultTrie.push_back(55);
resultTrie.push_back(32);
resultTrie.push_back(97);
resultTrie.push_back(381);
resultTrie.push_back(402);
resultTrie.push_back(114);
resultTrie.push_back(32);
resultTrie.push_back(893);
resultTrie.push_back(711);
resultTrie.push_back(476);
resultTrie.push_back(115);
resultTrie.push_back(97);
resultTrie.push_back(116);
resultTrie.push_back(122);
resultTrie.push_back(45);
resultTrie.push_back(69);
resultTrie.push_back(105);
resultTrie.push_back(110);
resultTrie.push_back(912);
resultTrie.push_back(281);
resultTrie.push_back(108);
resultTrie.push_back(117);
resultTrie.push_back(110);
resultTrie.push_back(103);
resultTrie.push_back(46);

// Hier entsteht die für Test verwendete Datenstruktur
testPhrasesList["Wenn Sonderzeichen nicht korrekt dargestellt werden, so liegt es bei ASCII-Zeichen oberhalb 127 an der Zeichensatz-Einstellung."] = resultList;
testPhrasesTrie["Wenn Sonderzeichen nicht korrekt dargestellt werden, so liegt es bei ASCII-Zeichen oberhalb 127 an der Zeichensatz-Einstellung."] = resultTrie;

}


  // Hauptprogramm Unittest
int main(int argc, char** argv) {
	// Testphrasen aufbauen
	buildPhrases();

	// Google Test initialisieren
	testing::InitGoogleTest(&argc, argv);

	// alle Tests ausführen
	int ret = RUN_ALL_TESTS();

	// und Ergebnis zurückgeben
	return ret;
}
