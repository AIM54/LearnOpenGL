# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions -Wall")
if (${ANDROID_PLATFORM_LEVEL} LESS 12)
    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 \
                      (currently using ${ANDROID_PLATFORM_LEVEL}).")
    return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
    add_definitions("-DDYNAMIC_ES3")
    set(GL3STUB_SRC gl3stub.c)
    set(OPENGL_LIB GLESv2)
else ()
    set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 12)

include_directories(
        header
        header/glm
        header/assimp
        header/ffmpeg
        header/png
        libleaktracer/include
        header/opencv2
        opengl)

set(jniPath "${CMAKE_CURRENT_SOURCE_DIR}/../jniLib")
set(opencv3rdPath "${jniPath}/3rdparty/libs")
set(opencvStaticPath "${jniPath}/staticlibs")
set(PATH_TO_MEDIACORE ${CMAKE_SOURCE_DIR})

file(GLOB FILES_C "${PATH_TO_MEDIACORE}/glbase/*.c"
                  "${PATH_TO_MEDIACORE}/glbase/*.cpp")
file(GLOB FILE_RENDER_BASE "${PATH_TO_MEDIACORE}/opengl/*.cpp")
file(GLOB FILE_RENDER "${PATH_TO_MEDIACORE}/opengl/drawer/*.cpp")
file(GLOB VIDEO_CPP "${PATH_TO_MEDIACORE}/video/*.cpp")
file(GLOB SURFACE_RENDER_SOURCE "${PATH_TO_MEDIACORE}/glsurface/render/*.cpp")

file(GLOB LEAK_TRACER_CPP_SOURCE "${PATH_TO_MEDIACORE}/libleaktracer/src/*.cpp")
file(GLOB LEAK_TRACER_C_SOURCE "${PATH_TO_MEDIACORE}/libleaktracer/src/*.c")

add_library(png STATIC IMPORTED)
set_target_properties(png PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libpng.a)
set_target_properties(png PROPERTIES INTERFACE_LINK_LIBRARIES "z")

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libassimp.so)

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libavcodec.so)

add_library(avdevice SHARED IMPORTED)
set_target_properties(avdevice PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libavdevice.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libavfilter.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libavutil.so)

add_library(postproc SHARED IMPORTED)
set_target_properties(postproc PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libpostproc.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libswresample.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${jniPath}/${ANDROID_ABI}/libswscale.so)


#openCv的一些库文件导入
add_library(ippiw STATIC IMPORTED)
set_target_properties(ippiw PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libippiw.a"
        )

# Create imported target libcpufeatures
add_library(libcpufeatures STATIC IMPORTED)
set_target_properties(libcpufeatures PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libcpufeatures.a"
        )

# Create imported target libjpeg-turbo
add_library(libjpeg-turbo STATIC IMPORTED)
set_target_properties(libjpeg-turbo PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibjpeg-turbo.a"
        )

# Create imported target libtiff
add_library(libtiff STATIC IMPORTED)
set_target_properties(libtiff PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C;CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibtiff.a"
        )
set_target_properties(libtiff PROPERTIES
        INTERFACE_LINK_LIBRARIES "z"
        )

# Create imported target libwebp
add_library(libwebp STATIC IMPORTED)
set_target_properties(libwebp PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibwebp.a"
        )

set_target_properties(libwebp PROPERTIES
        INTERFACE_LINK_LIBRARIES "libcpufeatures"
        )

# Create imported target libjasper
add_library(libjasper STATIC IMPORTED)
set_target_properties(libjasper PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibjasper.a"
        )


# Create imported target libpng
add_library(libpng STATIC IMPORTED)
set_target_properties(libpng PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibpng.a"
        )
set_target_properties(libpng PROPERTIES
        INTERFACE_LINK_LIBRARIES "z"
        )

# Create imported target IlmImf
add_library(IlmImf STATIC IMPORTED)
set_target_properties(IlmImf PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libIlmImf.a"
        )
set_target_properties(IlmImf PROPERTIES
        INTERFACE_LINK_LIBRARIES "z"
        )

# Create imported target tbb
add_library(tbb STATIC IMPORTED)
set_target_properties(tbb PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libtbb.a"
        )
set_target_properties(tbb PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "TBB_USE_GCC_BUILTINS=1;__TBB_GCC_BUILTIN_ATOMICS_PRESENT=1;TBB_SUPPRESS_DEPRECATED_MESSAGES=1"
        INTERFACE_LINK_LIBRARIES "c;m;dl"
        )

# Create imported target libprotobuf
add_library(libprotobuf STATIC IMPORTED)
set_target_properties(libprotobuf PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/liblibprotobuf.a"
        )

# Create imported target quirc
add_library(quirc STATIC IMPORTED)
set_target_properties(quirc PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libquirc.a"
        )


# Create imported target tegra_hal
add_library(tegra_hal STATIC IMPORTED)
set_target_properties(tegra_hal PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libtegra_hal.a"
        )


# Create imported target ittnotify
add_library(ittnotify STATIC IMPORTED)
set_target_properties(ittnotify PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libittnotify.a"
        )

set_target_properties(ittnotify PROPERTIES
        INTERFACE_LINK_LIBRARIES "dl"
        )

# Create imported target ade
add_library(ade STATIC IMPORTED)
set_target_properties(ade PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libade.a"
        )
# Create imported target ocv.3rdparty.android_mediandk
add_library(ocv.3rdparty.android_mediandk INTERFACE IMPORTED)

set_target_properties(ocv.3rdparty.android_mediandk PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "HAVE_ANDROID_MEDIANDK"
        INTERFACE_INCLUDE_DIRECTORIES ""
        INTERFACE_LINK_LIBRARIES "-landroid -llog -lmediandk"
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ""
        )
add_library(ippicv STATIC IMPORTED)
set_target_properties(ippicv PROPERTIES
        IMPORTED_LINK_INTERFACE_LIBRARIES ""
        IMPORTED_LOCATION "${opencv3rdPath}/${ANDROID_ABI}/libippicv.a"
        )

# Create imported target opencv_core
add_library(opencv_core STATIC IMPORTED)
set_target_properties(opencv_core PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_core.a"
        )


# Create imported target opencv_flann
add_library(opencv_flann STATIC IMPORTED)
set_target_properties(opencv_flann PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_flann.a"
        )


# Create imported target opencv_imgproc
add_library(opencv_imgproc STATIC IMPORTED)
set_target_properties(opencv_imgproc PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_imgproc.a"
        )


# Create imported target opencv_ml
add_library(opencv_ml STATIC IMPORTED)
set_target_properties(opencv_ml PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_ml.a"
        )


# Create imported target opencv_photo
add_library(opencv_photo STATIC IMPORTED)
set_target_properties(opencv_photo PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_photo.a"
        )


# Create imported target opencv_dnn
add_library(opencv_dnn STATIC IMPORTED)
set_target_properties(opencv_dnn PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_dnn.a"
        )


# Create imported target opencv_features2d
add_library(opencv_features2d STATIC IMPORTED)
set_target_properties(opencv_features2d PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_features2d.a"
        )


# Create imported target opencv_imgcodecs
add_library(opencv_imgcodecs STATIC IMPORTED)
set_target_properties(opencv_imgcodecs PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_imgcodecs.a"
        )


# Create imported target opencv_videoio
add_library(opencv_videoio STATIC IMPORTED)
set_target_properties(opencv_videoio PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_videoio.a"
        )


# Create imported target opencv_calib3d
add_library(opencv_calib3d STATIC IMPORTED)
set_target_properties(opencv_calib3d PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_calib3d.a"
        )


# Create imported target opencv_highgui
add_library(opencv_highgui STATIC IMPORTED)
set_target_properties(opencv_highgui PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_highgui.a"
        )


# Create imported target opencv_objdetect
add_library(opencv_objdetect STATIC IMPORTED)
set_target_properties(opencv_objdetect PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_objdetect.a"
        )


# Create imported target opencv_stitching
add_library(opencv_stitching STATIC IMPORTED)
set_target_properties(opencv_stitching PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_stitching.a"
        )

# Create imported target opencv_video
add_library(opencv_video STATIC IMPORTED)
set_target_properties(opencv_video PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_video.a"
        )


# Create imported target opencv_gapi
add_library(opencv_gapi STATIC IMPORTED)
set_target_properties(opencv_gapi PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${opencvStaticPath}/${ANDROID_ABI}/libopencv_gapi.a"
        )


if (${ANDROID_ABI} STREQUAL arm64-v8a)
    set_target_properties(opencv_flann PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_imgproc PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )

    set_target_properties(opencv_ml PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_photo PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_dnn PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>;\$<LINK_ONLY:libprotobuf>"
            )

    set_target_properties(opencv_features2d PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_flann;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_imgcodecs PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>;\$<LINK_ONLY:z>;\$<LINK_ONLY:libjpeg-turbo>;\$<LINK_ONLY:libwebp>;\$<LINK_ONLY:libpng>;\$<LINK_ONLY:libtiff>;\$<LINK_ONLY:libjasper>;\$<LINK_ONLY:IlmImf>"
            )
    set_target_properties(opencv_videoio PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_imgcodecs>;opencv_core;opencv_imgproc;opencv_imgcodecs;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>;\$<LINK_ONLY:ocv.3rdparty.android_mediandk>"
            )
    set_target_properties(opencv_calib3d PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_highgui PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_imgcodecs>;\$<LINK_ONLY:opencv_videoio>;opencv_core;opencv_imgproc;opencv_imgcodecs;opencv_videoio;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )

    set_target_properties(opencv_objdetect PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>;\$<LINK_ONLY:quirc>"
            )
    set_target_properties(opencv_stitching PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_video PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>"
            )
    set_target_properties(opencv_gapi PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;\$<LINK_ONLY:opencv_video>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;opencv_video;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:tegra_hal>;\$<LINK_ONLY:ade>;\$<LINK_ONLY:tbb>"
            )
elseif (${ANDROID_ABI} STREQUAL x86)
    set_target_properties(opencv_core PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:tbb>;\$<LINK_ONLY:z>;\$<LINK_ONLY:libcpufeatures>;\$<LINK_ONLY:ittnotify>"
            )
    set_target_properties(opencv_flann PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_imgproc PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_ml PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;opencv_core;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_photo PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_dnn PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:libprotobuf>"
            )
    set_target_properties(opencv_features2d PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_flann;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_imgcodecs PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;opencv_core;opencv_imgproc;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:z>;\$<LINK_ONLY:libjpeg-turbo>;\$<LINK_ONLY:libwebp>;\$<LINK_ONLY:libpng>;\$<LINK_ONLY:libtiff>;\$<LINK_ONLY:libjasper>;\$<LINK_ONLY:IlmImf>"
            )
    set_target_properties(opencv_videoio PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_imgcodecs>;opencv_core;opencv_imgproc;opencv_imgcodecs;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:ocv.3rdparty.android_mediandk>"
            )
    set_target_properties(opencv_calib3d PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_highgui PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_imgcodecs>;\$<LINK_ONLY:opencv_videoio>;opencv_core;opencv_imgproc;opencv_imgcodecs;opencv_videoio;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_objdetect PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:quirc>"
            )
    set_target_properties(opencv_stitching PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_video PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>"
            )
    set_target_properties(opencv_gapi PROPERTIES
            INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:opencv_core>;\$<LINK_ONLY:opencv_flann>;\$<LINK_ONLY:opencv_imgproc>;\$<LINK_ONLY:opencv_features2d>;\$<LINK_ONLY:opencv_calib3d>;\$<LINK_ONLY:opencv_video>;opencv_core;opencv_flann;opencv_imgproc;opencv_features2d;opencv_calib3d;opencv_video;\$<LINK_ONLY:dl>;\$<LINK_ONLY:m>;\$<LINK_ONLY:log>;\$<LINK_ONLY:ippiw>;\$<LINK_ONLY:ippicv>;\$<LINK_ONLY:ade>;\$<LINK_ONLY:tbb>"
            )
endif ()

#自己编写的两个库
add_subdirectory(${CMAKE_SOURCE_DIR}/opengl)
add_subdirectory(${CMAKE_SOURCE_DIR}/glsurface)
add_subdirectory(${CMAKE_SOURCE_DIR}/video)
add_subdirectory(${CMAKE_SOURCE_DIR}/opencv)
