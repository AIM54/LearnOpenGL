package com.bian.learnopengl.nativeutil;

import android.content.res.AssetManager;

public class GLSurfaceViewRender {
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
        System.loadLibrary("androidGL");
    }

    public native void onSurfaceCreated(AssetManager assetManager);

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
