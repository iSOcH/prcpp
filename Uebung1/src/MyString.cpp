/*
 * MyMyString.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: iso
 */

#include "MyString.h"

template <typename T> class ArrayDeleter {
public:
    void operator () (T* d) const {
    	delete [] d;
    }
};

String::String() {
	m_len = 0;
	m_start = 0;
	m_string = nullptr;
}

String::String(const char* ptr) {
	//std::cout << "conv-ctor with " << ptr << std::endl;

	m_len = 0;
	m_start = 0;

	// Check if it is an empty cstring
	if (ptr[0] != '\0') {
		while (ptr[m_len] != '\0') {
			m_len++;
		}
	}

	// Create a new char array on the heap
	m_string = std::shared_ptr<char>(new char[m_len], ArrayDeleter<char>());

	// Copy the content of the cstring
	for (size_t i = 0; i < m_len; i++) {
		m_string.get()[i] = ptr[i];
	}
}

String::String(String&& str) {
	//std::cout << "Move-Ctor called" << std::endl;
	m_len = str.m_len;
	m_string = std::move(str.m_string);
	m_start = str.m_start;
}

String::~String() {
	//std::cout << "destroyed " << toCString().get() << std::endl;
	// nothing to do
}

char String::charAt(size_t index) const {
	if (index < m_len && index >= 0) {
		return m_string.get()[index+m_start];
	} else {
		throw std::out_of_range("index out of bounds: " + index);
	}
}

int String::compareTo(const String& s) const {
	size_t minlength = m_len < s.length() ? m_len : s.length();

	for (size_t pos=0; pos<minlength; pos++) {
		if (charAt(pos) < s.charAt(pos)) {
			return -1;
		} else if (charAt(pos) > s.charAt(pos)) {
			return 1;
		}
	}

	// strings are the same until minlength
	if (m_len == s.length()) {
		return 0;
	} else {
		return m_len < s.length() ? -1 : 1;
	}
}

String String::concat(char c) const {
	size_t len = m_len+1;

	String* tmpStr = new String();
	tmpStr->m_string = std::shared_ptr<char>(new char[len], ArrayDeleter<char>());
	tmpStr->m_len = len;

	memcpy(tmpStr->m_string.get(), m_string.get(), m_len);
	tmpStr->m_string.get()[len-1] = c;

	return std::move(*tmpStr);
}

String String::concat(const String & str) const {
	size_t len = m_len + str.length();

	String* tmpStr = new String();
	tmpStr->m_string = std::shared_ptr<char>(new char[len], ArrayDeleter<char>());
	tmpStr->m_len = len;

	memcpy(tmpStr->m_string.get(), m_string.get(), m_len);
	memcpy(&tmpStr->m_string.get()[m_len], str.m_string.get(), str.length());

	return std::move(*tmpStr);
}

std::unique_ptr<char[]> String::toCString() const {
	std::unique_ptr<char[]> r = std::unique_ptr<char[]>(new char[m_len + 1]);
	const char * const tc = m_string.get();
	//for (size_t i=0; i < m_len; i++) r[i] = tc[m_start + i];
	memcpy(r.get(), tc + m_start, m_len);
	r[m_len] = '\0';
	return std::move(r);
}

size_t String::length() const {
	return m_len;
}

String String::subString(size_t begin, size_t end) const {
	if (begin >= end || begin >= m_len) {
		return String();
	} else {
		if (end > m_len) {
			end = m_len;
		}
		String* retStr = new String();
		retStr->m_start = begin;
		retStr->m_len = end-begin;
		retStr->m_string = m_string;
		return std::move(*retStr);
	}
}

String String::valueOf(int i) {
	if (i==0) return String("0");

	bool negative = false;
	if (i < 0) {
		negative = true;
		i *= -1;
	}
	size_t digits = log10(i) + (negative ? 2 : 1);
	size_t digit = digits-1;

	String* result = new String();
	result->m_len = digits;
	result->m_string = std::shared_ptr<char>(new char[digits], ArrayDeleter<char>());

	if (negative) result->m_string.get()[0] = '-';

	while (i!=0) {
		int modres = i % 10;
		result->m_string.get()[digit] = modres+48;
		i -= modres;
		i /= 10;
		digit--;
	}
	return std::move(*result);
}
