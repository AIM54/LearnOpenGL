package com.bian.learnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.view.Surface;

import com.bian.learnopengl.nativeutil.MyRender;
import com.bian.learnopengl.util.LogUtils;

public class OpenglActivity extends AppCompatActivity implements MySurfaceView.Render {
    private MySurfaceView surfaceView;
    private MyRender myRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opengl);
        initView();
        myRender = new MyRender(getAssets());
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
        myRender.initSurface(surface);
    }

    @Override
    public void onSizeChanged(int width, int height) {
        LogUtils.logMessageI("onSizeChanged1");
        myRender.onSizeChanged(width, height);
    }

    @Override
    public void onDraw() {
        LogUtils.logMessageI("onDraw1");
        myRender.draw();
    }

    @Override
    public void onRelease() {
        LogUtils.logMessageI("onRelease");
        myRender.destroyView();
    }
}