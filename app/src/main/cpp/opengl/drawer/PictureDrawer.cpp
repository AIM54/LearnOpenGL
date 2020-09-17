//
// Created by tom1 on 2020/9/7.
//

#include "png.h"
#include "zlib.h"
#include "PictureDrawer.h"

PictureDrawer::PictureDrawer(AAssetManager *manager,
                             const char *imagePath) : BaseRender(manager) {
    if (imagePath) {
        ALOGI("imagePath:%s", imagePath);
        FILE *file = fopen(imagePath, "rb");
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        if (png_ptr == NULL) {
            fclose(file);
            return;
        }
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL) {
            fclose(file);
            png_destroy_write_struct(&png_ptr, NULL);
            return;
        }
        if (setjmp(png_jmpbuf(png_ptr))) {
            fclose(file);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            ALOGI("onDestroy");
            return;
        }
        //开始读文件
        png_init_io(png_ptr, file);

        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

        //获取文件的宽高色深
        int m_width = png_get_image_width(png_ptr, info_ptr);
        int m_height = png_get_image_height(png_ptr, info_ptr);

        //获取图像的色彩类型
        int color_type = png_get_color_type(png_ptr, info_ptr);

        ALOGI("width=%d,height=%d,color_type=%d", m_width, m_height, color_type);

        // row_pointers内部存放的就是RGBA数据了
        png_bytep *row_pointers = png_get_rows(png_ptr, info_ptr);

        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        fclose(file);
    }
}

int PictureDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    return GL_TRUE;
}

int PictureDrawer::draw() {
    return GL_TRUE;
}
