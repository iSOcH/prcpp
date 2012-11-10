/*
 * MyString.h
 *
 *  Created on: Oct 18, 2012
 *      Author: iso
 */

#ifndef MyString_H_
#define MyString_H_

#include <cstddef>
#include <memory>
#include <ostream>
#include <iostream>
#include <utility>
#include <cstring>
#include <math.h>
#include <stdexcept>

class String final {
	std::shared_ptr<char> m_string;
	size_t m_len;
	size_t m_start;
public:
	String();
	virtual ~String();
	String(const String& str): m_string(str.m_string), m_len(str.length()), m_start(str.m_start) {
		//std::cout << "Copy ctor called" << std::endl;
	};
	String(const char*);
	String(String&& str);

	// Instanz-Methoden
	char charAt(size_t index) const; // bei falschem Index: wirft exception
	int compareTo(const String& s) const; // C++ untypische Funktion: gibt -1, 0, 1 zurück
	String concat(char c) const; // hängt c ans Ende und gibt neuen MyString zurück
	String concat(const String& s) const;
	size_t length() const; // gibt die Länge des MyStrings zurück

	// SubMyString des Bereichs [beg, end)
	// falls beg ≥ m_len oder end ≤ beg: gibt leeren MyString zurück
	String subString(size_t beg, size_t end) const;

	// erzeugt 0-terminierten C-String, kopiert Inhalt und gibt Zeigerobjekt zurück
	std::unique_ptr<char[]> toCString() const;

	// Gleichheitsoperator (Inline-Implementation schon gegeben)
	bool operator==(const String& s) const { return compareTo(s) == 0; }

	// Ausgabe-Operator für Output-Streams (Inline-Implementation schon gegeben)
	friend std::ostream& operator<<(std::ostream& os, const String& s) {
		const size_t end = s.m_start + s.m_len;
		const char* const sc = s.m_string.get();
		for(size_t i=s.m_start; i < end; i++) os << sc[i];
		return os;
	}
	// Klassen-Methode
	static String valueOf(int i); // erzeugt eine MyString-Repräsentation von i
};

#endif /* MyString_H_ */
