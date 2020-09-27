package com.bian.learnopengl

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.bian.learnopengl.util.CommonUtils
import com.bian.learnopengl.util.ConstantUtil
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.*
import java.io.File

class MainActivity : AppCompatActivity() {
    val scope = MainScope() + CoroutineName("MyActivity");
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        initEvent();
    }

    private fun initEvent() {
        bt_load_model.setOnClickListener { copyDataBase() }
    }

    private fun copyDataBase() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE), 110);
            return
        }
        scope.launch {
            val targetPath="${externalCacheDir}${File.separator}Models"
            withContext(Dispatchers.IO) {
                CommonUtils.copyAssetsDirToSDCard(this@MainActivity, "3dmodel${File.separator}nanosuit", targetPath);
            }
            val it=Intent(this@MainActivity,OpenglActivity::class.java)
            it.putExtra(ConstantUtil.ARG_FILE_PATH,targetPath);
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


