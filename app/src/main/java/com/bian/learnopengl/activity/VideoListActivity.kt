package com.bian.learnopengl.activity

import android.database.Cursor
import android.os.Bundle
import android.provider.MediaStore
import android.view.LayoutInflater
import android.widget.AdapterView.OnItemClickListener
import androidx.cursoradapter.widget.SimpleCursorAdapter
import androidx.databinding.DataBindingUtil
import androidx.loader.app.LoaderManager
import androidx.loader.content.CursorLoader
import androidx.loader.content.Loader
import com.bian.learnopengl.R
import com.bian.learnopengl.base.BaseActivity
import com.bian.learnopengl.databinding.ActivityVideoListBinding
import com.bian.learnopengl.nativeutil.OpenCvUtil
import com.bian.learnopengl.util.LogUtils
import kotlinx.coroutines.CoroutineName
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.plus

class VideoListActivity : BaseActivity(), LoaderManager.LoaderCallbacks<Cursor> {
    private var mCursorAdapter: SimpleCursorAdapter? = null
    private val project = arrayOf(
            MediaStore.Video.Media._ID,
            MediaStore.Video.Media.DATA,
            MediaStore.Video.Media.DISPLAY_NAME
    )
    private var binding: ActivityVideoListBinding? = null
    private var openCvUtil: OpenCvUtil? = null
    val scope = MainScope() + CoroutineName("VideoListActivity");

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.bind(LayoutInflater.from(this).inflate(R.layout.activity_video_list, null))
        setContentView(binding?.root)
        initData()
    }

    private fun initData() {
        openCvUtil = OpenCvUtil()
        val manager = LoaderManager.getInstance(this)
        manager.initLoader(110, null, this)
    }

    override fun onCreateLoader(id: Int, args: Bundle?): Loader<Cursor> {
        return CursorLoader(this, MediaStore.Video.Media.EXTERNAL_CONTENT_URI, project, null, null, null)
    }

    override fun onLoadFinished(loader: Loader<Cursor>, data: Cursor) {
        mCursorAdapter = SimpleCursorAdapter(this,
                android.R.layout.simple_list_item_1,
                data, arrayOf(MediaStore.Video.Media.DISPLAY_NAME), intArrayOf(android.R.id.text1), 0)
        binding?.videoAdapter = mCursorAdapter
        binding?.lvVideo?.onItemClickListener = OnItemClickListener { parent, view, position, id ->
            LogUtils.logMessageI("Position:${position}")
            val cursor = mCursorAdapter?.getItem(position) as Cursor
            val path = cursor.getString(cursor.getColumnIndex( MediaStore.Video.Media.DATA))
        }

    }

    override fun onLoaderReset(loader: Loader<Cursor>) {}

    private fun beginOpenVideo(path: String) {
        LogUtils.logMessageI("path:${path}")

    }
}