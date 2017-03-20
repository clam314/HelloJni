//
// Created by clam314 on 2017/3/20.
//

#include "hello-jni.h"
#include <stdlib.h>
#include <android/log.h>
#define LOGE(format, ...) __android_log_print(ANDROID_LOG_INFO,"hello-jni", format, ##__VA_ARGS__)
#define LOGES(string) __android_log_write(ANDROID_LOG_INFO,"hello-jni",string);

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterInput(JNIEnv *env, jobject instance, jshort s,
                                                            jint i, jlong l, jfloat f, jdouble d,
                                                            jchar c) {
    LOGE("s=%hd, i=%d, l=%lld, f=%f, d=%lf, c=%c,b=%d", s, i, l, f, d,c);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterStringInput(JNIEnv *env,jobject instance, jstring s_){
    const char *c_str = nullptr;
    c_str = env->GetStringUTFChars(s_, nullptr);
    if(c_str == nullptr){
        LOGE("字符串为空");
        return;
    }
    LOGES(c_str);
    env->ReleaseStringUTFChars(s_,c_str);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterArrayInput(JNIEnv *env, jobject instance, jintArray array_){
    jint i,sum = 0;
    jint *c_array;
    jint arr_len;

    arr_len = env->GetArrayLength(array_);
    c_array = (jint*)malloc(sizeof(jint) * arr_len);
    memset(c_array,0, sizeof(jint)*arr_len);
    LOGE("arr_len = %d",arr_len);
    env->GetIntArrayRegion(array_,0,arr_len,c_array);
    for(i = 0; i<arr_len;i++){
        sum += c_array[i];
    }
    LOGE("sum = %d",sum);
    free(c_array);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterObjectInput(JNIEnv *env, jobject instance, jobject parameter){
    jfieldID fim_instance;
    jfieldID fim_static;
    jstring str;
    jint num;
    const char *c_str;
    fim_instance = env->GetFieldID(env->GetObjectClass(parameter),"str","Ljava/lang/String;");
    fim_static = env->GetStaticFieldID(env->GetObjectClass(parameter),"num","I");
    if(fim_instance == nullptr){
        LOGES("没有找到str这个实例变量");
        return;
    }
    if(fim_static == nullptr){
        LOGES("没有找到num这个静态变量");
        return;
    }
    num = env->GetStaticIntField(env->GetObjectClass(parameter),fim_static);
    str = (jstring)env->GetObjectField(parameter,fim_instance);
    c_str = env->GetStringUTFChars(str, nullptr);
    LOGE("parameter str = %s  num = %d",c_str,num);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_callInstanceMethod(JNIEnv *env, jobject instance, jobject parameter){
    jmethodID  mid_instance_method;
    mid_instance_method = env->GetMethodID(env->GetObjectClass(parameter),"toString","()Ljava/lang/String;");
    if(mid_instance_method == nullptr){
        LOGES("找不到toString这个方法。");
        return;
    }
    env->CallObjectMethod(parameter,mid_instance_method);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_callStaticMethod(JNIEnv *env, jobject instance){
    jclass  clazz = nullptr;
    jstring  str_arg = nullptr;
    jmethodID mid_static_method;
    clazz = env->FindClass("com/clam314/hellojni/ParameterTest");
    if(clazz == nullptr){
        LOGES("找不到类");
        return;
    }
    mid_static_method = env->GetStaticMethodID(clazz,"callStaticMethod","(Ljava/lang/String;I)V");
    if(mid_static_method == nullptr){
        LOGES("找不到callStaticMethod这个静态方法。");
        return;
    }
    str_arg = env->NewStringUTF("我是静态方法");
    env->CallStaticVoidMethod(clazz,mid_static_method,str_arg,666);
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(str_arg);
}

JNIEXPORT jobject JNICALL
Java_com_clam314_hellojni_HelloJniActivity_getInstance(JNIEnv *env, jobject instance, jstring str_, jint num){
    jclass clazz = env->FindClass("com/clam314/hellojni/ParameterTest");
    jmethodID constructor = env->GetMethodID(clazz,"<init>","(Ljava/lang/String;I)V");
    jobject  stub_object = env->NewObject(clazz,constructor,str_,num);
    return stub_object;
}

JNIEXPORT jobject JNICALL
Java_com_clam314_hellojni_HelloJniActivity_getParameterTestList(JNIEnv *env, jobject instance, jint size) {
    jclass clazz = env->FindClass("com/clam314/hellojni/ParameterTest");
    jmethodID constructor = env->GetMethodID(clazz,"<init>","(Ljava/lang/String;I)V");
    jclass clazz_list = env->FindClass("java/util/ArrayList");
    jmethodID constructor_list = env->GetMethodID(clazz_list,"<init>","()V");
    jmethodID add_list = env->GetMethodID(clazz_list,"add","(Ljava/lang/Object;)Z");

    jobject list = env->NewObject(clazz_list,constructor_list);
    for(jint i = 0; i<size;i++){
        jobject parameter_test = env->NewObject(clazz,constructor,env->NewStringUTF("add list"),i);
        env->CallBooleanMethod(list,add_list,parameter_test);
    }
    return list;
}
