package com.bian.learnopengl.nativeutil;

public class OpenCvUtil {
    static {
        System.loadLibrary("opencv_test");
    }


    public native void loadImage(String imagePath);

    public native void anlyisVideo(String videoPath);
}
