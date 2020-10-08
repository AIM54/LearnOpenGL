# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")
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