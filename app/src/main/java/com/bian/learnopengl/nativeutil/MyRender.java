package com.bian.learnopengl.nativeutil;

import android.view.Surface;

public class MyRender {
    static {
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("postproc");
        System.loadLibrary("avutil");
        System.loadLibrary("avformat");
        System.loadLibrary("avfilter");
        System.loadLibrary("avdevice");
        System.loadLibrary("avcodec");
        System.loadLibrary("assimp");
        System.loadLibrary("native-lib");
    }

    public native int init(Surface surface);

    public native int onSizeChanged(int width, int height);

    public native int draw();

    public native int pause();

    public native int resume();

    public native int destroy();
}