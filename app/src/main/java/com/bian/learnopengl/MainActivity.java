package com.bian.learnopengl;

import android.content.Intent;
import android.opengl.GLES31;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.bian.learnopengl.activity.GLSurfaceActivity;
import com.bian.learnopengl.activity.ImageListActivity;

import java.nio.IntBuffer;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button testOpenglButton;
    private Button testGLButton;
    private Button imageListButton;
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
        imageListButton = findViewById(R.id.bt_image_list);
        testOpenglButton.setOnClickListener(this);
        testGLButton.setOnClickListener(this);
        imageListButton.setOnClickListener(this);
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

            case R.id.bt_image_list:
                it.setClass(this, ImageListActivity.class);
                break;
        }
        startActivity(it);
    }
}
