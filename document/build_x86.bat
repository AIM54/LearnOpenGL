
@echo off
cls

REM *NOTE* Change these based on 
SET ASSIMP_DIR=assimp
SET OUTPUT_DIR=assimp-build-x86
SET ANDROID_PATH=D:\Android\Sdk
SET NDK_PATH=D:\Android\Sdk\ndk-bundle
SET NDK_TOOLCHAIN=%~dp0aandroid-toolchain-24-llvm-x86
SET CMAKE_TOOLCHAIN=%NDK_PATH%\build\cmake\android.toolchain.cmake
SET CMAKE_PATH=%ANDROID_PATH%\cmake\3.6.4111459

REM *NOTE* Careful if you don't want rm -rf, I use it for testing purposes.
del /F /S /Q %OUTPUT_DIR%
mkdir %OUTPUT_DIR%

REM pushd doesn't seem to work ):<
cd %OUTPUT_DIR%

if not defined ORIGPATH set ORIGPATH=%PATH%
SET PATH=%CMAKE_PATH%\bin;%ANDROID_PATH%\tools;%ANDROID_PATH%\platform-tools;%ORIGPATH%

cmake ^
      -GNinja ^
      -DCMAKE_TOOLCHAIN_FILE=%CMAKE_TOOLCHAIN% ^
      -DASSIMP_ANDROID_JNIIOSYSTEM=ON ^
      -DANDROID_NDK=%NDK_PATH% ^
      -DCMAKE_MAKE_PROGRAM=%CMAKE_PATH%\bin\ninja.exe ^
      -DCMAKE_BUILD_TYPE=Release ^
      -DANDROID_ABI="x86" ^
      -DANDROID_NATIVE_API_LEVEL=24 ^
      -DCMAKE_INSTALL_PREFIX=install ^
      -DANDROID_STL=c++_static ^
      -DCMAKE_CXX_FLAGS=-Wno-c++11-narrowing ^
      -DANDROID_TOOLCHAIN=clang ^

      -DASSIMP_BUILD_TESTS=OFF ^

      ../%ASSIMP_DIR%

cmake --build .

cd ..

pause