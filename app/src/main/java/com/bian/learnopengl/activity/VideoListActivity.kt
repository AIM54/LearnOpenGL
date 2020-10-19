package com.bian.learnopengl.activity

import android.R
import android.database.Cursor
import android.os.Bundle
import android.provider.MediaStore
import android.view.LayoutInflater
import android.widget.AdapterView.OnItemClickListener
import androidx.appcompat.app.AppCompatActivity
import androidx.cursoradapter.widget.SimpleCursorAdapter
import androidx.loader.app.LoaderManager
import androidx.loader.content.CursorLoader
import androidx.loader.content.Loader
import com.bian.learnopengl.databinding.ActivityVideoList2Binding
import com.bian.learnopengl.nativeutil.OpenCvUtil
import com.bian.learnopengl.util.LogUtils
import kotlinx.coroutines.*

class VideoListActivity : AppCompatActivity(), LoaderManager.LoaderCallbacks<Cursor> {
    private var mCursorAdapter: SimpleCursorAdapter? = null
    private val project = arrayOf(
            MediaStore.Video.Media._ID,
            MediaStore.Video.Media.DATA,
            MediaStore.Video.Media.DISPLAY_NAME
    )
    private var binding: ActivityVideoList2Binding? = null
    private var openCvUtil: OpenCvUtil? = null
    val scope = MainScope() + CoroutineName("VideoListActivity");

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityVideoList2Binding.inflate(LayoutInflater.from(this))
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
                R.layout.simple_list_item_1,
                data, arrayOf(MediaStore.Video.Media.DISPLAY_NAME), intArrayOf(R.id.text1), 0)
        binding?.videoAdapter = mCursorAdapter
        binding!!.lvMain!!.onItemClickListener = OnItemClickListener { parent, view, position, id ->
            LogUtils.logMessageI("Position:${position}")
            val cursor = mCursorAdapter?.getItem(position) as Cursor
            val path = cursor.getString(cursor.getColumnIndex(MediaStore.Video.Media.DATA))
            beginOpenVideo(path)
        }

    }

    override fun onLoaderReset(loader: Loader<Cursor>) {}

    private fun beginOpenVideo(path: String) {
        LogUtils.logMessageI("path:${path}")
        scope.launch {
            withContext(Dispatchers.IO) {
                openCvUtil?.anlyisVideo(path)
            }
        }

    }
}