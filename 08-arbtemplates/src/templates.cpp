/*
 * templates.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: iso
 */

#include <iostream>
#include <typeinfo>

/*
 * aufgabe 1
 */
template<typename A, typename B> auto min(A a, B b) -> decltype((a<b) ? a : b) {
	return (a<b) ? a : b;
};
// end aufgabe 1

/*
 * aufgabe 2
 */
template <int n> struct Fibonacci {
	static const int value = Fibonacci<n-1>::value + Fibonacci<n-2>::value;
};

template <> struct Fibonacci<1> {
	static const int value = 1;
};

template <> struct Fibonacci<0> {
	static const int value = 0;
};
// end aufgabe 2

/*
 * aufgabe 3
 * DAFUQ THIS IS MADNESS
 */
template <bool condition, typename Then, typename Else> struct IF {
	typedef Then RET;
};

template <typename Then, typename Else> struct IF<false, Then, Else> {
	typedef Else RET;
};
// end aufgabe 3

int main() {
	int i=3;
	double d=2.14;

	std::cout << "min" << std::endl;
	std::cout << min<int,int>(2, i) << '\n';
	std::cout << min<int,double>(i, d) << '\n';

	std::cout << "fibonacci\n";
	std::cout << Fibonacci<10>::value << '\n';

	IF<sizeof(int)<sizeof(long), long, int>::RET x=1;
	std::cout << "typ von x " << typeid(x).name() << std::endl;
}
