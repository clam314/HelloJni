//
// Created by clam314 on 2017/3/20.
//
#include <jni.h>

extern "C"
{
JNIEXPORT jobject JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_getParameterTestList(JNIEnv *env, jobject instance, jint size) ;

JNIEXPORT jobject JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_getInstance(JNIEnv *env, jobject instance, jstring str_, jint num);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_callInstanceMethod(JNIEnv *env, jobject instance, jobject parameter);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_callStaticMethod(JNIEnv *env, jobject instance);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_parameterStringInput(JNIEnv *env,
                                                                        jobject instance,
                                                                        jstring s_);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_parameterArrayInput(JNIEnv *env,
                                                                       jobject instance,
                                                                       jintArray array_);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_parameterObjectInput(JNIEnv *env,
                                                                        jobject instance,
                                                                        jobject parameter);

JNIEXPORT void JNICALL
        Java_com_clam314_hellojni_HelloJniActivity_parameterInput(JNIEnv *env, jobject instance,
                                                                  jshort s,
                                                                  jint i, jlong l, jfloat f,
                                                                  jdouble d,
                                                                  jchar c);
}