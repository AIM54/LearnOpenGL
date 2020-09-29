package com.bian.learnopengl.activity

import android.graphics.ImageFormat
import android.hardware.Camera
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.SurfaceHolder
import com.bian.learnopengl.R
import kotlinx.android.synthetic.main.activity_video_record.*

class VideoRecordActivity : AppCompatActivity(), SurfaceHolder.Callback {
    var mCamera: Camera? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_video_record)
        initCamera();
    }

    private fun initCamera() {
        mCamera = Camera.open(Camera.CameraInfo.CAMERA_FACING_BACK);
        var cameraParam = mCamera?.parameters
        cameraParam?.let {
            if (it.supportedPreviewFormats.contains(ImageFormat.NV21)) {
                it.previewFormat = ImageFormat.NV21
            }
        }
        mCamera?.parameters = cameraParam;
        camera_preview.holder.addCallback(this)
    }

    override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {

    }

    override fun surfaceDestroyed(holder: SurfaceHolder?) {

    }

    override fun surfaceCreated(holder: SurfaceHolder?) {
    }
}