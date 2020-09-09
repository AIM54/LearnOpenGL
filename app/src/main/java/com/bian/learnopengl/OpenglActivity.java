package com.bian.learnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.view.Surface;

import com.bian.learnopengl.nativeutil.MyRender;

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
    }

    @Override
    protected void onResume() {
        super.onResume();
    }


    @Override
    public void onSurfaceCreate(Surface surface) {
        myRender.initSurface(surface);
    }

    @Override
    public void onSizeChanged(int width, int height) {
        myRender.onSizeChanged(width, height);
    }

    @Override
    public void onDraw() {
        myRender.draw();
    }

    @Override
    public void onRelease() {
        myRender.destroyView();
    }
}