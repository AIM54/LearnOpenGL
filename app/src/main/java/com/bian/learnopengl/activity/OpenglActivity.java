package com.bian.learnopengl.activity;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.Surface;

import com.bian.learnopengl.MySurfaceView;
import com.bian.learnopengl.R;
import com.bian.learnopengl.base.BaseActivity;
import com.bian.learnopengl.nativeutil.MyRender;
import com.bian.learnopengl.util.ConstantUtil;

import java.io.File;

public class OpenglActivity extends BaseActivity implements MySurfaceView.Render {
    private MySurfaceView surfaceView;
    private MyRender myRender;
    private String modelFilePath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opengl);
        initView();
        modelFilePath = getIntent().getStringExtra(ConstantUtil.ARG_FILE_PATH);
        if (!TextUtils.isEmpty(modelFilePath)) {
            myRender = new MyRender(getAssets(), modelFilePath + File.separator + "nanosuit" + File.separator + "nanosuit.obj");
            return;
        }
        myRender = new MyRender(10, getAssets(), getIntent().getStringExtra(ConstantUtil.ARG_IMG));
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