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
		jint k, jint rows, jint cols) {

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
			// Einheitsmatrix retournieren?
			for (int i=0; i<rows; i++) {
				r[i*cols + i] = 1.0;
			}
			break;
		case 1:
			for (int i=0; i<rows*cols; i++) {
				r[i] = m[i];
			}
			break;
		default:
			// k>=2
			matrix_multiply(m,m,r,rows,cols,cols);
			if (k>2) {
				for (int i=2; i<k; i++) {
					// FIXME: i dont think produces the correct result
					// because matrix_multiply expects r to be a 0-matrix
					matrix_multiply(r,m,r,rows,cols,cols);
				}
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


