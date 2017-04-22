LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on

include /Users/yifanyang/Downloads/OpenCV-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := stitcher
LOCAL_SRC_FILES := stitcher.cpp
LOCAL_LDLIBS +=  -llog -ldl

include $(BUILD_SHARED_LIBRARY)