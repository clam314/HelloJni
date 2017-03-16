//
// Created by clam314 on 2017/3/16.
//
#include <stdio.h>
#include "ffmpeg-hello.h"
extern "C"
{
#include <libavcodec/avcodec.h>
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_clam314_hellojni_FFmpegHelloActivity_avcodeConfigFromJni(JNIEnv *env, jobject instance) {
    char info[10000] = { 0 };
    sprintf(info, "%s\n", avcodec_configuration());
    return env->NewStringUTF(info);
}
