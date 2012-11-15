/*
 * =====================================================================================
 *
 *       Filename:  ch_fhnw_ch_prcpp_uebung2schwarzsacher_Matrix.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/2012 11:32:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Sacher (ms), michael.sacher@students.fhnw.ch
 *         					Pascal Schwarz (ps), pascal.schwarz@students.fhnw.ch
 *   Organization:  Fachhochschule Nordwestschweiz
 *
 * =====================================================================================
 */


#include "ch_fhnw_ch_prcpp_uebung2schwarzsacher_Matrix.h"
#include <time.h>
#include <stdio.h>
#include <cstring>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  matrix_multiply
 *  Description:  
 * =====================================================================================
 */
void matrix_multiply(
		jdouble * a, jdouble * b, jdouble * r,
		jint heightA, jint widthA, jint widthB) {
	const int rH = heightA;
	const int rW = widthB;
	for (int row=0; row<rH; row++) { // row in result
		for (int col=0; col<rW; col++) { // col in results
			r[row*rW + col] = 0; // make sure result is 0 before we begin
			for (int k=0; k<widthA; k++) {
				r[row*rW + col] += a[row*widthA + k] * b[k*widthB + col];
			}
		}
	}
}		/* -----  end of function matrix_multiply  ----- */

JNIEXPORT void JNICALL Java_ch_fhnw_ch_prcpp_uebung2schwarzsacher_Matrix_multiplyC(
		JNIEnv * env,
		jobject caller,
		jdoubleArray matA, jdoubleArray matB, jdoubleArray matR,
		jint heightA, jint widthA , jint widthB) {

	jboolean jfalse = false;
	jdouble * a, * b, * r;
	a = env->GetDoubleArrayElements(matA, &jfalse);
	b = env->GetDoubleArrayElements(matB, &jfalse);
	r = env->GetDoubleArrayElements(matR, &jfalse);


	//initialize stopwatch
	clock_t start, stop;
	double t = 0.0;
	//start the timer
	start = clock();

	matrix_multiply(a,b,r,heightA,widthA,widthB);


	//stop the timer
	stop = clock();
	t = (double) (stop-start)/CLOCKS_PER_SEC;
	printf("c++ took: %1.0fms\n", 1000*t);

	// mode 0: copy back and free elems-buffer
	// mode JNI_ABORT: free buffer, dont copy back
	env->ReleaseDoubleArrayElements(matA, a, JNI_ABORT);
	env->ReleaseDoubleArrayElements(matB, b, JNI_ABORT);
	env->ReleaseDoubleArrayElements(matR, r, 0);
}

JNIEXPORT void JNICALL Java_ch_fhnw_ch_prcpp_uebung2schwarzsacher_Matrix_powerC(
		JNIEnv * env, jobject caller,
		jdoubleArray matM, jdoubleArray matR,
		jint k, jint rows) {

	jboolean jfalse = false;
	jdouble * m, * r;
	m = env->GetDoubleArrayElements(matM, &jfalse);
	r = env->GetDoubleArrayElements(matR, &jfalse);

	//initialize stopwatch
	clock_t start, stop;
	double t = 0.0;
	//start the timer
	start = clock();

	switch (k) {
		case 0:
			for (int i=0; i<rows; i++) {
				r[i*rows + i] = 1.0;
			}
			break;
		case 1:
			for (int i=0; i<rows*rows; i++) {
				r[i] = m[i];
			}
			break;
		default:
			// k>=2
			matrix_multiply(m, m, r, rows, rows, rows);
			if (k>2) {
				jdouble * tmp = new jdouble[rows*rows];
				for (int i=2; i<k; i++) {
					matrix_multiply(r, m, tmp, rows, rows, rows);

					// swap for next iteration
					jdouble * tmpPointer = r;
					r = tmp;
					tmp = tmpPointer;
				}

				if (k%2!=0) {
					// k%2!=0 means the actual result is in the
					// location tmp initially pointed to, not in r

					// make our r point to the array our caller thinks
					// it is pointing to
					jdouble * tmpPointer = r;
					r = tmp;
					tmp = tmpPointer;

					// as we cant change the pointers outside of this scope,
					// we have to copy the contents of tmp to r
					memcpy(r, tmp, sizeof(jdouble) * rows * rows);
				}
				delete[] tmp;
			}
			break;
	}

	//stop the timer
	stop = clock();
	t = (double) (stop-start)/CLOCKS_PER_SEC;
	printf("c++ took: %1.0fms\n", 1000*t);

	// mode 0: copy back and free elems-buffer
	// mode JNI_ABORT: free buffer, dont copy back
	env->ReleaseDoubleArrayElements(matM, m, JNI_ABORT);
	env->ReleaseDoubleArrayElements(matR, r, 0);
}


