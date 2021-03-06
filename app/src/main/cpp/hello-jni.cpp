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
    c_str = env->GetStringUTFChars(s_, nullptr);//第二个参数用于指定是复制字符串还在直接引用字符串，为了保证Java String是final的，一般都选择复制一份
    if(c_str == nullptr){//当分配空间失败时候。JNI并不会抛异常，只会返回NULL，这时候需要判断，否则后续的操作都是非常危险
        LOGE("字符串为空");
        return;
    }
    LOGES(c_str);
    env->ReleaseStringUTFChars(s_,c_str);//释放字符串,Get方法一般都有配套的Release用于释放之前分配的内存
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterArrayInput(JNIEnv *env, jobject instance, jintArray array_){
    jint i,sum = 0;
    jint *c_array;
    jint arr_len;
    //1. 获取数组长度
    arr_len = env->GetArrayLength(array_);
    //2. 根据数组长度和数组元素的数据类型申请存放java数组元素的缓冲区
    c_array = (jint*)malloc(sizeof(jint) * arr_len);
    //3. 初始化缓冲区
    memset(c_array,0, sizeof(jint)*arr_len);
    LOGE("arr_len = %d",arr_len);
    //4. 拷贝Java数组中的所有元素到缓冲区中
    env->GetIntArrayRegion(array_,0,arr_len,c_array);
    for(i = 0; i<arr_len;i++){
        sum += c_array[i];
    }
    LOGE("sum = %d",sum);
    //5. 释放存储数组元素的缓冲区
    free(c_array);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_parameterObjectInput(JNIEnv *env, jobject instance, jobject parameter){
    jfieldID fim_instance;
    jfieldID fim_static;
    jstring str;
    jint num;
    const char *c_str;
    //使用env->env->GetObjectClass(parameter)获取实例的类实例jclass
    //第一个参数是jclass第二个参数是变量名，第三个参数是变量的类型
    //获取实例变量的id
    fim_instance = env->GetFieldID(env->GetObjectClass(parameter),"str","Ljava/lang/String;");
    //获取静态变量的id
    fim_static = env->GetStaticFieldID(env->GetObjectClass(parameter),"num","I");
    if(fim_instance == nullptr){
        LOGES("没有找到str这个实例变量");
        return;
    }
    if(fim_static == nullptr){
        LOGES("没有找到num这个静态变量");
        return;
    }
    //根据获取到的静态变量id，获取静态变量
    num = env->GetStaticIntField(env->GetObjectClass(parameter),fim_static);
    //根据获取到的实例变量id，获取实例变量
    str = (jstring)env->GetObjectField(parameter,fim_instance);
    c_str = env->GetStringUTFChars(str, nullptr);
    LOGE("parameter str = %s  num = %d",c_str,num);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_callInstanceMethod(JNIEnv *env, jobject instance, jobject parameter){
    jmethodID  mid_instance_method;//方法的id
    //第一个参数是实例的类实例jclass，第二个参数是方法名，第三个参数方法描述符
    mid_instance_method = env->GetMethodID(env->GetObjectClass(parameter),"toString","()Ljava/lang/String;");
    if(mid_instance_method == nullptr){
        LOGES("找不到toString这个方法。");
        return;
    }
    //根据方法id调用实例的方法
    env->CallObjectMethod(parameter,mid_instance_method);
}

JNIEXPORT void JNICALL
Java_com_clam314_hellojni_HelloJniActivity_callStaticMethod(JNIEnv *env, jobject instance){
    jclass  clazz = nullptr;
    jstring  str_arg = nullptr;
    jmethodID mid_static_method;
    //查找类的实例jclass,类所在的路径. 类的全路径名，中间用/代替. 若是SDK提供类似 "java/util/ArrayList"
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
