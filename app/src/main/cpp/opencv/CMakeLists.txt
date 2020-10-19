# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI})

# set target ABI options
if( ${ANDROID_ABI} STREQUAL "x86" )
    set( ANDROID_NDK_ABI_NAME "x86" )
    set( ANDROID_ARCH_NAME "x86" )
    set( CMAKE_SYSTEM_PROCESSOR "i686" )
    set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -funwind-tables" )
    set( ANDROID_CXX_FLAGS_RELEASE "-fomit-frame-pointer -fstrict-aliasing" )
    set( ANDROID_CXX_FLAGS_DEBUG   "-fno-omit-frame-pointer -fno-strict-aliasing" )
elseif( ${ANDROID_ABI} STREQUAL "x86_64" )
    set( ANDROID_NDK_ABI_NAME "x86_64" )
    set( ANDROID_ARCH_NAME "x86_64" )
    set( CMAKE_SYSTEM_PROCESSOR "x86_64" )
    set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -funwind-tables" )
    set( ANDROID_CXX_FLAGS_RELEASE "-fomit-frame-pointer -fstrict-aliasing" )
    set( ANDROID_CXX_FLAGS_DEBUG   "-fno-omit-frame-pointer -fno-strict-aliasing" )
elseif( ${ANDROID_ABI} STREQUAL "arm64-v8a" )
    set( ANDROID_NDK_ABI_NAME "arm64-v8a" )
    set( ANDROID_ARCH_NAME "arm64" )
    set( CMAKE_SYSTEM_PROCESSOR "aarch64" )
    set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -mfpu=vfpv3" )
    set( ANDROID_CXX_FLAGS         "${ANDROID_CXX_FLAGS} -funwind-tables" )
    set( ANDROID_CXX_FLAGS_RELEASE "-fomit-frame-pointer -fstrict-aliasing" )
    set( ANDROID_CXX_FLAGS_DEBUG   "-fno-omit-frame-pointer -fno-strict-aliasing" )
elseif( ${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set( ANDROID_NDK_ABI_NAME "armeabi-v7a" )
    set( ANDROID_ARCH_NAME "arm" )
    set( CMAKE_SYSTEM_PROCESSOR "armv7-a" )
    set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -funwind-tables" )
    set( ANDROID_CXX_FLAGS_RELEASE "-mthumb -fomit-frame-pointer -fno-strict-aliasing" )
    set( ANDROID_CXX_FLAGS_DEBUG   "-marm -fno-omit-frame-pointer -fno-strict-aliasing" )
else()
    message( SEND_ERROR "Unknown ANDROID_ABI=\"${ANDROID_ABI}\" is specified." )
endif()
set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -fsigned-char" ) # good/necessary when porting desktop libraries
set( CMAKE_CXX_FLAGS           "${ANDROID_CXX_FLAGS} ${CMAKE_CXX_FLAGS}" )
set( CMAKE_C_FLAGS             "${ANDROID_CXX_FLAGS} ${CMAKE_C_FLAGS}" )
set( CMAKE_CXX_FLAGS_RELEASE   "${ANDROID_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS_RELEASE}" )
set( CMAKE_C_FLAGS_RELEASE     "${ANDROID_CXX_FLAGS_RELEASE} ${CMAKE_C_FLAGS_RELEASE}" )
set( CMAKE_CXX_FLAGS_DEBUG     "${ANDROID_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_DEBUG}" )
set( CMAKE_C_FLAGS_DEBUG       "${ANDROID_CXX_FLAGS_DEBUG} ${CMAKE_C_FLAGS_DEBUG}" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions  -Wall")
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
include_directories(header)

add_library( # Sets the name of the library.
        opencv_test
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        OpencvController.cpp
        ../gl3stub.c)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        opencv_test
        png
        assimp
        # Links the target library to the log library
        # included in the NDK.
        ${OPENGL_LIB}
        opencv_gapi
        opencv_video
        opencv_stitching
        opencv_objdetect
        opencv_highgui
        opencv_calib3d
        opencv_videoio
        opencv_imgcodecs
        opencv_features2d
        opencv_dnn
        opencv_photo
        opencv_ml
        opencv_imgproc
        opencv_flann
        opencv_core
        jnigraphics
        android
        EGL
        ${log-lib}
        m
        dl
        z)