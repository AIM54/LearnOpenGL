package com.bian.learnopengl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.bian.learnopengl.activity.GLSurfaceActivity;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button testOpenglButton;
    private Button testGLButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    private void initView() {
        testOpenglButton = findViewById(R.id.bt_test_opengl);
        testGLButton = findViewById(R.id.bt_test_glsurface);
        testOpenglButton.setOnClickListener(this);
        testGLButton.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent it = new Intent();
        switch (v.getId()) {
            case R.id.bt_test_opengl:
                it.setClass(this, OpenglActivity.class);
                break;
            case R.id.bt_test_glsurface:
                it.setClass(this, GLSurfaceActivity.class);
                break;
        }
        startActivity(it);
    }
}
