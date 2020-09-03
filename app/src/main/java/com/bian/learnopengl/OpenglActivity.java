package com.bian.learnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.view.Surface;

import com.bian.learnopengl.util.LogUtils;

public class OpenglActivity extends AppCompatActivity implements MySurfaceView.Render {
    private MySurfaceView surfaceView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opengl);
        initView();
    }

    private void initView() {
        surfaceView = findViewById(R.id.msfv_main);
        surfaceView.setRender(this);
    }


    @Override
    protected void onPause() {
        super.onPause();
        LogUtils.logMessageI("onPause");
    }

    @Override
    protected void onResume() {
        super.onResume();
        LogUtils.logMessageI("onResume");
    }


    @Override
    public void onSurfaceCreate(Surface surface) {
        LogUtils.logMessageI("onSurfaceCreate1");
    }

    @Override
    public void onSizeChanged(int width, int height) {
        LogUtils.logMessageI("onSizeChanged1");
    }

    @Override
    public void onDraw() {
        LogUtils.logMessageI("onDraw1");
    }

    @Override
    public void onRelease() {
        LogUtils.logMessageI("onRelease1");
    }
}