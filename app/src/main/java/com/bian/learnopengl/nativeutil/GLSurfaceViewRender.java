package com.bian.learnopengl.nativeutil;

public class GLSurfaceViewRender {
    static {
        System.loadLibrary("assimp");
        System.loadLibrary("gltest");
    }

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
