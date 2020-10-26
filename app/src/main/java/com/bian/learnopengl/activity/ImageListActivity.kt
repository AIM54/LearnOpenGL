package com.bian.learnopengl.activity

import android.content.Intent
import android.database.Cursor
import android.os.Bundle
import android.provider.MediaStore
import android.view.View
import android.widget.AdapterView
import android.widget.AdapterView.OnItemClickListener
import androidx.cursoradapter.widget.SimpleCursorAdapter
import androidx.loader.app.LoaderManager
import androidx.loader.content.CursorLoader
import androidx.loader.content.Loader
import com.bian.learnopengl.R
import com.bian.learnopengl.base.BaseActivity
import com.bian.learnopengl.nativeutil.OpenCvUtil
import com.bian.learnopengl.util.ConstantUtil
import kotlinx.android.synthetic.main.activity_image_list.*
import kotlinx.coroutines.CoroutineName
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.plus

class ImageListActivity : BaseActivity(), LoaderManager.LoaderCallbacks<Cursor>, OnItemClickListener {
    private var mCursorAdapter: SimpleCursorAdapter? = null
    private val project = arrayOf(
            MediaStore.Images.Media._ID,
            MediaStore.Images.Media.DATA,
            MediaStore.Images.Media.DISPLAY_NAME
    )
    private var openCvUtil: OpenCvUtil? = null
    val scope = MainScope() + CoroutineName("ImageListActivity");

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_image_list)
        initData()
        openCvUtil = OpenCvUtil()
    }

    private fun initData() {
        val manager = LoaderManager.getInstance(this)
        manager.initLoader(110, null, this)
    }

    override fun onCreateLoader(i: Int, bundle: Bundle?): Loader<Cursor> {
        return CursorLoader(this, MediaStore.Images.Media.EXTERNAL_CONTENT_URI, project, null, null, null)
    }

    override fun onLoadFinished(loader: Loader<Cursor>, data: Cursor) {
        mCursorAdapter = SimpleCursorAdapter(this,
                android.R.layout.simple_list_item_1,
                data, arrayOf(MediaStore.Images.Media.DISPLAY_NAME), intArrayOf(android.R.id.text1), 0)
        lv_main?.adapter = mCursorAdapter
        lv_main?.onItemClickListener = this
    }

    override fun onLoaderReset(loader: Loader<Cursor>) {}
    override fun onItemClick(parent: AdapterView<*>?, view: View, position: Int, id: Long) {
        val cursor = mCursorAdapter!!.getItem(position) as Cursor
        val path = cursor.getString(cursor.getColumnIndex(MediaStore.Images.Media.DATA))
        val it = Intent(this, OpenglActivity::class.java)
        it.putExtra(ConstantUtil.ARG_IMG, path);
        startActivity(it)
    }
}