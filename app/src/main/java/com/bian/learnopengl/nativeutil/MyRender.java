package com.bian.learnopengl.nativeutil;

import android.content.res.AssetManager;
import android.view.Surface;

public class MyRender {

    public int renderType;
    private AssetManager assetManager;

    public MyRender(AssetManager assetManager) {
        this(12, assetManager);
    }

    public MyRender(int renderType, AssetManager assetManager) {
        this.renderType = renderType;
        this.assetManager = assetManager;
        init(assetManager);
    }


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
        System.loadLibrary("gltest");
    }

    public native void init(AssetManager assetManager);


    public native int initSurface(Surface surface);

    public native int onSizeChanged(int width, int height);

    public native int draw();

    public native int pause();

    public native int resume();

    public native int destroyView();

    @Override
    protected void finalize() throws Throwable {
        super.finalize();

    }
}