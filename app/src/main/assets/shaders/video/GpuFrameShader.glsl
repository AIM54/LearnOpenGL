#version 300 es
#extension GL_OES_EGL_image_external : require
precision mediump float;
uniform samplerExternalOES yuvTexSampler;
varying vec2 yuvTexCoords;
void main() {
    gl_FragColor = texure2D(yuvTexCoords,yuvTexSampler);
}
