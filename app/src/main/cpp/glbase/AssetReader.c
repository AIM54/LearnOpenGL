//
// Created by tom1 on 2020/9/1.
//

#include "AssetReader.h"

char *readStringFromAssert(AAssetManager *aAssetManager, const char *path) {
    AAsset *aasert = AAssetManager_open(aAssetManager, path, AASSET_MODE_UNKNOWN);
    off_t assetSize = AAsset_getLength(aasert);
    char *buffer = malloc(sizeof(char) * (assetSize + 1));
    memset(buffer, 0, assetSize + 1);
    int readStatus = AAsset_read(aasert, buffer, assetSize);
    AAsset_close(aasert);
    if (readStatus >= 0) {
    }
    return buffer;
}