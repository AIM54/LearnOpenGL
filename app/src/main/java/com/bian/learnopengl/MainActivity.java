package com.bian.learnopengl;

import android.Manifest;
import android.content.Intent;
import android.opengl.GLES31;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import com.bian.learnopengl.activity.GLSurfaceActivity;
import com.bian.learnopengl.activity.ImageListActivity;
import com.bian.learnopengl.activity.OffLineActivity;

import java.nio.IntBuffer;

import static android.content.pm.PackageManager.PERMISSION_GRANTED;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button testOpenglButton;
    private Button testGLButton;
    private Button imageListButton;
    private Button offlineDrawer;
    private IntBuffer buffers;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    private void initView() {
        testOpenglButton = findViewById(R.id.bt_test_opengl);
        testGLButton = findViewById(R.id.bt_test_glsurface);
        imageListButton = findViewById(R.id.bt_image_list);
        offlineDrawer = findViewById(R.id.bt_offline);
        testOpenglButton.setOnClickListener(this);
        testGLButton.setOnClickListener(this);
        imageListButton.setOnClickListener(this);
        offlineDrawer.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 110);
            return;
        }
        Intent it = new Intent();
        switch (v.getId()) {
            case R.id.bt_test_opengl:
                it.setClass(this, OpenglActivity.class);
                break;
            case R.id.bt_test_glsurface:
                it.setClass(this, GLSurfaceActivity.class);
                break;

            case R.id.bt_image_list:
                it.setClass(this, ImageListActivity.class);
                break;
            case R.id.bt_offline:
                it.setClass(this, OffLineActivity.class);
                break;
        }
        startActivity(it);
    }
}
