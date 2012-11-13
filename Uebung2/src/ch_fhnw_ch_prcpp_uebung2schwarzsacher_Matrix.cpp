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

	const int rH = heightA;
	const int rW = widthB;
	for (int row=0; row<rH; row++) { // row in result
		for (int col=0; col<rW; col++) { // col in results
			for (int k=0; k<widthA; k++) {
				r[row*rW + col] += a[row*widthA + k] * b[k*widthB + col];
			}
		}
	}

	// mode 0: copy back and free elems-buffer (here: r)
	// mode
	env->ReleaseDoubleArrayElements(matA, a, 0);
	env->ReleaseDoubleArrayElements(matB, b, JNI_ABORT);
	env->ReleaseDoubleArrayElements(matR, r, JNI_ABORT);
}

