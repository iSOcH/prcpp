/*
 * genericfactorial.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: iso
 */

#include <iostream>

template <int n> struct Factorial {
	enum { value = n * Factorial<n-1>::value };
};

template <> struct Factorial<1> {
	enum {value = 1};
};

int main() {
	const int fact = Factorial<10>::value;
	std::cout << fact << std::endl;
}
