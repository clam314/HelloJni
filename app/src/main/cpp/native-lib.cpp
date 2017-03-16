#include <jni.h>
#include <string>

extern "C"{
#include "libavcodec/avcodec.h"
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_clam314_hellojni_MainActivity_stringSizeFormJNI(JNIEnv *env, jobject instance, jstring s_) {
    return env->GetStringUTFLength(s_);
}

extern "C"
jstring
Java_com_clam314_hellojni_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
    char info[10000] = { 0 };
    sprintf(info, "%s\n", avcodec_configuration());
    return env->NewStringUTF(info);
}
