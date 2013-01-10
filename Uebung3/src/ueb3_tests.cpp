/*
 * ueb3_tests.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: iso
 */

#include <iostream>
#include "ueb3.cpp";

void first() {
	double a_data[] = { 2, 3, 5, 9 };
	double b_data[] = { 1, 0, 0, 1 };
	double c_data[] = { 3, 0, 2, 5 };
	double d_data[4];

	Array<double> A(a_data,4);
	Array<double> B(b_data,4);
	Array<double> C(c_data,4);
	Array<double> D(d_data,4);

	D = A + B + C;
	D.print();

	D = A - B - C;
	D.print();
}

void second() {
	int k = 5;
	double l = 3.14;

	double a_data[] = { 2, 3, 5, 9 };
	double b_data[] = { 1, 0, 0, 1 };
	double c_data[] = { 3, 0, 2, 5 };
	double d_data[4];

	Array<double> A(a_data,4);
	Array<double> B(b_data,4);
	Array<double> C(c_data,4);
	Array<double> D(d_data,4);

	C = k*A;
	D = l*B;
	D = C+D;
	//D = k*A + B; // das funktioniert noch
	//D = B + k*A; // no match for ‘operator+’ in ‘B + operator*(double, Array<T>) [with T = double](A)’
	D = k*A + B + l*C;
	D = k*A - B - l*C;
	D = A*k;
	D = A*k + B + C*l;
	D = A*k - B - C*l;
	D.print();
}
//
//void third() {
//	double a_data[] = { 2, 3, 5, 9 };
//	double b_data[] = { 1, 0, 0, 1 };
//
//	Array<double> A(a_data,4);
//	Array<double> B(b_data,4);
//
//	Array<double> C = A**B;
//	C.print();
//}

int main() {
	first();
	std::cout << "********************************************";
	second();
}
