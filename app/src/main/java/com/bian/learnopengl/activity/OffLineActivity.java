package com.bian.learnopengl.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.bian.learnopengl.R;
import com.bian.learnopengl.nativeutil.MyRender;
import com.bian.learnopengl.util.ConstantUtil;

import io.reactivex.Observable;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.schedulers.Schedulers;

public class OffLineActivity extends AppCompatActivity {

    private MyRender myRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_off_line);
        myRender = new MyRender();
        myRender.drawOffScreen(getAssets());

    }
}