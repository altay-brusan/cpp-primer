/*
 * Chapter 34 - JNI: Implementing a Java native Method in C++
 *
 * The C++ side of calling C++ from Java through the Java Native Interface (JNI).
 * The Java class HelloCpp declares "public static native void callCpp()"; the
 * javah/javac toolchain generates HelloCpp.h with the mangled prototype
 * Java_HelloCpp_callCpp, which this file implements. It is compiled into a
 * shared library (hellocpp.dll or hellocpp.so) that Java loads at runtime via
 * System.loadLibrary, after which the native method prints from C++.
 *
 * Key notes:
 *   - Needs a JDK: include jni.h and the generated HelloCpp.h, build as a shared library.
 */

#include <jni.h>
#include "HelloCpp.h"
#include <iostream>

JNIEXPORT void JNICALL Java_HelloCpp_callCpp(JNIEnv*, jclass)
{
	std::cout << "Hello from C++!" << std::endl;
}
