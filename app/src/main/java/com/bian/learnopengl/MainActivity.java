package com.bian.learnopengl;

import android.content.Intent;
import android.opengl.GLES31;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.bian.learnopengl.activity.GLSurfaceActivity;

import java.nio.IntBuffer;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button testOpenglButton;
    private Button testGLButton;
    private IntBuffer buffers;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        buffers = IntBuffer.allocate(10);
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
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2) {
                    GLES31.glGenVertexArrays(1, buffers);
                }
                it.setClass(this, OpenglActivity.class);
                break;
            case R.id.bt_test_glsurface:
                it.setClass(this, GLSurfaceActivity.class);
                break;
        }
        startActivity(it);
    }
}
