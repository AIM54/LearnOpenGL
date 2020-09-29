package com.bian.learnopengl.nativeutil;

import android.view.Surface;

public class VideoRecorder {
    public native void setSurface(Surface surface);

    public native void startPreview();

    public native void onPause();

    public native void onResume();

    public native void beginRecord();

    public native void stopRecord();

    public native void setOutputFile();

    public native void setVideoBitrate(int bitrate);

    public native void setVideoHeight(int videoHeight);

    public native void setVideoWidth(int videoHeight);
}
