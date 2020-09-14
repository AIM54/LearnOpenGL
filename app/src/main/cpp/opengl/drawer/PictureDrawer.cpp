//
// Created by tom1 on 2020/9/7.
//

#include "png.h"
#include "zlib.h"
#include "PictureDrawer.h"

#define PNG_BYTES_TO_CHECK    8
#define HAVE_ALPHA            1
#define NOT_HAVE_ALPHA        0

PictureDrawer::PictureDrawer(AAssetManager *manager,
                             const char *imagePath) : BaseRender(manager) {
    if (imagePath) {
        ALOGI("imagePath:%s", imagePath);
        FILE *imageFile = fopen(imagePath, "wb");
        png_structp structp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!structp) {
            ALOGI("!structp");
            fclose(imageFile);
            return;
        }
        png_infop infop = png_create_info_struct(structp);
        if (!infop) {
            ALOGI("!infop");
            png_destroy_write_struct(&structp, nullptr);
            fclose(imageFile);
            return;
        }
        int iRetVal = setjmp(png_jmpbuf(structp));//安装错误处理跳转点
//当libpng内部出现错误的时候，libpng会调用longjmp直接跳转到这里运行。
        if (iRetVal)//setjmp的返回值就是libpng跳转后提供的错误代码（貌似总是1，但是还是请大家看libpng的官方文档）
        {
            ALOGI("错误码：%d\n", iRetVal);
            return;
        }
        ALOGI("png_init_io");
        png_init_io(structp, imageFile);
        png_read_png(structp, infop, PNG_TRANSFORM_EXPAND, 0);
        int channels = png_get_channels(structp, infop);
        int colorType = png_get_color_type(structp, infop);
        int width = png_get_image_width(structp, infop);
        int height = png_get_image_height(structp, infop);
        ALOGI("channels:%d,colorType:%d,width:%d,height:%d", channels, colorType, width, height);
        png_destroy_read_struct(&structp, &infop, 0);
        fclose(imageFile);
    }
}

int PictureDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    return GL_TRUE;
}

int PictureDrawer::draw() {
    return GL_TRUE;
}
