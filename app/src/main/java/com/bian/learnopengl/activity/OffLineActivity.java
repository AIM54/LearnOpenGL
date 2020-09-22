package com.bian.learnopengl.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.bian.learnopengl.R;
import com.bian.learnopengl.nativeutil.MyRender;
import com.bian.learnopengl.util.ConstantUtil;

public class OffLineActivity extends AppCompatActivity {

    private MyRender myRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_off_line);
        myRender = new MyRender(12, getAssets(), getIntent().getStringExtra(ConstantUtil.ARG_IMG));
        myRender.drawOffScreen(getAssets());
    }
}