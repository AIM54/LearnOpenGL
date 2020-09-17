//
// Created by tom1 on 2020/9/7.
//

#include <gl3stub.h>

#include "PictureDrawer.h"

#define  VERTEX_POS_INDEX 0
#define  VERTEX_POS_SIZE  3

#define  COLOR_POS_INDEX  1
#define  COLOR_POS_SIZE   4


#define  TEX_POS_INDEX  2
#define  TEX_POS_SIZE   2


#define  VERTEX_STRIDE (sizeof(GLfloat)*(VERTEX_POS_SIZE+COLOR_POS_SIZE+TEX_POS_SIZE))

PictureDrawer::PictureDrawer(AAssetManager *manager,
                             const char *imagePath) : BaseRender(manager) {
    imageData = nullptr;
    if (imagePath) {
        ALOGI("imagePath:%s", imagePath);
        FILE *file = fopen(imagePath, "rb");
        if (!file) {
            return;
        }
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
        ALOGI("png_init_io");
        //开始读文件
        png_init_io(png_ptr, file);

        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
        //获取文件的宽高色深
        image_width = png_get_image_width(png_ptr, info_ptr);
        image_height = png_get_image_height(png_ptr, info_ptr);
        //获取图像的色彩类型
        int color_type = png_get_color_type(png_ptr, info_ptr);
        int picChannel = png_get_channels(png_ptr, info_ptr);
        int bitDepth = png_get_bit_depth(png_ptr, info_ptr);
        ALOGI("width=%d,height=%d,color_type=%d,bitDepth=:%d,channel=%d", image_width, image_height,
              color_type,
              bitDepth, picChannel);
        png_bytep *row_pointers = png_get_rows(png_ptr, info_ptr);
        if (color_type == PNG_COLOR_TYPE_RGBA) {
            int pos = 0;
            imageData = new uint8_t[image_width * image_height * picChannel];
            for (int i = 0; i < image_height; i++) {
                for (int j = 0; j < (picChannel * image_width); j += picChannel) {
                    imageData[pos++] = row_pointers[i][j];   // red
                    imageData[pos++] = row_pointers[i][j + 1]; // green
                    imageData[pos++] = row_pointers[i][j + 2]; // blue
                    imageData[pos++] = row_pointers[i][j + 3]; // alpha
                }
            }
        }
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        fclose(file);
    }
    verticalShader = readStringFromAssert(manager, "shaders/FirstPicVerticalShader.glsl");
    fragmentShader = readStringFromAssert(manager, "shaders/FirstPicFragmentShader.glsl");
}

int PictureDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    if (!BaseRender::initSurface(jniEnv, surface)) {
        return GL_FALSE;
    }
    if (!gl3stubInit()) {
        return GL_FALSE;
    }
    mProgram = esLoadProgram(verticalShader, fragmentShader);
    GLfloat verticals[] = {
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };
    GLushort indics[] = {0, 1, 2, 2, 1, 3};
    glGenBuffers(2, mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indics), indics, GL_STATIC_DRAW);
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
    glEnableVertexAttribArray(VERTEX_POS_INDEX);
    glEnableVertexAttribArray(COLOR_POS_INDEX);
    glEnableVertexAttribArray(TEX_POS_INDEX);

    glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) 0);
    glVertexAttribPointer(COLOR_POS_INDEX, COLOR_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) (sizeof(GLfloat) * VERTEX_POS_SIZE));
    glVertexAttribPointer(TEX_POS_INDEX, TEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) (sizeof(GLfloat) * (VERTEX_POS_SIZE + COLOR_POS_SIZE)));

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (imageData) {
        delete[]imageData;
    }
    GLint texLocation = glGetUniformLocation(mProgram, "ourTexture");
    glUniform1i(texLocation, 0);
    glBindVertexArray(0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    return GL_TRUE;
}


int PictureDrawer::draw() {
    glViewport(0, 0, getWidth(), getHeight());
    glUseProgram(mProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(0);
    eglSwapBuffers(eglDisplay, eglSurface);
    return GL_TRUE;
}

int PictureDrawer::destroyView() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteProgram(mProgram);
    glDeleteBuffers(2, mVBO);
    glDeleteVertexArrays(1, &mVAO);
    return GL_TRUE;
}
