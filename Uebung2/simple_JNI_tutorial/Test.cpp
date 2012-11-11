#include "Test.h"
#include <jni.h>
#include <iostream>
JNIEXPORT void JNICALL Java_Test_display(JNIEnv*, jclass) {
	std::cout << "C++: Hello, world!" << std::endl;
}
JNIEXPORT jint JNICALL Java_Test_increment (JNIEnv*, jclass, jint i) {
	return i + 1;
}

