/*
 * ueb3.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: iso
 */

#include <iostream>

template <typename Left, typename Op, typename Right, typename T>
struct X {
	Left m_left; Right m_right;

	X(Left t1, Right t2) : m_left(t1), m_right(t2) { }

	T operator[](int i) {
		return Op::apply(m_left[i], m_right[i]);
	}
};

/*
 * einmal für double
 */
template <typename Op, typename Right, typename T>
struct X<double, Op, Right, T> {
	double m_left; Right m_right;

	X(double t1, Right t2) : m_left(t1), m_right(t2) { }

	T operator[](int i) {
		return Op::apply(m_left, m_right[i]);
	}
};

///*
// * und für long (long ist präziser als double bei zahlen in
// * der nähe von 2^63)
// */
//template <typename Op, typename Right, typename T>
//struct X<long, Op, Right, T> {
//	long m_left; Right m_right;
//
//	X(long t1, Right t2) : m_left(t1), m_right(t2) { }
//
//	T operator[](int i) {
//		return Op::apply(m_left, m_right[i]);
//	}
//};


template <typename T>
struct Array {
	T *m_data;
	int m_N;

	// constructor
	Array( T *data, int N) : m_data(data), m_N(N) { }

	~Array() {
		std::cout << "Destructor called" << std::endl;
	}

	// assign an expression to the array
	template <typename Left, typename Op, typename Right>
	void operator=(X<Left, Op, Right, T> expr) {
		for (int i = 0; i < m_N; ++i) m_data[i] = expr[i];
	}

	T operator[] (int i) {
		return m_data[i];
	}

	void print() const {
		int l = 0;
		std::cout << '[';
		if (m_N > 0) std::cout << m_data[l++];
		while(l < m_N) std::cout << ',' << m_data[l++];
		std::cout << ']' << std::endl;
	}
};

template <typename T> struct Plus {
	static T apply(T a, T b) {
		return a+b;
	}
};

template <typename T> struct Minus {
	static T apply(T a, T b) {
		return a-b;
	}
};

template <typename T> struct Mul {
//	static auto apply(double a, T b) -> decltype(a*b) {
//		return a*b;
//	}
	static double apply(double a, T b) {
		return a*b;
	}
};

template <typename Left, typename T>
X<Left, Plus<T>, Array<T>, T> operator+(Left a, Array<T> b) {
	return X<Left, Plus<T>, Array<T>, T>(a,b);
}

template <typename Left, typename T>
X<Left, Minus<T>, Array<T>, T> operator-(Left a, Array<T> b) {
	return X<Left, Minus<T>, Array<T>, T>(a,b);
}

template <typename T>
X<double, Mul<T>, Array<T>, T> operator*(double a, Array<T> b) {
	return X<double, Mul<T>, Array<T>, T>(a,b);
}
