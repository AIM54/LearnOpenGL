package com.bian.learnopengl.activity;

import android.os.Bundle;

import com.bian.learnopengl.R;
import com.bian.learnopengl.base.BaseActivity;
import com.bian.learnopengl.nativeutil.MyRender;

public class OffLineActivity extends BaseActivity {

    private MyRender myRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_off_line);
        myRender = new MyRender();
        myRender.drawOffScreen(getAssets());
    }
}