package com.bian.learnopengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.recyclerview.widget.RecyclerView;

import java.lang.ref.WeakReference;


public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    private MyRenderThread renderThread;
    private Object mRenderManager = new Object();
    private Render mRender;
    private RecyclerView recyclerView;

    private int threadCount;

    public interface Render {
        void onSurfaceCreate(Surface surface);

        void onSizeChanged(int width, int height);

        void onDraw();

        void onRelease();

    }

    public MySurfaceView(Context context) {
        this(context, null);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
    }

    public void setRender(Render mRender) {
        this.mRender = mRender;
        init();
    }


    private void init() {
        renderThread = new MyRenderThread();
        renderThread.start();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if (renderThread != null) {
            if (renderThread.mShouldExit) {
                renderThread = new MyRenderThread();
                renderThread.start();
            }
            renderThread.setSurface(holder.getSurface());
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if (renderThread != null) {
            renderThread.onWindowsChanged(width, height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if (renderThread != null) {
            renderThread.onDestroy();
        }
    }


    public void onPause() {
        renderThread.onPause();
    }

    public void onResume() {
        renderThread.onResume();
    }

    private class MyRenderThread extends Thread {
        private int mHeight;
        private int mWidth;
        private boolean mInitSurface;
        private boolean hasSurface;
        private boolean mPaused;
        private boolean mShouldExit;
        private boolean mSizeChanged;

        private WeakReference<Surface> mSurfaceReference;


        @Override
        public void run() {
            setName("MyRenderThread--" + threadCount++);
            try {
                looperForRender();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        private void looperForRender() throws InterruptedException {
            while (true) {
                synchronized (mRenderManager) {
                    if (mShouldExit) {
                        break;
                    }
                    if (mInitSurface) {
                        mRender.onSurfaceCreate(mSurfaceReference.get());
                        mInitSurface = false;
                    }
                    if (mSizeChanged) {
                        mRender.onSizeChanged(mWidth, mHeight);
                        mSizeChanged = false;
                    }
                    if (readyForDraw()) {
                        mRender.onDraw();
                    }
                }
            }
            mRender.onRelease();
        }

        private boolean readyForDraw() {
            return mWidth > 0 &&
                    mHeight > 0 &&
                    hasSurface &&
                    !mPaused &&
                    !mShouldExit;
        }

        public void setSurface(Surface surface) {
            mSurfaceReference = new WeakReference<>(surface);
            hasSurface = true;
            mInitSurface = true;
        }

        public void onWindowsChanged(int width, int height) {
            mWidth = width;
            mHeight = height;
            mSizeChanged = true;
        }

        public void onPause() {
            mPaused = true;
        }

        public void onResume() {
            mPaused = false;
        }

        public void onDestroy() {
            mShouldExit = true;
            hasSurface = false;
            mInitSurface = false;
            mWidth = 0;
            mHeight = 0;
        }
    }
}
