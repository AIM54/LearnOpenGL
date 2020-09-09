package com.bian.learnopengl.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;

import com.bian.learnopengl.R;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenglActivity extends AppCompatActivity implements GLSurfaceView.Renderer {
    private GLSurfaceView mainGlSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opengl2);
        mainGlSurfaceView = findViewById(R.id.glsv_main);
        mainGlSurfaceView.setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        mainGlSurfaceView.setEGLContextClientVersion(3);
        mainGlSurfaceView.setRenderer(this);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }
}