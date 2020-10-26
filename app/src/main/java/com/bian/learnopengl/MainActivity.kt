package com.bian.learnopengl

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.view.LayoutInflater
import android.widget.AdapterView
import android.widget.ArrayAdapter
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.databinding.DataBindingUtil
import com.bian.learnopengl.activity.ImageListActivity
import com.bian.learnopengl.activity.OpenglActivity
import com.bian.learnopengl.activity.VideoListActivity
import com.bian.learnopengl.databinding.ActivityMainBinding
import com.bian.learnopengl.util.CommonUtils
import com.bian.learnopengl.util.ConstantUtil
import kotlinx.coroutines.*
import java.io.File

class MainActivity : AppCompatActivity() {
    private var mBinder: ActivityMainBinding? = null
    val scope = MainScope() + CoroutineName("MyActivity");
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mBinder = DataBindingUtil.bind(LayoutInflater.from(this).inflate(R.layout.activity_main, null))
        setContentView(mBinder?.root)
        setAdapter();
    }

    private fun setAdapter() {
        val data = arrayOf("TestOpencvModule", "opencvVideoFunction", "testModelLoader")
        val simpleAdapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, data)
        mBinder?.adapter = simpleAdapter
        mBinder?.lvMain?.onItemClickListener = AdapterView.OnItemClickListener { parent, view, position, id ->
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE), 110);
                return@OnItemClickListener;
            }
            when (position) {
                0 -> startActivity(Intent(this@MainActivity, ImageListActivity::class.java))
                1 -> startActivity(Intent(this@MainActivity, VideoListActivity::class.java))
                2 -> copyDataBase()
            }
        }
    }

    private fun copyDataBase() {
        scope.launch {
            val targetPath = "${externalCacheDir}${File.separator}Models"
            withContext(Dispatchers.IO) {
                CommonUtils.copyAssetsDirToSDCard(this@MainActivity, "3dmodel${File.separator}nanosuit", targetPath);
            }
            val it = Intent(this@MainActivity, OpenglActivity::class.java)
            it.putExtra(ConstantUtil.ARG_FILE_PATH, targetPath);
            startActivity(it)
        }
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == 100 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            copyDataBase()
        }
    }
}


