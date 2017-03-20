# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.
#源码树的顶层路径。
set(distribution_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

add_library(
            avcodec-57
            SHARED
            IMPORTED)
set_target_properties( avcodec-57
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libavcodec-57.so )

add_library(
            avfilter-6
            SHARED
            IMPORTED)
set_target_properties( avfilter-6
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libavfilter-6.so )

add_library(
            avformat-57
            SHARED
            IMPORTED)
set_target_properties( avformat-57
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libavformat-57.so )

add_library(
            avutil-55
            SHARED
            IMPORTED)
set_target_properties( avutil-55
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libavutil-55.so )

add_library(
            swresample-2
            SHARED
            IMPORTED)
set_target_properties( swresample-2
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libswresample-2.so )

add_library(
            swscale-4
            SHARED
            IMPORTED)
set_target_properties( swscale-4
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libswscale-4.so )
add_library( avdevice-57
             SHARED
             IMPORTED)
set_target_properties( avdevice-57
                       PROPERTIES IMPORTED_LOCATION
                       ${distribution_DIR}/${ANDROID_ABI}/libavdevice-57.so )

#支持-std=gnu++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp )


add_library( ffmpeg-hello
             SHARED
             src/main/cpp/ffmpeg-hello.cpp )

add_library( hello-jni
             SHARED
             src/main/cpp/hello-jni.cpp )

include_directories(src/main/jniLibs/include/)

target_link_libraries( native-lib avcodec-57 avfilter-6 avformat-57 avutil-55 swresample-2 swscale-4 avdevice-57
                       ${log-lib} )

target_link_libraries( ffmpeg-hello avcodec-57 avfilter-6 avformat-57 avutil-55 swresample-2 swscale-4 avdevice-57
                       ${log-lib} )

target_link_libraries( hello-jni ${log-lib} )