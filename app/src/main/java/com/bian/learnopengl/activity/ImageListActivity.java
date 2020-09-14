package com.bian.learnopengl.activity;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.cursoradapter.widget.SimpleCursorAdapter;
import androidx.loader.app.LoaderManager;
import androidx.loader.content.CursorLoader;
import androidx.loader.content.Loader;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

import com.bian.learnopengl.OpenglActivity;
import com.bian.learnopengl.R;
import com.bian.learnopengl.util.ConstantUtil;
import com.bian.learnopengl.util.LogUtils;

public class ImageListActivity extends AppCompatActivity implements LoaderManager.LoaderCallbacks<Cursor>, AdapterView.OnItemClickListener {
    private SimpleCursorAdapter mCursorAdapter;
    private String project[] = new String[]{
            MediaStore.Images.Media._ID,
            MediaStore.Images.Media.DATA,
            MediaStore.Images.Media.DISPLAY_NAME
    };
    private ListView mListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_list);
        mListView = findViewById(R.id.lv_main);
        initData();
    }

    private void initData() {
        LoaderManager manager = LoaderManager.getInstance(this);
        manager.initLoader(110, null, this);
    }

    @NonNull
    @Override
    public Loader<Cursor> onCreateLoader(int i, @Nullable Bundle bundle) {
        CursorLoader cursorLoader = new CursorLoader(this, MediaStore.Images.Media.EXTERNAL_CONTENT_URI, project, null, null, null);
        return cursorLoader;
    }

    @Override
    public void onLoadFinished(@NonNull Loader<Cursor> loader, Cursor data) {
        mCursorAdapter = new SimpleCursorAdapter(this,
                android.R.layout.simple_list_item_1,
                data,
                new String[]{MediaStore.Images.Media.DISPLAY_NAME},
                new int[]{android.R.id.text1}, 0);
        mListView.setAdapter(mCursorAdapter);
        mListView.setOnItemClickListener(this);

    }

    @Override
    public void onLoaderReset(@NonNull Loader<Cursor> loader) {

    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        final Cursor cursor = (Cursor) mCursorAdapter.getItem(position);
        Intent it = new Intent(this, OpenglActivity.class);
        String path = cursor.getString(cursor.getColumnIndex(MediaStore.Images.Media.DATA));
        LogUtils.logMessageI(path);
        it.putExtra(ConstantUtil.ARG_IMG, path);
        startActivity(it);

    }
}