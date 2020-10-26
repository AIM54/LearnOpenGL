package com.bian.learnopengl.activity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;

import com.bian.learnopengl.R;
import com.bian.learnopengl.base.BaseActivity;
import com.bian.learnopengl.nativeutil.GLSurfaceViewRender;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLSurfaceActivity extends BaseActivity implements GLSurfaceView.Renderer {
    private GLSurfaceView mainGlSurfaceView;
    private GLSurfaceViewRender glSurfaceViewRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_opengl2);
        glSurfaceViewRender = new GLSurfaceViewRender();
        mainGlSurfaceView = findViewById(R.id.glsv_main);
        mainGlSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        mainGlSurfaceView.setEGLContextClientVersion(3);
        mainGlSurfaceView.setRenderer(this);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        glSurfaceViewRender.onSurfaceCreated(getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        glSurfaceViewRender.onSurfaceChanged(width, height);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mainGlSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mainGlSurfaceView.onResume();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        glSurfaceViewRender.onDrawFrame();
    }
}