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

template <typename Left, typename Op, typename T>
struct X<Left, Op, double, T> {
	Left m_left; double m_right;

	X(Left t1, double t2) : m_left(t1), m_right(t2) { }

	T operator[](int i) {
		return Op::apply(m_left[i], m_right);
	}
};


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
		if (m_N == 1) {
			return m_data[0];
		} else {
			return m_data[i];
		}
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

template <typename T> class Mul {
private: T scalar;
public:
	static T apply(T a, T b) { return a * b; }
    Mul(T scalar) : scalar(scalar) {};
    T operator[](int i) { return scalar; } // same value for every index!
};

template <typename Left, typename T>
X<Left, Plus<T>, Array<T>, T> operator+(Left a, Array<T> b) {
	return X<Left, Plus<T>, Array<T>, T>(a,b);
}

template <typename Left, typename T, typename XL, typename XO, typename XR>
X<Left, Plus<T>, X<XL,XO,XR,T>, T> operator+( Left a, X<XL,XO,XR,T> b) {
    return X<Left, Plus<T>, X<XL,XO,XR,T>, T>(a,b);
}

template <typename Left, typename T>
X<Left, Minus<T>, Array<T>, T> operator-(Left a, Array<T> b) {
	return X<Left, Minus<T>, Array<T>, T>(a,b);
}

template <typename Left, typename T, typename XL, typename XO, typename XR>
X<Left, Minus<T>, X<XL,XO,XR,T>, T> operator-(Left a, X<XL,XO,XR,T> b) {
    return X<Left, Minus<T>, X<XL,XO,XR,T>, T>(a,b);
}

template <typename T>
X<double, Mul<T>, Array<T>, T> operator*(double a, Array<T> b) {
	return X<double, Mul<T>, Array<T>, T>(a,b);
}

template <typename T>
X<Array<T>, Mul<T>, double, T> operator*(Array<T> a, double b) {
	return X<Array<T>, Mul<T>, double, T>(a,b);
}
