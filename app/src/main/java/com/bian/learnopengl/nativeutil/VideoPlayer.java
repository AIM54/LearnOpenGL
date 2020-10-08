package com.bian.learnopengl.nativeutil;

import android.view.Surface;

public class VideoPlayer {

    public native void setSurface(Surface surface);

    public native void startAsync(String videoPath);

    public native void start();

    public native void pause();

    public native void resume();

    public native void stop();

}
