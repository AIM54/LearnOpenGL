package com.bian.learnopengl.nativeutil;

import android.view.Surface;

public class MyRender {
    public native int init();

    public native int setSurface(Surface surface, int width, int height);

    public native int draw();

    public native int pause();

    public native int resume();

}