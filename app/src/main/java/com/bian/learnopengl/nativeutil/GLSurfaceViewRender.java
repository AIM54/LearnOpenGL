package com.bian.learnopengl.nativeutil;

import android.content.res.AssetManager;

public class GLSurfaceViewRender {
    static {
        System.loadLibrary("assimp");
        System.loadLibrary("androidGL");
    }

    public native void onSurfaceCreated(AssetManager assetManager);

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
