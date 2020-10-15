package com.bian.learnopengl.activity;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import android.os.Bundle;
import android.view.LayoutInflater;

import com.bian.learnopengl.R;
import com.bian.learnopengl.databinding.ActivityVideoList2Binding;

public class VideoListActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityVideoList2Binding binding = ActivityVideoList2Binding.inflate(LayoutInflater.from(this));
        setContentView(binding.getRoot());
    }
}